#pragma once
#include "Automator.h++"


class PlayerRankUpConfirmAutomator : public Automator
{
    public:
        void Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot) override;
        std::string ToString() const override;
};
