#include "StoryQuest.h++"

StoryQuest::StoryQuest() : Automator()
{
}

void StoryQuest::Update()
{
    Automator::Update();

    cv::Point coordinate;

    if (DoesScreenshotMatchTemplate("assets/PrepareForQuest.jpg", coordinate))
    {
        PointAndClick(coordinate);
        return;
    }

    // Immediate action. Don't need to wait for a loading before doing anything so don't return.
    if (DoesScreenshotMatchTemplate("assets/use_stats_boost.jpg", coordinate)) PointAndClick(coordinate);

    if (DoesScreenshotMatchTemplate("assets/StartQuest.jpg", coordinate))
    {
        PointAndClick(coordinate);
        return;
    }

    if (DoesScreenshotMatchTemplate("assets/Skip.jpg", coordinate))
    {
        PointAndClick(coordinate);
        return;
    }

    if (DoesScreenshotMatchTemplate("assets/TapScreen.jpg", coordinate))
    {
        PointAndClick(coordinate);
        return;
    }

    if (DoesScreenshotMatchTemplate("assets/NextQuest.jpg", coordinate))
    {
        PointAndClick(coordinate);
        return;
    }

    if (DoesScreenshotMatchTemplate("assets/QuestClear.jpg", coordinate))
    {
        PointAndClick(coordinate);
        return;
    }
}
