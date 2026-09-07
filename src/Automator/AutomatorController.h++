#pragma once
#include <thread>

#include "Automator.h++"


class AutomatorController
{
    public:
        void SetNewAutomator(std::unique_ptr<Automator> automator_);
        void StartAutomator();
        void StopAutomator();
        [[nodiscard]] bool HasAnAutomator() const;

    private:
        std::unique_ptr<Automator> automator;
        std::jthread automatorThead;
};
