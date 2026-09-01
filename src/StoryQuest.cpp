#include "StoryQuest.h++"

#include <thread>


StoryQuest::StoryQuest(): Automator()
{
}

void StoryQuest::Start()
{
    Automator::Start();

    while (true)
    {
        TakeScreenshotAndMatchTemplate("assets/PrepareForQuest.jpg");
        TakeScreenshotAndMatchTemplate("assets/StartQuest.jpg");
        TakeScreenshotAndMatchTemplate("assets/Skip.jpg");
        TakeScreenshotAndMatchTemplate("assets/TapScreen.jpg");
        TakeScreenshotAndMatchTemplate("assets/NextQuest.jpg");
        TakeScreenshotAndMatchTemplate("assets/QuestClear.jpg");

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

}
