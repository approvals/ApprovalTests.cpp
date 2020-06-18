#pragma once

#include <utility>
#include <exception>

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
            const Options* options_ = nullptr; // set in Options::fileOptions()
            std::string fileExtensionWithDot_ = ".txt";
            friend class Options;

            FileOptions() = default;

            explicit FileOptions(std::string fileExtensionWithDot)
                : fileExtensionWithDot_(std::move(fileExtensionWithDot))
            {
            }

            APPROVAL_TESTS_NO_DISCARD
            FileOptions clone() const
            {
                // the returned options_ must be null
                return FileOptions(fileExtensionWithDot_);
            }

        public:
            APPROVAL_TESTS_NO_DISCARD
            const std::string& getFileExtension() const
            {
                return fileExtensionWithDot_;
            }

            APPROVAL_TESTS_NO_DISCARD
            Options withFileExtension(const std::string& fileExtensionWithDot) const
            {
                FileOptions newSelf(fileExtensionWithDot);
                return options_->clone(newSelf);
            }
        };

    private:
        FileOptions fileOptions_;
        Scrubber scrubber_ = Scrubbers::doNothing;
        const Reporter& reporter_ = defaultReporter();
        bool usingDefaultScrubber_ = true;

        Options(FileOptions fileOptions,
                Scrubber scrubber,
                const Reporter& reporter,
                bool usingDefaultScrubber)
            : fileOptions_(std::move(fileOptions))
            , scrubber_(std::move(scrubber))
            , reporter_(reporter)
            , usingDefaultScrubber_(usingDefaultScrubber)
        {
        }

        APPROVAL_TESTS_NO_DISCARD
        Options clone(const FileOptions& fileOptions) const
        {
            // TODO error this can retain a previous Options* ???
            return Options(fileOptions, scrubber_, reporter_, usingDefaultScrubber_);
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
            usingDefaultScrubber_ = false;
        }

        explicit Options(const Reporter& reporter) : reporter_(reporter)
        {
        }

        APPROVAL_TESTS_NO_DISCARD
        FileOptions fileOptions() const
        {
            if (fileOptions_.options_ != nullptr)
            {
                throw std::logic_error(
                    "Incorrect assumption: A FileOptions has been re-used");
            }
            FileOptions copy = fileOptions_.clone();
            copy.options_ = this;
            return copy;
        }

        APPROVAL_TESTS_NO_DISCARD
        Scrubber getScrubber() const
        {
            return scrubber_;
        }

        APPROVAL_TESTS_NO_DISCARD
        bool isUsingDefaultScrubber() const
        {
            return usingDefaultScrubber_;
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
            return Options(fileOptions_, scrubber_, reporter, usingDefaultScrubber_);
        }

        APPROVAL_TESTS_NO_DISCARD
        Options withScrubber(Scrubber scrubber) const
        {
            return Options(fileOptions_, std::move(scrubber), reporter_, false);
        }
    };

    namespace Detail
    {
        //! Helper to prevent compilation failure when types are wrongly treated as Options
        template <typename T, typename R = void>
        using EnableIfNotOptions = typename std::enable_if<
            (!std::is_same<Options, typename std::decay<T>::type>::value),
            R>::type;
    } // namespace Detail
}
