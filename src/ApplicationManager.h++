#pragma once
#include "Automator/AutomatorManager.h++"
#include "Watcher/WatcherManager.h++"


class ApplicationManager
{
    public:
        ApplicationManager();


        [[nodiscard]] static ApplicationManager& Instance();
        [[nodiscard]] AutomatorManager& GetAutomatorManager();
        [[nodiscard]] cv::Mat TakeGameScreenshot() const;
        void PointAndClick(cv::Point coordinate) const;

    private:
        const DWORD gameProcessId;
        const HWND gameWindowHandle = nullptr;

        AutomatorManager automatorManager;
        WatcherManager watcherManager;
};
