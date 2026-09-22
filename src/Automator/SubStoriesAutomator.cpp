#include "SubStoriesAutomator.h++"

#include "../ApplicationManager.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"

void SubStoriesAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;
    cv::Point _;

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate))
    {
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/SubStories/New.jpg", coordinate))
        {
            goto selectSubStories;;
        }

        yield();
    }

    while (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate) && !TemplateMatching::Match(gameScreenshot, "assets/SubStories.jpg", _))
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }

    TemplateMatching::Match(gameScreenshot, "assets/SubStories.jpg", coordinate);
    applicationManager.PointAndClick(coordinate);

    selectSubStories:
    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/SubStories/New.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);
    yield();

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/SubStories/New.jpg", coordinate))
    {
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Close.jpg", coordinate))
        {
            applicationManager.PointAndClick(coordinate);
        }

        yield();
    }
    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Close.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }

    TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/SubStories/New.jpg", coordinate);
    applicationManager.PointAndClick(coordinate);


    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/SubStories/NoStars.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

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

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/TapScreen.jpg", coordinate))
    {
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Skip.jpg", coordinate))
        {
            applicationManager.PointAndClick(coordinate);
        }
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/Story/Close.jpg", coordinate))
        {
            applicationManager.PointAndClick(coordinate);
        }
        // We had the popup of maximum characters in inventory.
        // The automator sold characters and we are back to the main menu.
        // We can't next quest anymore, so we just finish this sequence and re-do it from the start.
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate)) return;

        yield();
    }
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Home.jpg", coordinate))
    {
        // We had the popup of maximum characters in inventory.
        // The automator sold characters and we are back to the main menu.
        // We can't next quest anymore, so we just finish this sequence and re-do it from the start.
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate)) return;

        yield();
    }

    applicationManager.PointAndClick(coordinate);
}

std::string SubStoriesAutomator::ToString() const
{
    return "Sub Stories";
}
