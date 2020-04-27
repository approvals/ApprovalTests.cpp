#pragma once
#include "scrubbers/Scrubbers.h"
#include "core/Reporter.h"
#include "reporters/DefaultReporter.h"

namespace ApprovalTests
{
    class Options
    {
    private:
        std::string fileExtensionWithDot_ = ".txt";
        Scrubber scrubber_ = Scrubbers::doNothing;
        const Reporter& reporter_ = defaultReporter();

        Options(std::string fileExtensionWithDot,
                Scrubber scrubber,
                const Reporter& reporter)
            : fileExtensionWithDot_(std::move(fileExtensionWithDot))
            , scrubber_(std::move(scrubber))
            , reporter_(reporter)
        {
        }

        static const Reporter& defaultReporter()
        {
            static DefaultReporter defaultReporter;
            return defaultReporter;
        }

    public:
        Options() = default;

        explicit Options(Scrubber scrubber) : scrubber_(std::move(scrubber))
        {
        }

        explicit Options(const Reporter& reporter) : reporter_(reporter)
        {
        }

        APPROVAL_TESTS_NO_DISCARD
        const std::string& getFileExtension() const
        {
            return fileExtensionWithDot_;
        }

        APPROVAL_TESTS_NO_DISCARD
        Scrubber getScrubber() const
        {
            return scrubber_;
        }

        APPROVAL_TESTS_NO_DISCARD
        std::string scrub(const std::string& input) const
        {
            return scrubber_(input);
        }

        APPROVAL_TESTS_NO_DISCARD
        const Reporter& getReporter() const
        {
            return reporter_;
        }

        APPROVAL_TESTS_NO_DISCARD
        Options withFileExtension(const std::string& fileExtensionWithDot) const
        {
            return Options(fileExtensionWithDot, scrubber_, reporter_);
        }

        APPROVAL_TESTS_NO_DISCARD
        Options withReporter(const Reporter& reporter) const
        {
            return Options(fileExtensionWithDot_, scrubber_, reporter);
        }

        APPROVAL_TESTS_NO_DISCARD
        Options withScrubber(Scrubber scrubber) const
        {
            return Options(fileExtensionWithDot_, std::move(scrubber), reporter_);
        }
    };

    namespace Detail
    {
        //! Helper to prevent compilation failure when types are wrongly treated as Option
        //  or Reporter:
        template <typename T, typename R = void>
        using EnableIfNotOptionsOrReporter = typename std::enable_if<
            (!std::is_same<Options, typename std::decay<T>::type>::value) &&
                (!std::is_base_of<Reporter, typename std::decay<T>::type>::value),
            R>::type;
    } // namespace Detail
}