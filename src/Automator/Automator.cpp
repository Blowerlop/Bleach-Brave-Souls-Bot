#include "Automator.h++"

#include <condition_variable>
#include <iostream>
#include <thread>

#include "opencv2/core.hpp"
#include "../AssetsManager.h++"
#include "../AutoClicker.h++"
#include "../Process.h++"
#include "../Screenshot.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"


void Automator::Start()
{
    const auto pid = GetProcessId();
    windowHandle = GetWindowHandle(pid);
}

void Automator::Update(const std::stop_token& stopStoken)
{
    const auto hbitmap = Screenshot::Window(windowHandle);
    currentScreenshotMat = BitmapConverter::ToMat(hbitmap);
    DeleteObject(hbitmap);
}

void Automator::Run(const std::stop_token& stopToken)
{
    std::condition_variable conditionVariable;
    std::mutex mutex;
    std::unique_lock lock(mutex);

    Start();

    while (!stopToken.stop_requested())
    {
        Update(stopToken);

        conditionVariable.wait_for(
            lock,
            std::chrono::duration<float>{Settings::automatorUpdateDelayInSeconds.load()},
            [&stopToken]
            {
                return stopToken.stop_requested();
            }
        );
    }
}


void Automator::PointAndClick(cv::Point coordinate) const
{
    ShowWindow(windowHandle, SW_RESTORE);
    SetForegroundWindow(windowHandle);

    RECT rect;
    GetWindowRect(windowHandle, &rect);

    AutoClicker::PointAndClick(rect.left + coordinate.x, rect.top + coordinate.y);
}

DWORD Automator::GetProcessId()
{
    const auto pid = Process::FindProcessId("BleachBraveSouls.exe");
    if (pid == 0)
    {
        std::cerr << "Game process not found." << std::endl;
    }

    return pid;
}

HWND Automator::GetWindowHandle(const DWORD pid)
{
    const auto windowHandle = Window::GetWindowHandleByProcessId(pid);

    if (windowHandle == nullptr)
    {
        std::cerr << "Game window not found." << std::endl;
    }

    return windowHandle;
}

bool Automator::DoesScreenshotMatchTemplate(const cv::String& file, cv::Point& coordinate) const
{
    return TemplateMatching::match(currentScreenshotMat, AssetsManager::Load(file), coordinate, false);
}
