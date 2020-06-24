#include "ApprovalTests/core/FileApprover.h"

namespace ApprovalTests
{

    ComparatorDisposer FileApprover::registerComparatorForExtension(
        const std::string& extensionWithDot,
        std::shared_ptr<ApprovalComparator> comparator)
    {
        return ComparatorFactory::registerComparator(extensionWithDot, comparator);
    }

    void FileApprover::verify(const std::string& receivedPath,
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
        s.write(receivedPath);
        try
        {
            verify(receivedPath, approvedPath);
            s.cleanUpReceived(receivedPath);
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
}
