#include "Automator.h++"

#include <imgui.h>
#include <iostream>

#include "opencv2/core.hpp"
#include "AssetsManager.h++"
#include "AutoClicker.h++"
#include "Process.h++"
#include "Screenshot.h++"
#include "Settings.h++"
#include "TemplateMatching.h++"


void Automator::Start()
{
    hasStarted = true;

    const auto pid = GetProcessId();
    windowHandle = GetWindowHandle(pid);
}

bool Automator::CanUpdate()
{
    currentUpdateDelay -= ImGui::GetIO().DeltaTime;

    if (currentUpdateDelay <= 0)
    {
        currentUpdateDelay = Settings::automatorUpdateDelayInSeconds;
        return true;
    }

    return false;
}

void Automator::Update()
{
    const auto hbitmap = Screenshot::Window(windowHandle);
    currentScreenshotMat = BitmapConverter::ToMat(hbitmap);
    DeleteObject(hbitmap);
}

bool Automator::HasStarted() const
{
    return hasStarted;
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

