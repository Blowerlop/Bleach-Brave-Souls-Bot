#pragma once
#include "Watcher.h++"


class FullChararactersCapacityWatcher : public Watcher
{
    public:
        void Update(const cv::Mat& screenshot) override;
};
