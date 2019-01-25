#ifndef FILEAPPROVER_H
#define FILEAPPROVER_H

#include <fstream>
#include <map>
#include "ApprovalException.h"
#include "StringWriter.h"
#include "reporters/Reporter.h"
#include "namers/ApprovalNamer.h"
#include "comparers/ApprovalComparator.h"
#include "comparers/TextFileComparator.h"
#include "FileUtils.h"
#include "Macros.h"

class FileApprover {
private:
    using ComparerContainer = std::map< std::string, ApprovalComparator >;
    STATIC(ComparerContainer, comparators, new ComparerContainer())

public:
    FileApprover() {};

    ~FileApprover() {};

    static void registerComparator(std::string extensionWithDot, ApprovalComparator comparator)
    {
        comparators()[extensionWithDot] = comparator;
    }

    static ApprovalComparator getComparerForFile(string receivedPath) {
        const std::string fileExtension = FileUtils::getExtensionWithDot(receivedPath);
        if (comparators().find(fileExtension) != comparators().end()) {
            return comparators()[fileExtension];
        }
        return TextFileComparator::getComparator();
    }

    static void verify(std::string receivedPath,
                       std::string approvedPath,
                       const ApprovalComparator& comparator) {
        if (!FileUtils::fileExists(approvedPath)) {
            throw ApprovalMissingException(receivedPath, approvedPath);
        }

        if (!FileUtils::fileExists(receivedPath)) {
            throw ApprovalMissingException(approvedPath, receivedPath);
        }

        if (!comparator(receivedPath, approvedPath)) {
            throw ApprovalMismatchException(receivedPath, approvedPath);
        }
    }

    static void verify(std::string receivedPath,
                       std::string approvedPath) {
        verify(receivedPath, approvedPath, getComparerForFile(receivedPath));
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