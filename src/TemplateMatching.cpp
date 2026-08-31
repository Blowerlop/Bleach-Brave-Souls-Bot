#include "TemplateMatching.h++"

bool TemplateMatching::match(const cv::Mat& image, const cv::Mat& template_, cv::Point& centerPoint, bool debug)
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

    const cv::Point matchPoint = maxPoint;

    centerPoint = cv::Point(
        matchPoint.x + template_.cols / 2,
        matchPoint.y + template_.rows / 2
    );

    if (debug)
    {
        drawMatch(image, template_, matchPoint, centerPoint, maxValue);
    }

    if (maxValue < THRESHOLD) return false;
    return true;
}

void TemplateMatching::drawMatch(const cv::Mat& image, const cv::Mat& template_, const cv::Point& matchPoint,
                                 const cv::Point& centerPoint, const double confidence)
{
    // ----------------------------------------
    // Draw rectangle around detected template
    // ----------------------------------------

    cv::rectangle(
        image,
        matchPoint,
        cv::Point(
            matchPoint.x + template_.cols,
            matchPoint.y + template_.rows
        ),
        cv::Scalar(0, 255, 0),
        2
    );

    // ----------------------------------------
    // Draw crosshair at match center
    // ----------------------------------------

    constexpr int crosshairSize = 15;

    cv::line(
        image,
        cv::Point(
            centerPoint.x - crosshairSize,
            centerPoint.y
        ),
        cv::Point(
            centerPoint.x + crosshairSize,
            centerPoint.y
        ),
        cv::Scalar(0, 0, 255),
        2
    );

    cv::line(
        image,
        cv::Point(
            centerPoint.x,
            centerPoint.y - crosshairSize
        ),
        cv::Point(
            centerPoint.x,
            centerPoint.y + crosshairSize
        ),
        cv::Scalar(0, 0, 255),
        2
    );

    // ----------------------------------------
    // Draw confidence text
    // ----------------------------------------

    const int textY =
            (matchPoint.y - 10 > 20)
                ? matchPoint.y - 10
                : 20;

    cv::putText(
        image,
        "Confidence: " + std::to_string(confidence),
        cv::Point(matchPoint.x, textY),
        cv::FONT_HERSHEY_SIMPLEX,
        0.7,
        cv::Scalar(0, 255, 0),
        2
    );

    // ----------------------------------------
    // Show result
    // ----------------------------------------

    cv::imshow("Template matching result", image);
    cv::waitKey(0);
}
