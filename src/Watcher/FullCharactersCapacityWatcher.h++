#pragma once
#include "Watcher.h++"


class FullCharactersCapacityWatcher : public Watcher
{
    public:
        void Update(const cv::Mat& gameScreenshot) override;
};
