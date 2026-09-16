#pragma once
#include "Automator.h++"


class DailyAutomator : public Automator
{
    public:
        void Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot) override;
        [[nodiscard]] std::string ToString() const override;

    private:
        int currentQuest = -1;
};
