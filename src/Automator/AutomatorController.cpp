#include "AutomatorController.h++"


AutomatorController::AutomatorController(std::unique_ptr<Automator>&& automator)
    : automator(std::move(automator))
{
}

void AutomatorController::Update(const cv::Mat& gameScreenshot)
{
    currentGameScreenshot = gameScreenshot;

    if (!sequence)
    {
        sequence.emplace([this] (boost::coroutines2::coroutine<void>::push_type& yield) { automator->Update(yield, currentGameScreenshot);  });
    }
    else (*sequence)();

    if (!*sequence) sequence.reset();
}
