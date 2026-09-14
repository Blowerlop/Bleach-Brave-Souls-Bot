#pragma once
#include "Watcher.h++"


class NotEnoughSoulTicketsWatcher : public Watcher
{
    public:
        void Update(const cv::Mat& gameScreenshot) override;
};
