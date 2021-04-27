#include "ApprovalTests/core/FileApprover.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/reporters/FrontLoadedReporterFactory.h"
#include "ApprovalException.h"

#include <sstream>

namespace ApprovalTests
{

    ComparatorDisposer FileApprover::registerComparatorForExtension(
        const std::string& extensionWithDot,
        std::shared_ptr<ApprovalComparator> comparator)
    {
        return ComparatorFactory::registerComparator(extensionWithDot, comparator);
    }

    FileApprover::TestPassedNotification FileApprover::testPassedNotification_ = []() {};

    void FileApprover::verify(const std::string& receivedPath,
                              const std::string& approvedPath,
                              const ApprovalComparator& comparator)
    {
        if (receivedPath == approvedPath)
        {
            std::stringstream s;
            s << "Identical filenames for received and approved.\n"
              << "Tests would spuriously pass. \n"
              << "Please check your custom namer. \n"
              << "Received : \"" << receivedPath << "\" \n"
              << "Approved : \"" << approvedPath << "\"";
            // Do not throw ApprovalException, as we don't want reporters to trigger.
            // They would show two seemingly identical files, due to matching file name.
            throw std::runtime_error(s.str());
        }

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

    void FileApprover::verify(const std::string& receivedPath,
                              const std::string& approvedPath)
    {
        verify(receivedPath,
               approvedPath,
               *ComparatorFactory::getComparatorForFile(receivedPath));
    }

    void FileApprover::verify(const ApprovalNamer& n,
                              const ApprovalWriter& s,
                              const Reporter& r)
    {
        std::string approvedPath = n.getApprovedFile(s.getFileExtensionWithDot());
        std::string receivedPath = n.getReceivedFile(s.getFileExtensionWithDot());
        SystemUtils::ensureParentDirectoryExists(approvedPath);
        SystemUtils::ensureParentDirectoryExists(receivedPath);
        s.write(receivedPath);
        try
        {
            verify(receivedPath, approvedPath);
            s.cleanUpReceived(receivedPath);
            notifyTestPassed();
        }
        catch (const ApprovalException&)
        {
            reportAfterTryingFrontLoadedReporter(receivedPath, approvedPath, r);
            throw;
        }
    }

    void
    FileApprover::reportAfterTryingFrontLoadedReporter(const std::string& receivedPath,
                                                       const std::string& approvedPath,
                                                       const Reporter& r)
    {
        auto tryFirst = FrontLoadedReporterFactory::getFrontLoadedReporter();
        if (!tryFirst->report(receivedPath, approvedPath))
        {
            r.report(receivedPath, approvedPath);
        }
    }

    void FileApprover::setTestPassedNotification(
        FileApprover::TestPassedNotification notification)
    {
        testPassedNotification_ = notification;
    }

    void FileApprover::notifyTestPassed()
    {
        testPassedNotification_();
    }
}
