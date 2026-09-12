#include "ApplicationManager.h++"

#include <iostream>

#include "AutoClicker.h++"
#include "BitmapConverter.h++"
#include "Process.h++"
#include "Screenshot.h++"
#include "Window.h++"
#include "Automator/SellCharactersAutomator.h++"
#include "Watcher/FullCharactersCapacityWatcher.h++"


ApplicationManager::ApplicationManager()
    : gameProcessId(Process::FindProcessId("BleachBraveSouls.exe")),
      gameWindowHandle(Window::GetWindowHandleByProcessId(gameProcessId))

{
    if (gameProcessId == 0 || gameWindowHandle == nullptr)
    {
        throw std::runtime_error("Game process not found.");
    }

    // Automator
    automatorManager.StartRunControllersThread();

    // Watcher
    auto fullCharactersCapacityWatcher = std::make_unique<FullCharactersCapacityWatcher>();
    fullCharactersCapacityWatcher->onWatchProblem.connect([this]
    {
        auto sellCharactersAutomator = std::make_unique<SellCharactersAutomator>();
        sellCharactersAutomator->onCompleted.connect([this]
        {
            automatorManager.PopAutomator();
        });

        this->automatorManager.StackAutomator(AutomatorController(std::move(sellCharactersAutomator)));
    });

    watcherManager.AddController(WatcherController(std::move(fullCharactersCapacityWatcher)));
    watcherManager.StartRunControllersThread();
}

ApplicationManager& ApplicationManager::Instance()
{
    static ApplicationManager instance;
    return instance;
}

AutomatorManager& ApplicationManager::GetAutomatorManager()
{
    return automatorManager;
}

cv::Mat ApplicationManager::TakeGameScreenshot() const
{
    const auto hbitmap = Screenshot::Window(gameWindowHandle);

    auto screenshot = BitmapConverter::ToMat(hbitmap);
    DeleteObject(hbitmap);

    if (screenshot.empty())
    {
        throw std::runtime_error("Screenshot capture failed (empty image).");
    }

    return screenshot;
}

void ApplicationManager::PointAndClick(const cv::Point coordinate) const
{
    ShowWindow(gameWindowHandle, SW_RESTORE);
    SetForegroundWindow(gameWindowHandle);

    RECT rect;
    GetWindowRect(gameWindowHandle, &rect);

    AutoClicker::PointAndClick(rect.left + coordinate.x, rect.top + coordinate.y);
}
