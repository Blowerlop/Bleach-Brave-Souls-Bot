#include "PlayerRankUpConfirmAutomator.h++"

#include "../ApplicationManager.h++"
#include "../TemplateMatching.h++"

void PlayerRankUpConfirmAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield,
                                          const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    cv::Point coordinate;

    if (!TemplateMatching::Match(gameScreenshot, "assets/PlayerRankReward/PlayerRankReward.jpg", coordinate))
    {
        std::cerr << "Player rank up not detected" << std::endl;
        onCompleted();
    }

    TemplateMatching::Match(gameScreenshot, "assets/PlayerRankReward/Close.jpg", coordinate);
    ApplicationManager::Instance().PointAndClick(coordinate);
    yield();

    onCompleted();
}

std::string PlayerRankUpConfirmAutomator::ToString() const
{
    return "Player rank up confirm";
}
