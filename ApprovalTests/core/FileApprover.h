#ifndef APPROVALTESTS_CPP_FILEAPPROVER_H
#define APPROVALTESTS_CPP_FILEAPPROVER_H

#include <fstream>
#include <map>
#include <memory>
#include "ApprovalException.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/reporters/Reporter.h"
#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalComparator.h"
#include "ApprovalTests/comparators/TextFileComparator.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/Macros.h"

namespace ApprovalTests {
class FileApprover {
private:
    using ComparatorContainer = std::map< std::string, std::shared_ptr<ApprovalComparator> >;
    APPROVAL_TESTS_MACROS_STATIC(ComparatorContainer, comparators, new ComparatorContainer())

public:
    FileApprover() = default;

    ~FileApprover() = default;

    static void registerComparator(std::string extensionWithDot, std::shared_ptr<ApprovalComparator> comparator)
    {
        comparators()[extensionWithDot] = comparator;
    }

    static std::shared_ptr<ApprovalComparator> getComparatorForFile(std::string receivedPath) {
        const std::string fileExtension = FileUtils::getExtensionWithDot(receivedPath);
        auto iterator = comparators().find(fileExtension);
        if (iterator != comparators().end()) {
            return iterator->second;
        }
        return std::make_shared<TextFileComparator>();
    }

    //! This overload is an implementation detail. To add a new comparator, use registerComparator().
    static void verify(std::string receivedPath,
                       std::string approvedPath,
                       const ApprovalComparator& comparator) {
        if (!FileUtils::fileExists(approvedPath)) {
            throw ApprovalMissingException(receivedPath, approvedPath);
        }

        if (!FileUtils::fileExists(receivedPath)) {
            throw ApprovalMissingException(approvedPath, receivedPath);
        }

        if (!comparator.contentsAreEquivalent(receivedPath, approvedPath)) {
            throw ApprovalMismatchException(receivedPath, approvedPath);
        }
    }

    static void verify(std::string receivedPath,
                       std::string approvedPath) {
        verify(receivedPath, approvedPath, *getComparatorForFile(receivedPath));
    }

    static void verify(const ApprovalNamer& n, const ApprovalWriter& s, const Reporter& r) {
        std::string approvedPath = n.getApprovedFile(s.getFileExtensionWithDot());
        std::string receivedPath = n.getReceivedFile(s.getFileExtensionWithDot());
        s.write(receivedPath);
        try
        {
            verify(receivedPath, approvedPath);
            s.cleanUpReceived(receivedPath);
        }
        catch (const ApprovalException&) {
            reportAfterTryingFrontLoadedReporter(receivedPath, approvedPath, r);
            throw;
        }
    }

    static void
    reportAfterTryingFrontLoadedReporter(const std::string &receivedPath, const std::string &approvedPath, const Reporter &r)
    {
        auto tryFirst = FrontLoadedReporterFactory::getFrontLoadedReporter();
        if (!tryFirst->report(receivedPath, approvedPath))
        {
            r.report(receivedPath, approvedPath);
        }
    }


};
}

#endif