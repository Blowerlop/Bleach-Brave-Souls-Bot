#pragma once

#include <opencv2/opencv.hpp>


class TemplateMatching
{
    public:
        TemplateMatching() = delete;

        ~TemplateMatching() = delete;

        static bool match(const cv::Mat& image, const cv::Mat& template_, cv::Point& centerPoint, bool debug);

    private:
        static constexpr float THRESHOLD = 0.8f;
        static constexpr int METHOD = cv::TM_CCOEFF_NORMED;

        static void drawMatch(const cv::Mat& image, const cv::Mat& template_, const cv::Point& matchPoint, const cv::Point& centerPoint, const double confidence);
};
