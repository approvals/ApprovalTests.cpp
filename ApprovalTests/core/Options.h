#pragma once
#include "scrubbers/Scrubbers.h"
#include "core/Reporter.h"
namespace ApprovalTests
{
    class Options
    {
    private:
        Scrubber scrubber_;
        //const Reporter& reporter;
    public:
        Options() : scrubber_(Scrubbers::doNothing)
        {
        }
        Options(Scrubber scrubber) : scrubber_(scrubber)
        {
        }
        //   Options(const Reporter& reporter): reporter(reporter)
        Scrubber getScrubber() const
        {
            return scrubber_;
        }

        std::string scrub(const std::string& input) const
        {
            return scrubber_(input);
        }

        DefaultReporter getReporter() const
        {
            return DefaultReporter();
        }
    };
}