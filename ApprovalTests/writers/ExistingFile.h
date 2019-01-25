#ifndef APPROVALTESTS_CPP_EXISTINGFILE_H
#define APPROVALTESTS_CPP_EXISTINGFILE_H


#include <string>
#include "../ApprovalWriter.h"
#include "../FileUtils.h"

class ExistingFile : public ApprovalWriter{
    std::string filePath;
public:
    ExistingFile(std::string filePath) : filePath(filePath){}
    virtual std::string getFileExtension() override {
        return FileUtils::getExtensionWithDot(filePath);
    }
    virtual void write(std::string path) override {
        // do nothing
    }
    virtual void cleanUpReceived(std::string receivedPath) override {
        // do nothing
    }
};
#endif
