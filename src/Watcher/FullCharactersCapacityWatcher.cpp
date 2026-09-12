#include "FullCharactersCapacityWatcher.h++"

#include "../TemplateMatching.h++"


void FullCharactersCapacityWatcher::Update(const cv::Mat& gameScreenshot)
{
    Watcher::Update(gameScreenshot);

    cv::Point _;
    if (TemplateMatching::Match(gameScreenshot, "assets/Inventory/Characters/Sell/CharacterList.jpg", _))
    {
        onWatchProblem();
    }
}
