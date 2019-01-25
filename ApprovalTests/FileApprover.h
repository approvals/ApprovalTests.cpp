#ifndef FILEAPPROVER_H
#define FILEAPPROVER_H

#include <fstream>
#include "ApprovalException.h"
#include "StringWriter.h"
#include "reporters/Reporter.h"
#include "namers/ApprovalNamer.h"
#include "comparers/ApprovalComparer.h"
#include "comparers/TextFileComparer.h"
#include "FileUtils.h"

class FileApprover {
public:
    FileApprover() {};

    ~FileApprover() {};

    static std::unique_ptr<ApprovalComparer> getComparerForFile(string receivedPath) {
        return std::unique_ptr<ApprovalComparer>(new TextFileComparer());
    }

    static void verify(std::string receivedPath,
                       std::string approvedPath,
                       const ApprovalComparer& comparer) {
        int asize = FileUtils::fileSize(approvedPath);

        if (-1 == asize) {
            throw ApprovalMissingException(receivedPath, approvedPath);
        }

        int rsize = FileUtils::fileSize(receivedPath);

        if (-1 == rsize) {
            throw ApprovalMissingException(approvedPath, receivedPath);
        }

        if (!comparer.contentsAreEquivalent(receivedPath, approvedPath)) {
            throw ApprovalMismatchException(receivedPath, approvedPath);
        }
    }

    //! Verify that the contents of two text files are equivalent, ignoring any differences in line endings
    static void verify(std::string receivedPath,
                       std::string approvedPath) {
        verify(receivedPath, approvedPath, *getComparerForFile(receivedPath));
    }

    static void verify(ApprovalNamer& n, ApprovalWriter& s, const Reporter& r) {
        std::string approvedPath = n.getApprovedFile(s.GetFileExtension());
        std::string receivedPath = n.getReceivedFile(s.GetFileExtension());
        s.Write(receivedPath);
        try
        {
            verify(receivedPath, approvedPath);
            s.CleanUpReceived(receivedPath);
        }
        catch (const ApprovalException& exception) {
            r.Report(receivedPath, approvedPath);
            throw;
        }
    }


};

#endif