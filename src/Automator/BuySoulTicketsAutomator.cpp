#include "BuySoulTicketsAutomator.h++"

#include "../ApplicationManager.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"

void BuySoulTicketsAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield,
                                     const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;
    const std::string assetsPath = "assets/SoulTickets/";

    if (TemplateMatching::Match(gameScreenshot, assetsPath + "Cancel.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
    }

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "Plus.jpg", coordinate)) yield();

    cv::Point _;
    do
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }
    // Try to Open the Purchase Souls Tickets panel and wait for it to appear
    while (TemplateMatching::Match(gameScreenshot, assetsPath + "Plus.jpg", coordinate) && !TemplateMatching::Match(gameScreenshot, assetsPath + "Close1.jpg", _));

    bool match = false;

    while (!match)
    {
        switch (Settings::buySoulTicketsAmount.load())
        {
            case Settings::BuySoulTicketsAmount::FIVE:
                match = TemplateMatching::Match(gameScreenshot, assetsPath + "Five.jpg", coordinate);
                break;

            case Settings::BuySoulTicketsAmount::TWENTY_FIVE:
                match = TemplateMatching::Match(gameScreenshot, assetsPath + "TwentyFive.jpg", coordinate);
                break;

            case Settings::BuySoulTicketsAmount::FIFTY:
                match = TemplateMatching::Match(gameScreenshot, assetsPath + "Fifty.jpg", coordinate);
                break;
        }

        yield();
    }

    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "Purchase.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "PurchaseComplete.jpg", coordinate)) yield();

    while (!TemplateMatching::Match(gameScreenshot, assetsPath + "Close2.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);
    yield();

    onCompleted();
    std::cout << "After on completed" << std::endl;
}

std::string BuySoulTicketsAutomator::ToString() const
{
    return "Buying Soul Tickets";
}
