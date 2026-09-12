#include "TemplateMatching.h++"

#include "AssetsManager.h++"

bool TemplateMatching::Match(const cv::Mat& image, const cv::Mat& template_, cv::Point& centerPoint)
{
    cv::Mat result;

    cv::matchTemplate(
        image,
        template_,
        result,
        METHOD
    );

    double maxValue;
    cv::Point maxPoint;

    cv::minMaxLoc(
        result,
        nullptr,
        &maxValue,
        nullptr,
        &maxPoint
    );

    if (maxValue < THRESHOLD) return false;

    const cv::Point matchPoint = maxPoint;

    centerPoint = cv::Point(
        matchPoint.x + template_.cols / 2,
        matchPoint.y + template_.rows / 2
    );

    return true;
}

bool TemplateMatching::Match(const cv::Mat& image, const cv::String& fileTemplate, cv::Point& centerPoint)
{
    return Match(image, AssetsManager::Load(fileTemplate), centerPoint);
}


