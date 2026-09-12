#pragma once
#include <stack>
#include <thread>
#include <opencv2/core/mat.hpp>

#include "AutomatorController.h++"


class AutomatorManager
{
    public:
        ~AutomatorManager();

        void StackAutomator(AutomatorController&& controller);
        void PopAutomator();
        void PopAllAutomator();
        void StartRunControllersThread();
        bool HasAController();
        [[nodiscard]] AutomatorController& GetController() const;

    private:
        std::stack<AutomatorController> controllers;
        AutomatorController* currentController = nullptr;
        std::jthread thread;
        std::mutex mutex;
};
