#include "WatcherManager.h++"

#include <condition_variable>
#include <iostream>
#include <ostream>

#include "../BitmapConverter.h++"
#include "../Process.h++"
#include "../Screenshot.h++"
#include "../Settings.h++"
#include "../Window.h++"


WatcherManager::~WatcherManager()
{
    thread.request_stop();
}

void WatcherManager::AddController(WatcherController&& controller)
{
    if (thread.joinable())
    {
        std::cerr << "Cannot add controller: WatchManager has started" << std::endl;
        return;
    }

    controllers.push_back(std::move(controller));
}

void WatcherManager::StartRunControllersThread()
{
    thread = std::jthread([this](const std::stop_token& stopToken)
    {
        std::condition_variable conditionVariable;
        std::mutex mutex;
        std::unique_lock lock(mutex);

        while (!stopToken.stop_requested())
        {
            const auto screenshot = TakeGameScreenshot();

            for (auto& controller : controllers)
            {
                controller.Update(screenshot);
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

cv::Mat WatcherManager::TakeGameScreenshot() const
{
    const auto processId = Process::FindProcessId("BleachBraveSouls.exe");
    const auto windowHandle = Window::GetWindowHandleByProcessId(processId);

    const auto hbitmap = Screenshot::Window(windowHandle);
    auto screenshot = BitmapConverter::ToMat(hbitmap);
    DeleteObject(hbitmap);

    return screenshot;
}
