#ifndef APPROVALTESTS_CPP_EXISTINGFILE_H
#define APPROVALTESTS_CPP_EXISTINGFILE_H


#include <string>
#include "../ApprovalWriter.h"
#include "../FileUtils.h"

class ExistingFile : public ApprovalWriter{
    std::string filePath;
public:
    ExistingFile(std::string filePath) : filePath(filePath){}
    virtual std::string GetFileExtension(){
        return FileUtils::getExtensionWithDot(filePath);
    }
    virtual void Write(std::string path) {
        // do nothing
    }
    virtual void CleanUpReceived(std::string receivedPath){
        // do nothing
    }
};
#endif
