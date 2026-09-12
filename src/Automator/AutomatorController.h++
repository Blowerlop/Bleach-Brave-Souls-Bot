#pragma once
#include "Automator.h++"
#include <opencv2/core/mat.hpp>
#include <boost/coroutine2/all.hpp>



class AutomatorController
{
    public:
        std::unique_ptr<Automator> automator;

        explicit AutomatorController(std::unique_ptr<Automator>&& automator);

        void Update(const cv::Mat& gameScreenshot);

    private:
        std::optional<boost::coroutines2::coroutine<void>::pull_type> sequence;
        cv::Mat currentGameScreenshot;
};
