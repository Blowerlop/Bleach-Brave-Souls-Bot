#pragma once

#include <opencv2/opencv.hpp>


class TemplateMatching
{
    public:
        TemplateMatching() = delete;

        ~TemplateMatching() = delete;

        static bool Match(const cv::Mat& image, const cv::Mat& template_, cv::Point& centerPoint);
        static bool Match(const cv::Mat& image, const cv::String& fileTemplate, cv::Point& centerPoint);

    private:
        static constexpr float THRESHOLD = 0.8f;
        static constexpr int METHOD = cv::TM_CCOEFF_NORMED;
};
