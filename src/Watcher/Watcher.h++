#pragma once

#include <boost/signals2/signal.hpp>
#include <opencv2/core/mat.hpp>

class Watcher
{
    public:
        virtual ~Watcher() = default;

        boost::signals2::signal<void()> onWatchProblem;

        virtual void Update(const cv::Mat& screenshot);
};
