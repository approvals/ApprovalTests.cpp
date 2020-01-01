#ifndef APPROVALTESTS_CPP_FILEAPPROVER_H
#define APPROVALTESTS_CPP_FILEAPPROVER_H

#include <memory>
#include "ApprovalException.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "Reporter.h"
#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalComparator.h"
#include "ApprovalTests/comparators/ComparatorFactory.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests
{

    class FileApprover
    {

    public:
        FileApprover() = default;

        ~FileApprover() = default;

        static ComparatorDisposer registerComparatorForExtension(
            const std::string& extensionWithDot,
            std::shared_ptr<ApprovalComparator> comparator)
        {
            return ComparatorFactory::registerComparator(extensionWithDot,
                                                         comparator);
        }

        //! This overload is an implementation detail. To add a new comparator, use registerComparator().
        static void verify(const std::string& receivedPath,
                           const std::string& approvedPath,
                           const ApprovalComparator& comparator)
        {
            if (!FileUtils::fileExists(approvedPath))
            {
                throw ApprovalMissingException(receivedPath, approvedPath);
            }

            if (!FileUtils::fileExists(receivedPath))
            {
                throw ApprovalMissingException(approvedPath, receivedPath);
            }

            if (!comparator.contentsAreEquivalent(receivedPath, approvedPath))
            {
                throw ApprovalMismatchException(receivedPath, approvedPath);
            }
        }

        static void verify(const std::string& receivedPath,
                           const std::string& approvedPath)
        {
            verify(receivedPath,
                   approvedPath,
                   *ComparatorFactory::getComparatorForFile(receivedPath));
        }

        static void verify(const ApprovalNamer& n,
                           const ApprovalWriter& s,
                           const Reporter& r)
        {
            std::string approvedPath =
                n.getApprovedFile(s.getFileExtensionWithDot());
            std::string receivedPath =
                n.getReceivedFile(s.getFileExtensionWithDot());
            s.write(receivedPath);
            try
            {
                verify(receivedPath, approvedPath);
                s.cleanUpReceived(receivedPath);
            }
            catch (const ApprovalException&)
            {
                reportAfterTryingFrontLoadedReporter(
                    receivedPath, approvedPath, r);
                throw;
            }
        }

        static void
        reportAfterTryingFrontLoadedReporter(const std::string& receivedPath,
                                             const std::string& approvedPath,
                                             const Reporter& r)
        {
            auto tryFirst =
                FrontLoadedReporterFactory::getFrontLoadedReporter();
            if (!tryFirst->report(receivedPath, approvedPath))
            {
                r.report(receivedPath, approvedPath);
            }
        }
    };
}

#endif