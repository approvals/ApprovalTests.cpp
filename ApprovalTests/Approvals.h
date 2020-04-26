#pragma once
#include <string>
#include <functional>
#include <exception>
#include <utility>

#include "ApprovalTests/ApprovalTestsVersion.h"
#include "ApprovalTests/core/FileApprover.h"
#include "reporters/DefaultReporter.h"
#include "reporters/DefaultReporterDisposer.h"
#include "ApprovalTests/core/Reporter.h"
#include "namers/ApprovalTestNamer.h"
#include "writers/ExistingFile.h"
#include "namers/ExistingFileNamer.h"
#include "namers/SubdirectoryDisposer.h"
#include "namers/DefaultNamerDisposer.h"
#include "scrubbers/Scrubbers.h"
#include "core/Options.h"
#include "utilities/MoreHelpMessages.h"

namespace ApprovalTests
{

    class Approvals
    {
    private:
        Approvals() = default;

        ~Approvals() = default;

    public:
        static std::shared_ptr<ApprovalNamer> getDefaultNamer()
        {
            return DefaultNamerFactory::getDefaultNamer()();
        }

        static void verify(const std::string& contents,
                           const Options& options = Options())
        {
            verifyWithExtension(contents, ".txt", options);
        }

        static void verifyWithExtension(const std::string& contents,
                                        const std::string& fileExtensionWithDot,
                                        const Options& options = Options())
        {
            StringWriter writer(options.scrub(contents), fileExtensionWithDot);
            FileApprover::verify(*getDefaultNamer(), writer, options.getReporter());
        }

        // Note that this overload ignores any scrubber in options
        static void verify(const ApprovalWriter& writer,
                           const Options& options = Options())
        {
            FileApprover::verify(*getDefaultNamer(), writer, options.getReporter());
        }

        template <typename T>
        using IsNotDerivedFromWriter =
            typename std::enable_if<!std::is_base_of<ApprovalWriter, T>::value,
                                    int>::type;

        template <typename T, typename = IsNotDerivedFromWriter<T>>
        static void verify(const T& contents, const Options& options = Options())
        {
            verify(StringUtils::toString(contents), options);
        }

        template <typename T, typename = IsNotDerivedFromWriter<T>>
        static void verifyWithExtension(const T& contents,
                                        const std::string& fileExtensionWithDot,
                                        const Options& options = Options())
        {
            verifyWithExtension(
                StringUtils::toString(contents), fileExtensionWithDot, options);
        }

        template <typename T,
                  typename Function,
                  typename = Detail::EnableIfNotDerivedFromReporter<Function>>
        static void
        verify(const T& contents, Function converter, const Options& options = Options())
        {
            std::stringstream s;
            converter(contents, s);
            verify(s.str(), options);
        }

        template <typename T,
                  typename Function,
                  typename = Detail::EnableIfNotDerivedFromReporter<Function>>
        static void verifyWithExtension(const T& contents,
                                        Function converter,
                                        const std::string& fileExtensionWithDot,
                                        const Options& options = Options())
        {
            std::stringstream s;
            converter(contents, s);
            verifyWithExtension(s.str(), fileExtensionWithDot, options);
        }

        static void
        verifyExceptionMessage(const std::function<void(void)>& functionThatThrows,
                               const Options& options = Options())
        {
            std::string message = "*** no exception thrown ***";
            try
            {
                functionThatThrows();
            }
            catch (const std::exception& e)
            {
                message = e.what();
            }
            verify(message, options);
        }

        template <typename Iterator>
        static void verifyAll(
            const std::string& header,
            const Iterator& start,
            const Iterator& finish,
            std::function<void(typename Iterator::value_type, std::ostream&)> converter,
            const Options& options = Options())
        {
            std::stringstream s;
            if (!header.empty())
            {
                s << header << "\n\n\n";
            }
            for (auto it = start; it != finish; ++it)
            {
                converter(*it, s);
                s << '\n';
            }
            verify(s.str(), options);
        }

        template <typename Container>
        static void verifyAll(
            std::string header,
            const Container& list,
            std::function<void(typename Container::value_type, std::ostream&)> converter,
            const Options& options = Options())
        {
            verifyAll<typename Container::const_iterator>(
                header, list.begin(), list.end(), converter, options);
        }

        template <typename T>
        static void verifyAll(const std::string& header,
                              const std::vector<T>& list,
                              const Options& options = Options())
        {
            int i = 0;
            verifyAll<std::vector<T>>(
                header,
                list,
                [&](T e, std::ostream& s) { s << "[" << i++ << "] = " << e; },
                options);
        }

        template <typename T>
        static void verifyAll(const std::vector<T>& list,
                              const Options& options = Options())
        {
            verifyAll<T>("", list, options);
        }

        // Note that this method ignores any scrubber in options
        static void verifyExistingFile(const std::string& filePath,
                                       const Options& options = Options())
        {
            ExistingFile writer(filePath);
            ExistingFileNamer namer(filePath);
            FileApprover::verify(namer, writer, options.getReporter());
        }

        static SubdirectoryDisposer
        useApprovalsSubdirectory(const std::string& subdirectory = "approval_tests")
        {
            return SubdirectoryDisposer(subdirectory);
        }

        static DefaultReporterDisposer
        useAsDefaultReporter(const std::shared_ptr<Reporter>& reporter)
        {
            return DefaultReporterDisposer(reporter);
        }

        static FrontLoadedReporterDisposer
        useAsFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter)
        {
            return FrontLoadedReporterDisposer(reporter);
        }

        static DefaultNamerDisposer useAsDefaultNamer(NamerCreator namerCreator)
        {
            return DefaultNamerDisposer(std::move(namerCreator));
        }

#ifndef APPROVAL_TESTS_HIDE_DEPRECATED_CODE

        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS
        static void verify(std::string contents, const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verify(contents, Options(reporter));
        }

        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS
        static void verifyWithExtension(std::string contents,
                                        const std::string& fileExtensionWithDot,
                                        const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyWithExtension(contents, fileExtensionWithDot, Options(reporter));
        }

        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS
        static void verify(const ApprovalWriter& writer, const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verify(writer, Options(reporter));
        }

        template <typename T, typename = IsNotDerivedFromWriter<T>>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS static void verify(const T& contents,
                                                                 const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verify(StringUtils::toString(contents), reporter);
        }

        template <typename T, typename = IsNotDerivedFromWriter<T>>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS static void
        verifyWithExtension(const T& contents,
                            const std::string& fileExtensionWithDot,
                            const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyWithExtension(contents, fileExtensionWithDot, Options(reporter));
        }

        template <typename T,
                  typename Function,
                  typename = Detail::EnableIfNotDerivedFromReporter<Function>>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS static void
        verify(const T& contents, Function converter, const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verify(contents, converter, Options(reporter));
        }

        template <typename T,
                  typename Function,
                  typename = Detail::EnableIfNotDerivedFromReporter<Function>>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS static void
        verifyWithExtension(const T& contents,
                            Function converter,
                            const std::string& fileExtensionWithDot,
                            const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyWithExtension(
                contents, converter, fileExtensionWithDot, Options(reporter));
        }

        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS
        static void verifyExceptionMessage(std::function<void(void)> functionThatThrows,
                                           const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyExceptionMessage(functionThatThrows, Options(reporter));
        }

        template <typename Iterator>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS static void verifyAll(
            std::string header,
            const Iterator& start,
            const Iterator& finish,
            std::function<void(typename Iterator::value_type, std::ostream&)> converter,
            const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyAll(header, start, finish, converter, Options(reporter));
        }

        template <typename Container>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS static void verifyAll(
            std::string header,
            const Container& list,
            std::function<void(typename Container::value_type, std::ostream&)> converter,
            const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyAll(header, list, converter, Options(reporter));
        }

        template <typename T>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS static void verifyAll(
            std::string header, const std::vector<T>& list, const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyAll(header, list, Options(reporter));
        }

        template <typename T>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS static void
        verifyAll(const std::vector<T>& list, const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyAll<T>(list, Options(reporter));
        }

        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS
        static void verifyExistingFile(const std::string filePath,
                                       const Reporter& reporter)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyExistingFile(filePath, Options(reporter));
        }
#endif
    };
}
