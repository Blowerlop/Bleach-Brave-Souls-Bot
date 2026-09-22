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
    cv::Point _;

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate))
    {
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/PrepareForQuest.jpg", coordinate))
        {
            goto prepareForQuest;
        }

        // We unlock a new part
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/Close.jpg", coordinate))
        {
            // Close the popup
            applicationManager.PointAndClick(coordinate);

            while (!(TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/CurrentQuestSlot1.jpg", coordinate) || TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/CurrentQuestSlot2.jpg", coordinate)))
            {
                // Click on the new part
                applicationManager.PointAndClick(coordinate);
                yield();
            }

            goto currentQuestSlot;
        }

        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Skip.jpg", coordinate))
        {
            applicationManager.PointAndClick(coordinate);

            while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/QuestClear.jpg", coordinate)) yield();
            applicationManager.PointAndClick(coordinate);
            return;
        }

        yield();
    }

    while (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate) && !TemplateMatching::Match(gameScreenshot, "assets/Story.jpg", _))
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }

    TemplateMatching::Match(gameScreenshot, "assets/Story.jpg", coordinate);
    applicationManager.PointAndClick(coordinate);


    currentQuestSlot:
    while (!(TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/CurrentQuestSlot1.jpg", coordinate) || TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/CurrentQuestSlot2.jpg", coordinate)))
    {
        yield();
    }

    do
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }
    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/PrepareForQuest.jpg", _));

    prepareForQuest:
    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/PrepareForQuest.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/StartQuest.jpg", coordinate)) yield();

    if (Settings::useStatsBoost.load() && TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/UseStatsBoost.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
    }

    while (TemplateMatching::Match(gameScreenshot, "assets/Quests/StartQuest.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }

    tapScreen:
    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/TapScreen.jpg", coordinate))
    {
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Skip.jpg", coordinate))
        {
            applicationManager.PointAndClick(coordinate);
        }
        // We had the popup of maximum characters in inventory.
        // The automator sold characters and we are back to the main menu.
        // We can't next quest anymore, so we just finish this sequence and re-do it from the start.
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate)) return;
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/TapScreen.jpg", coordinate))
        {
            goto tapScreen;
        }

        yield();
    }
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/NextQuest.jpg", coordinate))
    {
        // We had the popup of maximum characters in inventory.
        // The automator sold characters and we are back to the main menu.
        // We can't next quest anymore, so we just finish this sequence and re-do it from the start.
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate)) return;

        yield();
    }

    applicationManager.PointAndClick(coordinate);
}

std::string StoryAutomator::ToString() const
{
    return "Story";
}
