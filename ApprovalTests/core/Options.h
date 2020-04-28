#pragma once

#include <utility>

#include "scrubbers/Scrubbers.h"
#include "core/Reporter.h"
#include "reporters/DefaultReporter.h"

namespace ApprovalTests
{
    class Options
    {
    public:
        class FileOptions
        {
            mutable const Options* options_ = nullptr; // set in Options::fileOptions()
            std::string fileExtensionWithDot_ = ".txt";
            friend class Options;

        public:
            FileOptions() = default;
            explicit FileOptions(std::string fileExtensionWithDot)
                : fileExtensionWithDot_(std::move(fileExtensionWithDot))
            {
            }

            APPROVAL_TESTS_NO_DISCARD
            const std::string& getFileExtension() const
            {
                return fileExtensionWithDot_;
            }

            APPROVAL_TESTS_NO_DISCARD
            Options withFileExtension(const std::string& fileExtensionWithDot) const
            {
                // Copy ourselves - and change the value
                FileOptions newSelf(fileExtensionWithDot);
                // Copy the previous options object - supplying the new copy of ourself
                // Return the new Options object
                return options_->clone(newSelf);
            }
        };

    private:
        FileOptions fileOptions_;
        Scrubber scrubber_ = Scrubbers::doNothing;
        const Reporter& reporter_ = defaultReporter();

        Options(FileOptions fileOptions, Scrubber scrubber, const Reporter& reporter)
            : fileOptions_(std::move(fileOptions))
            , scrubber_(std::move(scrubber))
            , reporter_(reporter)
        {
        }

        Options clone(const FileOptions& fileOptions) const
        {
            return Options(fileOptions, scrubber_, reporter_);
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
        const FileOptions& fileOptions() const
        {
            fileOptions_.options_ = this;
            return fileOptions_;
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
        Options withReporter(const Reporter& reporter) const
        {
            return Options(fileOptions_, scrubber_, reporter);
        }

        APPROVAL_TESTS_NO_DISCARD
        Options withScrubber(Scrubber scrubber) const
        {
            return Options(fileOptions_, std::move(scrubber), reporter_);
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