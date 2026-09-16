#include "SoloRetryAutomator.h++"

#include "../ApplicationManager.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"

void SoloRetryAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    if (retryCount >= Settings::maxRetry.load())
    {
        onCompleted();
        return;
    }


    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;

    // Immediate action. Don't need to wait for a loading before doing anything so don't return.
    if (Settings::useStatsBoost.load() && TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/UseStatsBoost.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/StartQuest.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        return;
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/ItemsObtained.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/TapScreen.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        return;
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Retry.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        retryCount++;
    }
}

std::string SoloRetryAutomator::ToString() const
{
    return std::format("Retry: {} times", retryCount);
}
