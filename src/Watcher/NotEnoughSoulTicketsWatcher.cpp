#include "NotEnoughSoulTicketsWatcher.h++"

#include "../TemplateMatching.h++"

void NotEnoughSoulTicketsWatcher::Update(const cv::Mat& gameScreenshot)
{
    Watcher::Update(gameScreenshot);

    cv::Point _;
    if (TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/NotEnough.jpg", _))
    {
        onWatchProblem();
    }
}
