#include "PlayerRankUpWatcher.h++"

#include "../TemplateMatching.h++"

void PlayerRankUpWatcher::Update(const cv::Mat& gameScreenshot)
{
    Watcher::Update(gameScreenshot);

    cv::Point _;
    if (TemplateMatching::Match(gameScreenshot, "assets/PlayerRankReward/PlayerRankReward.jpg", _))
    {
        onWatchProblem();
    }
}
