#include "WatcherController.h++"



WatcherController::WatcherController(std::unique_ptr<Watcher>&& watcher)
    : watcher(std::move(watcher))
{
}

void WatcherController::Update(const cv::Mat& screenshot) const
{
    watcher->Update(screenshot);
}
