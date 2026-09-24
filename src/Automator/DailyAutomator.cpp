#include "DailyAutomator.h++"

#include "../ApplicationManager.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"

void DailyAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;


    while (!(TemplateMatching::Match(gameScreenshot, "assets/Quests/VeryHard.jpg", coordinate) || TemplateMatching::Match(gameScreenshot, "assets/Quests/Normal.jpg", coordinate)))
    {
        // This is the coordinate of the top banner.
        // Try to open it. Maybe the user has already opened it so it will closes, but it's ok because we are going to open it later.
        applicationManager.PointAndClick(cv::Point(466, 231));
        yield();

        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/StartQuest.jpg", coordinate))
        {
            goto questSelected;
        }

        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Solo.jpg", coordinate))
        {
            onCompleted();
        }
    }
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/PrepareForQuest.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);
    currentQuest++;

    // Reset so we don't click on anything important by accident
    coordinate = cv::Point(0, 0);

    questSelected:
    const int requestedTeam = Settings::dailyTeam[currentQuest];
    const std::string requestedTeamFilePath = "assets/Team/" + std::to_string(requestedTeam) + ".jpg";
    while (!TemplateMatching::Match(gameScreenshot, requestedTeamFilePath, coordinate))
    {
        TemplateMatching::Match(gameScreenshot, "assets/Team/Next.jpg", coordinate);
        applicationManager.PointAndClick(coordinate);
        yield();
    }

    applicationManager.PointAndClick(coordinate);

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

    // When we click, we can can be notify that we have no more tickets and it will switch to the BuySoulTicketsAutomator.
    // After that, if we not loop, we are stuck because we had already click on the "Start Quest" button.
    // So we need to re-click until we past the "Start Quest" screen.
    while (TemplateMatching::Match(gameScreenshot, "assets/Quests/StartQuest.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/TapScreen.jpg", coordinate))
    {
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Close.jpg", coordinate))
        {
            applicationManager.PointAndClick(coordinate);
            yield();
        }

        yield();
    }
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, "assets/Quests/Retry.jpg", coordinate))
    {
        if (TemplateMatching::Match(gameScreenshot, "assets/Quests/Close.jpg", coordinate))
        {
            applicationManager.PointAndClick(coordinate);
        }

        yield();
    }
    applicationManager.PointAndClick(coordinate);
}

std::string DailyAutomator::ToString() const
{
    return "Daily";
}
