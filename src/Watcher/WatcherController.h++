#pragma once
#include "Watcher.h++"
#include <opencv2/core/mat.hpp>



class WatcherController
{
    public:
        std::unique_ptr<Watcher> watcher;

        explicit WatcherController(std::unique_ptr<Watcher>&& watcher);

        void Update(const cv::Mat& screenshot) const;
};
