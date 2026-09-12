#include "AutomatorManager.h++"

#include <condition_variable>
#include <iostream>
#include <opencv2/highgui.hpp>

#include "AutomatorController.h++"
#include "../ApplicationManager.h++"
#include "../BitmapConverter.h++"
#include "../Process.h++"
#include "../Screenshot.h++"
#include "../Settings.h++"
#include "../Window.h++"


AutomatorManager::~AutomatorManager()
{
    thread.request_stop();
}

void AutomatorManager::StackAutomator(AutomatorController&& controller)
{
    std::lock_guard lock(mutex);

    controllers.push(std::move(controller));
    currentController = &controllers.top();
}

void AutomatorManager::PopAutomator()
{
    std::lock_guard lock(mutex);

    if (controllers.empty()) return;

    controllers.pop();

    if (controllers.empty())
    {
        currentController = nullptr;
    }
    else
    {
        currentController = &controllers.top();
    }
}

void AutomatorManager::PopAllAutomator()
{
    while (!controllers.empty())
    {
        PopAutomator();
    }
}

void AutomatorManager::StartRunControllersThread()
{
    thread = std::jthread([this](const std::stop_token& stopToken)
    {
        std::unique_lock lock(mutex);
        std::condition_variable_any conditionVariable;

        while (!stopToken.stop_requested())
        {
            const AutomatorController* controller = currentController;
            lock.unlock();

            if (controller != nullptr)
            {
                const auto screenshot = ApplicationManager::Instance().TakeGameScreenshot();

                lock.lock();
                if (currentController == controller)
                {
                    currentController->Update(screenshot);
                }
            }
            else
            {
                lock.lock();
            }

            conditionVariable.wait_for(
                lock,
                std::chrono::duration<float>{Settings::automatorUpdateDelayInSeconds.load()},
                [&stopToken]
                {
                    return stopToken.stop_requested();
                }
            );
        }
    });
}

bool AutomatorManager::HasAController()
{
    std::lock_guard lock(mutex);

    return currentController != nullptr;
}

AutomatorController& AutomatorManager::GetController() const
{
    return *currentController;
}
