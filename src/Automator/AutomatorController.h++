#pragma once
#include <thread>

#include "Automator.h++"
#include "SellCharactersAutomator.h++"


class AutomatorController
{
    public:
        ~AutomatorController();

        void SetNewAutomator(std::unique_ptr<Automator> automator_);
        void StartAutomator();
        void StopAutomator();
        [[nodiscard]] bool HasAnAutomator() const;
        [[nodiscard]] Automator* GetAutomator() const;

    private:
        std::unique_ptr<Automator> automator;
        std::jthread automatorThead;
};
