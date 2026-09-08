#pragma once
#include "Automator.h++"
#include <optional>
#include <boost/coroutine2/all.hpp>


class SellCharactersAutomator : public Automator
{
    public:
        [[nodiscard]] bool HasSell() const;

    protected:
        void Update(const std::stop_token& stopStoken) override;

    private:
        std::atomic_bool hasSell = false;
        std::optional<boost::coroutines2::coroutine<void>::pull_type> sequence;

        void RunSequence(boost::coroutines2::coroutine<void>::push_type& yield);


};
