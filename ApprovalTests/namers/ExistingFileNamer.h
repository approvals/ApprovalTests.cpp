#ifndef APPROVALTESTS_CPP_EXISTINGFILENAMER_H
#define APPROVALTESTS_CPP_EXISTINGFILENAMER_H

#include "ApprovalNamer.h"
#include "ApprovalTestNamer.h"

class ExistingFileNamer: public ApprovalNamer{
    ApprovalTestNamer namer;
    std::string filePath;
public:
    ExistingFileNamer(std::string filePath): filePath(filePath){

    }
    virtual string getApprovedFile(string extensionWithDot) {
        return namer.getApprovedFile(extensionWithDot);
    }
    virtual string getReceivedFile(string extensionWithDot) {
        return filePath;
    }

};

#endif //APPROVALTESTS_CPP_EXISTINGFILENAMER_H
