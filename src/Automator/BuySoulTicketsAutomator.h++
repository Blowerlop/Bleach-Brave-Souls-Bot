#pragma once
#include "Automator.h++"


class BuySoulTicketsAutomator : public Automator
{
    public:
        void Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot) override;
        [[nodiscard]] std::string ToString() const override;
};
