#ifndef APPROVALTESTS_CPP_EXISTINGFILE_H
#define APPROVALTESTS_CPP_EXISTINGFILE_H


#include <string>
#include "ApprovalTests/core/ApprovalWriter.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests {
class ExistingFile : public ApprovalWriter{
    std::string filePath;
public:
    ExistingFile(std::string filePath) : filePath(filePath){}
    virtual std::string getFileExtensionWithDot() const override {
        return FileUtils::getExtensionWithDot(filePath);
    }
    virtual void write(std::string /*path*/) const override {
        // do nothing
    }
    virtual void cleanUpReceived(std::string /*receivedPath*/) const override {
        // do nothing
    }
};
}

#endif
