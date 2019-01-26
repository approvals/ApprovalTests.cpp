#ifndef FILEAPPROVER_H
#define FILEAPPROVER_H

#include <fstream>
#include <map>
#include <memory>
#include "ApprovalException.h"
#include "StringWriter.h"
#include "reporters/Reporter.h"
#include "namers/ApprovalNamer.h"
#include "comparators/ApprovalComparator.h"
#include "comparators/TextFileComparator.h"
#include "FileUtils.h"
#include "Macros.h"

class FileApprover {
private:
    using ComparatorContainer = std::map< std::string, std::shared_ptr<ApprovalComparator> >;
    STATIC(ComparatorContainer, comparators, new ComparatorContainer())

public:
    FileApprover() {};

    ~FileApprover() {};

    static void registerComparator(std::string extensionWithDot, ApprovalComparator* comparator)
    {
        comparators()[extensionWithDot] = std::shared_ptr<ApprovalComparator>(comparator);
    }

    static std::shared_ptr<ApprovalComparator> getComparatorForFile(string receivedPath) {
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

    static void verify(ApprovalNamer& n, ApprovalWriter& s, const Reporter& r) {
        std::string approvedPath = n.getApprovedFile(s.getFileExtension());
        std::string receivedPath = n.getReceivedFile(s.getFileExtension());
        s.write(receivedPath);
        try
        {
            verify(receivedPath, approvedPath);
            s.cleanUpReceived(receivedPath);
        }
        catch (const ApprovalException&) {
            r.report(receivedPath, approvedPath);
            throw;
        }
    }


};

#endif