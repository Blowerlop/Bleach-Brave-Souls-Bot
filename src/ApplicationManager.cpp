#include "ApplicationManager.h++"

#include <iostream>

#include "AutoClicker.h++"
#include "BitmapConverter.h++"
#include "Process.h++"
#include "Screenshot.h++"
#include "Window.h++"
#include "Automator/RefillTicketsAutomator.h++"
#include "Automator/PlayerRankUpConfirmAutomator.h++"
#include "Automator/SellCharactersAutomator.h++"
#include "Watcher/FullCharactersCapacityWatcher.h++"
#include "Watcher/NotEnoughSoulTicketsWatcher.h++"
#include "Watcher/PlayerRankUpWatcher.h++"


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
    std::unique_ptr<Watcher> watcher;

    watcher = std::make_unique<FullCharactersCapacityWatcher>();
    watcher->onWatchProblem.connect([this]
    {
        auto automator = std::make_unique<SellCharactersAutomator>();
        automator->onCompleted.connect([this]
        {
            std::thread([this] { automatorManager.PopAutomator(); }).detach();
        });

        this->automatorManager.StackAutomator(AutomatorController(std::move(automator)));
    });
    watcherManager.AddController(WatcherController(std::move(watcher)));

    watcher = std::make_unique<NotEnoughSoulTicketsWatcher>();
    watcher->onWatchProblem.connect([this]
    {
        auto automator = std::make_unique<RefillTicketsAutomator>();
        automator->onCompleted.connect([this]
        {
            std::thread([this] { automatorManager.PopAutomator(); }).detach();
        });

        this->automatorManager.StackAutomator(AutomatorController(std::move(automator)));
    });
    watcherManager.AddController(WatcherController(std::move(watcher)));

    watcher = std::make_unique<PlayerRankUpWatcher>();
    watcher->onWatchProblem.connect([this]
    {
        auto automator = std::make_unique<PlayerRankUpConfirmAutomator>();
        automator->onCompleted.connect([this]
        {
            std::thread([this] { automatorManager.PopAutomator(); }).detach();
        });

        this->automatorManager.StackAutomator(AutomatorController(std::move(automator)));
    });
    watcherManager.AddController(WatcherController(std::move(watcher)));

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
