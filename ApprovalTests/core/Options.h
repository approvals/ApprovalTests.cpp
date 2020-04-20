#pragma once
#include "scrubbers/Scrubbers.h"
#include "core/Reporter.h"
#include "reporters/DefaultReporter.h"
namespace ApprovalTests
{
    class Options
    {
    private:
        Scrubber scrubber_;
        DefaultReporter defaultReporter;
        const Reporter& reporter = defaultReporter;

    public:
        Options() : scrubber_(Scrubbers::doNothing)
        {
        }
        Options(Scrubber scrubber) : scrubber_(scrubber)
        {
        }
        Options(const Reporter& reporter) : reporter(reporter)
        {
        }
        Scrubber getScrubber() const
        {
            return scrubber_;
        }

        std::string scrub(const std::string& input) const
        {
            return scrubber_(input);
        }

        const Reporter& getReporter() const
        {
            return reporter;
        }
    };
}