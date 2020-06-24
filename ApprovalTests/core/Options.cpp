#include "ApprovalTests/core/Options.h"

namespace ApprovalTests
{
    // FileOptions -----------------------------------------------------------------------
    Options::FileOptions::FileOptions(std::string fileExtensionWithDot)
        : fileExtensionWithDot_(std::move(fileExtensionWithDot))
    {
    }

    Options::FileOptions Options::FileOptions::clone() const
    {
        // the returned options_ must be null
        return FileOptions(fileExtensionWithDot_);
    }

    const std::string& Options::FileOptions::getFileExtension() const
    {
        return fileExtensionWithDot_;
    }

    Options
    Options::FileOptions::withFileExtension(const std::string& fileExtensionWithDot) const
    {
        FileOptions newSelf(fileExtensionWithDot);
        return options_->clone(newSelf);
    }

    // Options ---------------------------------------------------------------------------
    Options::Options(Options::FileOptions fileOptions,
                     Scrubber scrubber,
                     const Reporter& reporter,
                     bool usingDefaultScrubber)
        : fileOptions_(std::move(fileOptions))
        , scrubber_(std::move(scrubber))
        , reporter_(reporter)
        , usingDefaultScrubber_(usingDefaultScrubber)
    {
    }

    Options Options::clone(const Options::FileOptions& fileOptions) const
    {
        // TODO error this can retain a previous Options* ???
        return Options(fileOptions, scrubber_, reporter_, usingDefaultScrubber_);
    }

    const Reporter& Options::defaultReporter()
    {
        static DefaultReporter defaultReporter;
        return defaultReporter;
    }

    Options::Options(Scrubber scrubber) : scrubber_(std::move(scrubber))
    {
        usingDefaultScrubber_ = false;
    }

    Options::Options(const Reporter& reporter) : reporter_(reporter)
    {
    }

    Options::FileOptions Options::fileOptions() const
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

    Scrubber Options::getScrubber() const
    {
        return scrubber_;
    }

    bool Options::isUsingDefaultScrubber() const
    {
        return usingDefaultScrubber_;
    }

    std::string Options::scrub(const std::string& input) const
    {
        return scrubber_(input);
    }
    const Reporter& Options::getReporter() const
    {
        return reporter_;
    }

    Options Options::withReporter(const Reporter& reporter) const
    {
        return Options(fileOptions_, scrubber_, reporter, usingDefaultScrubber_);
    }

    Options Options::withScrubber(Scrubber scrubber) const
    {
        return Options(fileOptions_, std::move(scrubber), reporter_, false);
    }
}
