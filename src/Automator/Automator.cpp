#include "Automator.h++"

void Automator::Update(boost::coroutines2::coroutine<void>::push_type& yield, const cv::Mat& gameScreenshot)
{
}

std::ostream& operator<<(std::ostream& os, const Automator& automator)
{
    return os << automator.ToString();
}
