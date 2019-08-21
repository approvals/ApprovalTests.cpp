#ifndef APPROVALTESTS_CPP_EXISTINGFILENAMER_H
#define APPROVALTESTS_CPP_EXISTINGFILENAMER_H

#include "ApprovalNamer.h"
#include "DefaultNamerFactory.h"

class ExistingFileNamer: public ApprovalNamer{
    std::string filePath;
public:
    ExistingFileNamer(std::string filePath): filePath(filePath){

    }
    virtual std::string getApprovedFile(std::string extensionWithDot) {
        return DefaultNamerFactory::getDefaultNamer()()->getApprovedFile(extensionWithDot);
    }
    virtual std::string getReceivedFile(std::string /*extensionWithDot*/) {
        return filePath;
    }

};

#endif //APPROVALTESTS_CPP_EXISTINGFILENAMER_H
