#include "AutomatorController.h++"

#include <thread>

#include "SellCharactersAutomator.h++"

AutomatorController::~AutomatorController()
{
    StopAutomator();
}

void AutomatorController::SetNewAutomator(std::unique_ptr<Automator> automator_)
{
    StopAutomator();
    automator = std::move(automator_);
}

void AutomatorController::StartAutomator()
{
    automatorThead = std::jthread([this](const std::stop_token& stopToken)
    {
        automator->Run(stopToken);
    });
}

void AutomatorController::StopAutomator()
{
    automatorThead.request_stop();
    automator.reset();
}

bool AutomatorController::HasAnAutomator() const
{
    return automator != nullptr;
}

Automator* AutomatorController::GetAutomator() const
{
    return automator.get();
}
