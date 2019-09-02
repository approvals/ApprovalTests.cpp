#ifndef APPROVALTESTS_CPP_EXISTINGFILENAMER_H
#define APPROVALTESTS_CPP_EXISTINGFILENAMER_H

#include <utility>
#include "ApprovalTests/core/ApprovalNamer.h"
#include "DefaultNamerFactory.h"

namespace ApprovalTests {
class ExistingFileNamer: public ApprovalNamer{
    std::string filePath;
public:
    explicit ExistingFileNamer(std::string filePath): filePath(std::move(filePath)){

    }
    virtual std::string getApprovedFile(std::string extensionWithDot) const override {
        return DefaultNamerFactory::getDefaultNamer()()->getApprovedFile(extensionWithDot);
    }
    virtual std::string getReceivedFile(std::string /*extensionWithDot*/) const override {
        return filePath;
    }

};
}

#endif //APPROVALTESTS_CPP_EXISTINGFILENAMER_H
