#pragma once
#include "Automator.h++"
#include <boost/coroutine2/all.hpp>


class SellCharactersAutomator : public Automator
{
    public:
        void Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot) override;
        [[nodiscard]] std::string ToString() const override;
};
