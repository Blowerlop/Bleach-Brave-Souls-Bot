#include "FullChararactersCapacityWatcher.h++"

#include "../TemplateMatching.h++"


void FullChararactersCapacityWatcher::Update(const cv::Mat& screenshot)
{
    Watcher::Update(screenshot);

    cv::Point _;
    if (TemplateMatching::Match(screenshot, "assets/Inventory/Characters/Sell/CharacterList.jpg", _))
    {
        onWatchProblem();
    }
}
