#include "StoryAutomator.h++"

#include "../ApplicationManager.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"

void StoryAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield,
    const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate))
    {
        cv::Point _;

        // The loading can cause a click to be missed, so we need to click until the next screen is loaded.
        do
        {
            applicationManager.PointAndClick(coordinate);
            yield();

        }
        while (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate) && !TemplateMatching::Match(gameScreenshot, "assets/Story.jpg", _));

        while (!TemplateMatching::Match(gameScreenshot, "assets/Story.jpg", coordinate)) yield();
        applicationManager.PointAndClick(coordinate);

        while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/CurrentQuestSlot.jpg", coordinate)) yield();

        // The animation can cause a click to be missed, so we need to click until the animation is finished.
        do
        {
            applicationManager.PointAndClick(coordinate);
            yield();
        }
        while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/PrepareForQuest.jpg", _));
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/PrepareForQuest.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        return;
    }

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

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Skip.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        return;
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/TapScreen.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        return;
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/NextQuest.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        return;
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/QuestClear.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
    }
}

std::string StoryAutomator::ToString() const
{
    return "Story";
}
