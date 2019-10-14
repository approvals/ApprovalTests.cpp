#ifndef APPROVALTESTS_CPP_FILEAPPROVER_H
#define APPROVALTESTS_CPP_FILEAPPROVER_H

#include <map>
#include <memory>
#include "ApprovalException.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "Reporter.h"
#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalComparator.h"
#include "ApprovalTests/comparators/TextFileComparator.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/Macros.h"

namespace ApprovalTests {

using ComparatorContainer = std::map< std::string, std::shared_ptr<ApprovalComparator> >;

class APPROVAL_TESTS_NO_DISCARD ComparatorDisposer
{
public:
    ComparatorDisposer(
            ComparatorContainer& comparators,
            std::string extensionWithDot,
            std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator)
            :
              comparators(comparators),
              ext_(extensionWithDot),
              previousComparator(previousComparator)
    {
    }

    ~ComparatorDisposer()
    {
        comparators[ext_] = previousComparator;
    }

private:
    ComparatorContainer& comparators;
    std::string ext_;
    std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator;
};

class ComparatorFactory
{
private:
    static ComparatorContainer& comparators()
    {
        static ComparatorContainer allComparators;
        return allComparators;
    }

public:
    static ComparatorDisposer registerComparator(const std::string& extensionWithDot, std::shared_ptr<ApprovalComparator> comparator)
    {
        ComparatorDisposer disposer(comparators(), extensionWithDot,
                                    getComparatorForFileExtensionWithDot(extensionWithDot));
        comparators()[extensionWithDot] = comparator;
        return disposer;
    }

    static std::shared_ptr<ApprovalComparator> getComparatorForFile(const std::string& receivedPath) {
        const std::string fileExtension = FileUtils::getExtensionWithDot(receivedPath);
        return getComparatorForFileExtensionWithDot(fileExtension);
    }

    static std::shared_ptr<ApprovalComparator> getComparatorForFileExtensionWithDot(const std::string &fileExtensionWithDot) {
        auto iterator = comparators().find(fileExtensionWithDot);
        if (iterator != comparators().end()) {
            return iterator->second;
        }
        return std::make_shared<TextFileComparator>();
    }
};

class FileApprover {

public:
    FileApprover() = default;

    ~FileApprover() = default;

    static ComparatorDisposer registerComparatorForExtension(const std::string& extensionWithDot, std::shared_ptr<ApprovalComparator> comparator)
    {
        return ComparatorFactory::registerComparator(extensionWithDot, comparator);
    }

    //! This overload is an implementation detail. To add a new comparator, use registerComparator().
    static void verify(const std::string& receivedPath,
                       const std::string& approvedPath,
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

    static void verify(const std::string& receivedPath,
                       const std::string& approvedPath) {
        verify(receivedPath, approvedPath, *ComparatorFactory::getComparatorForFile(receivedPath));
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