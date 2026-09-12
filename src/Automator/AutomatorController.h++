#pragma once
#include <stack>
#include <thread>

#include "Automator.h++"
#include "SellCharactersAutomator.h++"


class AutomatorController
{
    public:
        ~AutomatorController();

        void StackAutomator(std::unique_ptr<Automator> automator_);
        void PopStackAutomator();
        void StartAutomator();
        void StopAutomator();
        void PopAndStopAllAutomator();
        [[nodiscard]] bool HasAnAutomator() const;
        [[nodiscard]] Automator* GetCurrentAutomator() const;

    private:
        std::stack<std::unique_ptr<Automator>> automators;
        Automator* currentAutomator = nullptr;
        std::jthread automatorThead;
};
