#pragma once
#include "scrubbers/Scrubbers.h"
#include "core/Reporter.h"
#include "reporters/DefaultReporter.h"
namespace ApprovalTests
{
    class Options
    {
    private:
        Scrubber scrubber_ = Scrubbers::doNothing;
        DefaultReporter defaultReporter;
        const Reporter& reporter_ = defaultReporter;

        Options(Scrubber scrubber, const Reporter& reporter)
            : scrubber_(scrubber), reporter_(reporter)
        {
        }

    public:
        Options()
        {
        }
        Options(Scrubber scrubber) : scrubber_(scrubber)
        {
        }
        Options(const Reporter& reporter) : reporter_(reporter)
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
            return reporter_;
        }
        Options withReporter(const Reporter& reporter) const
        {
            return Options(scrubber_, reporter);
        }
        Options withScrubber(Scrubber scrubber) const
        {
            return Options(scrubber, reporter_);
        }
    };
}