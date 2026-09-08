#include "StoryQuestAutomator.h++"

#include <atomic>
#include <future>

#include "AutomatorController.h++"
#include "SellCharactersAutomator.h++"
#include "../Settings.h++"

void StoryQuestAutomator::Update(const std::stop_token& stopStoken)
{
    Automator::Update(stopStoken);

    cv::Point coordinate;

    if (DoesScreenshotMatchTemplate("assets/CharacterList.jpg", coordinate))
    {
        AutomatorController automatorController;
        automatorController.SetNewAutomator(std::make_unique<SellCharactersAutomator>());
        automatorController.StartAutomator();

        auto* automator = dynamic_cast<SellCharactersAutomator*>(automatorController.GetAutomator());
        while (!stopStoken.stop_requested() && !automator->HasSell())
        {
            // noop
        }

        automatorController.StopAutomator();
    }

    if (DoesScreenshotMatchTemplate("assets/PrepareForQuest.jpg", coordinate))
    {
        PointAndClick(coordinate);
        return;
    }

    // Immediate action. Don't need to wait for a loading before doing anything so don't return.
    if (Settings::useStatsBoost.load() && DoesScreenshotMatchTemplate("assets/UseStatsBoost.jpg", coordinate))
    {
        PointAndClick(coordinate);
    }

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
