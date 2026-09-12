#pragma once


#include <opencv2/core/mat.hpp>
#include <boost/coroutine2/all.hpp>
#include <boost/signals2/signal.hpp>

class Automator
{
    public:
        virtual ~Automator() = default;

        virtual void Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot);
        [[nodiscard]] virtual std::string ToString() const = 0;

        friend std::ostream& operator<<(std::ostream& os, const Automator& automator);

        boost::signals2::signal<void()> onCompleted;
};
