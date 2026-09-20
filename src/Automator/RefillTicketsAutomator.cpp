#include "RefillTicketsAutomator.h++"

#include "../ApplicationManager.h++"
#include "../Settings.h++"
#include "../TemplateMatching.h++"

void RefillTicketsAutomator::Update(boost::coroutines2::coroutine<void>::push_type& yield,
                                     const cv::Mat& gameScreenshot)
{
    Automator::Update(yield, gameScreenshot);

    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;

    while (!TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/Cancel.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    if (!CollectSoulsTickets(yield, gameScreenshot))
    {
        BuySoulTickets(yield, gameScreenshot);
    }

    onCompleted();
    yield();
}

std::string RefillTicketsAutomator::ToString() const
{
    return "Refilling Soul Tickets";
}

bool RefillTicketsAutomator::CollectSoulsTickets(boost::coroutines2::coroutine<void>::push_type& yield,
    const cv::Mat& gameScreenshot) const
{
    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;

    while (!TemplateMatching::Match(gameScreenshot, "assets/GiftBox.jpg", coordinate))
    {
        if (TemplateMatching::Match(gameScreenshot, "assets/Menu.jpg", coordinate))
        {
            applicationManager.PointAndClick(coordinate);
        }

        yield();
    }

    TemplateMatching::Match(gameScreenshot, "assets/GiftBox.jpg", coordinate);
    applicationManager.PointAndClick(coordinate);
    yield();

    while (!TemplateMatching::Match(gameScreenshot, "assets/GiftBox/SoulTicket.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);
    yield();

    if (TemplateMatching::Match(gameScreenshot, "assets/GiftBox/NoGift.jpg", coordinate))
    {
        TemplateMatching::Match(gameScreenshot, "assets/GiftBox/Close.jpg", coordinate);
        applicationManager.PointAndClick(coordinate);
        yield();
        return false;
    }

    TemplateMatching::Match(gameScreenshot, "assets/GiftBox/CollectAllOnThisPage.jpg", coordinate);
    applicationManager.PointAndClick(coordinate);
    yield();

    while (!TemplateMatching::Match(gameScreenshot, "assets/GiftBox/Ok.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);
    yield();

    while (TemplateMatching::Match(gameScreenshot, "assets/GiftBox/Close.jpg", coordinate))
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }

    return true;
}

void RefillTicketsAutomator::BuySoulTickets(boost::coroutines2::coroutine<void>::push_type& yield,
    const cv::Mat& gameScreenshot) const
{
    const auto& applicationManager = ApplicationManager::Instance();
    cv::Point coordinate;

    while (!TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/Plus.jpg", coordinate)) yield();

    cv::Point _;
    do
    {
        applicationManager.PointAndClick(coordinate);
        yield();
    }
    // Try to Open the Purchase Souls Tickets panel and wait for it to appear
    while (!TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/Close1.jpg", _));

    bool match = false;

    while (!match)
    {
        switch (Settings::buySoulTicketsAmount.load())
        {
            case Settings::BuySoulTicketsAmount::FIVE:
                match = TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/Five.jpg", coordinate);
                break;

            case Settings::BuySoulTicketsAmount::TWENTY_FIVE:
                match = TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/TwentyFive.jpg", coordinate);
                break;

            case Settings::BuySoulTicketsAmount::FIFTY:
                match = TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/Fifty.jpg", coordinate);
                break;
        }

        yield();
    }

    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/Purchase.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);

    while (!TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/PurchaseComplete.jpg", coordinate)) yield();

    while (!TemplateMatching::Match(gameScreenshot, "assets/SoulTickets/Close2.jpg", coordinate)) yield();
    applicationManager.PointAndClick(coordinate);
    yield();
}
