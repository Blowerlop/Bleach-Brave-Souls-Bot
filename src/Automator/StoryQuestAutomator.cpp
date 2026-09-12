#include "StoryQuestAutomator.h++"

#include <atomic>
#include <future>

#include "AutomatorController.h++"
#include "SellCharactersAutomator.h++"
#include "../Settings.h++"

void StoryQuestAutomator::Update(const std::stop_token& stopToken)
{
    Automator::Update(stopToken);

    if (!sequence)
    {
        sequence.emplace([stopToken, this](boost::coroutines2::coroutine<void>::push_type& yield)
        {
            RunSequence(stopToken, yield);
        });
    }
    else (*sequence)();

    if (!*sequence) sequence.reset();
}

void StoryQuestAutomator::RunSequence(const std::stop_token& stopToken,
                                      boost::coroutines2::coroutine<void>::push_type& yield)
{
    cv::Point coordinate;

    if (DoesScreenshotMatchTemplate("assets/Inventory/Characters/Sell/CharacterList.jpg", coordinate))
    {
        AutomatorController automatorController;
        automatorController.StackAutomator(std::make_unique<SellCharactersAutomator>());
        automatorController.StartAutomator();

        auto* automator = dynamic_cast<SellCharactersAutomator*>(automatorController.GetCurrentAutomator());
        while (!stopToken.stop_requested() && !automator->HasSell())
        {
            // noop
        }

        automatorController.StopAutomator();
    }

    if (DoesScreenshotMatchTemplate("assets/Quests/Solo.jpg", coordinate))
    {
        cv::Point _;

        // The loading can cause a click to be missed, so we need to click until the next screen is loaded.
        do
        {
            PointAndClick(coordinate);
            yield();
        }
        while (DoesScreenshotMatchTemplate("assets/Quests/Solo.jpg", coordinate) && !DoesScreenshotMatchTemplate("assets/Quests/Solo/Story.jpg", _));

        while (!DoesScreenshotMatchTemplate("assets/Quests/Solo/Story.jpg", coordinate)) yield();
        PointAndClick(coordinate);

        while (!DoesScreenshotMatchTemplate("assets/Quests/Solo/Story/CurrentQuestSlot.jpg", coordinate)) yield();

        // The animation can cause a click to be missed, so we need to click until the animation is finished.
        do
        {
            PointAndClick(coordinate);
            yield();
        }
        while (!DoesScreenshotMatchTemplate("assets/PrepareForQuest.jpg", _));
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
