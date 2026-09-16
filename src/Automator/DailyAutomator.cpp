#include "DailyAutomator.h++"

#include "../ApplicationManager.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"

void DailyAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;

    // This is the coordinate of the top banner.
    // Try to open it. Maybe the user has already opened it so it will closes, but it's ok because we are going to open it later.
    applicationManager.PointAndClick(cv::Point(466, 231));
    yield();

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/VeryHard.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Normal.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        yield();

    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/PrepareForQuest.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        currentQuest++;
    }

    const int currentTeam = Settings::dailyTeam[currentQuest];
    const std::string filePath = "assets/Team/" + std::to_string(currentTeam) + ".jpg";
    for (int i = 0; i < currentTeam; i++)
    {
        if (TemplateMatching::Match(gameScreenshot, filePath, coordinate))
        {
            applicationManager.PointAndClick(coordinate);
        }
        else
        {
            TemplateMatching::Match(gameScreenshot, "assets/Team/Next.jpg", coordinate);
            applicationManager.PointAndClick(coordinate);
        }

        yield();
    }

    if (Settings::useStatsBoost.load() && TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo/UseStatsBoost.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/SetBoost.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        yield();

        TemplateMatching::Match(gameScreenshot, "assets/Quests/SetBoostPlus.jpg", coordinate);

        for (int i = 0; i < 10; ++i)
        {
            applicationManager.PointAndClick(coordinate);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/StartQuest.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
    }

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/TapScreen.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Close.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        return;
    }

    if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Retry.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
    }
}

std::string DailyAutomator::ToString() const
{
    return "Daily";
}
