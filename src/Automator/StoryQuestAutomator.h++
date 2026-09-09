#pragma once
#include <boost/coroutine2/coroutine.hpp>

#include "Automator.h++"


class StoryQuestAutomator final : public Automator
{
    protected:
        void Update(const std::stop_token& stopToken) override;

    private:
        std::optional<boost::coroutines2::coroutine<void>::pull_type> sequence;

        void RunSequence(const std::stop_token& stopToken, boost::coroutines2::coroutine<void>::push_type& yield);
};
