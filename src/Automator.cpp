#include "Automator.h++"

#include <iostream>

#include "opencv2/core.hpp"
#include "AssetsManager.h++"
#include "AutoClicker.h++"
#include "Process.h++"
#include "Screenshot.h++"
#include "TemplateMatching.h++"


void Automator::Start()
{
    const auto pid = GetProcessId();
    windowHandle = GetWindowHandle(pid);
}

void Automator::OnScreenshotMatchTemplate(const cv::Point coordinate)
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

void Automator::TakeScreenshotAndMatchTemplate(const cv::String& file)
{
    const HBITMAP hbitmap = Screenshot::Window(windowHandle);
    const cv::Mat gameScreenshotMat = BitmapConverter::ToMat(hbitmap);
    DeleteObject(hbitmap);

    if (cv::Point coordinate{}; TemplateMatching::match(gameScreenshotMat, AssetsManager::Load(file), coordinate, false))
    {
        OnScreenshotMatchTemplate(coordinate);
    }
}
