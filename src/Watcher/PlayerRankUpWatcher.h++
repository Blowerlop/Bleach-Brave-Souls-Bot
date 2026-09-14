#pragma once
#include "Watcher.h++"


class PlayerRankUpWatcher : public Watcher
{
    public:
        void Update(const cv::Mat& gameScreenshot) override;
};
