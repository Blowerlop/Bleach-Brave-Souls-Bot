#include "AutomatorController.h++"

#include <iostream>
#include <thread>

#include "SellCharactersAutomator.h++"

AutomatorController::~AutomatorController()
{
    if (currentAutomator == nullptr) return;

    StopAutomator();
}

void AutomatorController::StackAutomator(std::unique_ptr<Automator> automator_)
{
    automators.push(std::move(automator_));
    currentAutomator = automators.top().get();
}

void AutomatorController::PopStackAutomator()
{
    if (!automators.empty())
    {
        auto automator = automators.top().get();
        if (automator == currentAutomator)
        {
            std::cerr << "Pop automator without stopping it first." << std::endl;
        }

        automators.pop();
        currentAutomator = nullptr;
    }
}

void AutomatorController::StartAutomator()
{
    if (currentAutomator == nullptr)
    {
        std::cerr << "No automator to start." << std::endl;
        return;
    }

    automatorThead = std::jthread([this](const std::stop_token& stopToken)
    {
        currentAutomator->Run(stopToken);
    });
}

void AutomatorController::StopAutomator()
{
    if (currentAutomator == nullptr)
    {
        std::cerr << "No automator to stop." << std::endl;
        return;
    }

    automatorThead.request_stop();
}

void AutomatorController::PopAndStopAllAutomator()
{
    while (!automators.empty())
    {
        automators.pop();
    }
}

bool AutomatorController::HasAnAutomator() const
{
    return currentAutomator != nullptr;
}

Automator* AutomatorController::GetCurrentAutomator() const
{
    return currentAutomator;
}
