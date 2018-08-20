#ifndef FILEAPPROVER_H
#define FILEAPPROVER_H

#include <fstream>
#include "ApprovalException.h"
#include "StringWriter.h"
#include "reporters/Reporter.h"
#include "namers/ApprovalNamer.h"
#include "FileUtils.h"

class FileApprover {
public:
    FileApprover() {};

    ~FileApprover() {};

	static std::ifstream::int_type getNextRelevantCharacter(std::ifstream& astream)
	{
		auto ch = astream.get();
		if (ch == '\r')
		{
			return astream.get();
		}
		else
		{
			return ch;
		}
	}

    static ApprovalException *verify(std::string receivedPath,
                                     std::string approvedPath) {
        int asize = FileUtils::fileSize(approvedPath);

        if (-1 == asize) {
            return new ApprovalMissingException(receivedPath, approvedPath);
        }

        int rsize = FileUtils::fileSize(receivedPath);

        if (-1 == rsize) {
            return new ApprovalMissingException(approvedPath, receivedPath);
        }

        std::ifstream astream(approvedPath.c_str(),
                              std::ios::binary | std::ifstream::in);
        std::ifstream rstream(receivedPath.c_str(),
                              std::ios::binary | std::ifstream::in);

        while (astream.good() && rstream.good()) {
            int a = getNextRelevantCharacter(astream);
            int r = getNextRelevantCharacter(rstream);

            if (a != r) {
                return new ApprovalMismatchException(receivedPath, approvedPath);
            }
        }
        return NULL;
    }


    static void verify(ApprovalNamer& n, ApprovalWriter& s, const Reporter& r) {
        std::string approvedPath = n.getApprovedFile(s.GetFileExtension());
        std::string receivedPath = n.getReceivedFile(s.GetFileExtension());
        s.Write(receivedPath);
        ApprovalException *ae = verify(receivedPath, approvedPath);

        if (ae != NULL) {
            r.Report(receivedPath, approvedPath);
            ApprovalException e(*ae);
            delete ae;
            throw e;
        } else {
            s.CleanUpReceived(receivedPath);
        }
    }


};

#endif