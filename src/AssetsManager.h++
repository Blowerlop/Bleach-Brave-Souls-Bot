#pragma once
#include <map>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/core/mat.hpp>


class AssetsManager
{
    public:
        AssetsManager() = delete;

        ~AssetsManager() = delete;

        static cv::Mat& Load(const cv::String &file);

    private:
        static std::map<cv::String, cv::Mat> cache;
};
