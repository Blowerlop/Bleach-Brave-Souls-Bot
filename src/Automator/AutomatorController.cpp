#include "AutomatorController.h++"

#include <thread>

void AutomatorController::SetNewAutomator(std::unique_ptr<Automator> automator_)
{
    StopAutomator();
    automator = std::move(automator_);
}

void AutomatorController::StartAutomator()
{
    automatorThead = std::jthread([this]
    {
        automator->Run();
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
