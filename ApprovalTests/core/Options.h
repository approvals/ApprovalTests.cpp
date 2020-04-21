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

    namespace Detail
    {
        //! Helper to prevent compilation failure when types are wrongly treated as Option:
        template <typename T, typename R = void>
        using EnableIfNotOptions = typename std::enable_if<
            !std::is_same<Options, typename std::decay<T>::type>::value,
            R>::type;

        //! Helper to prevent compilation failure when types are wrongly treated as Option
        //  or Reporter:
        template <typename T, typename R = void>
        using EnableIfNotOptionsOrReporter = typename std::enable_if<
            (!std::is_same<Options, typename std::decay<T>::type>::value) &&
                (!std::is_base_of<Reporter, typename std::decay<T>::type>::value),
            R>::type;
    } // namespace Detail
}