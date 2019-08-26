#ifndef APPROVALTESTS_CPP_SEPARATEAPPROVEDANDRECEIVEDDIRECTORIESNAMER_H
#define APPROVALTESTS_CPP_SEPARATEAPPROVEDANDRECEIVEDDIRECTORIESNAMER_H

#include "ApprovalTestNamer.h"
#include "../Approvals.h"
#include "Approvals.h"
#include "SystemUtils.h"

class SeparateApprovedAndReceivedDirectoriesNamer : public ApprovalTestNamer
{
public:
    virtual ~SeparateApprovedAndReceivedDirectoriesNamer() = default;

    std::string getFullFileNameWithExtraDirectory(std::string approved, std::string extensionWithDot)
    {
        std::string outputDirectory = getDirectory() +  approved;
        ApprovalTests::SystemUtils::ensureDirectoryExists(outputDirectory);
    
        std::string outputFile = getFileName() + "." + getTestName() + extensionWithDot;
    
        return outputDirectory + ApprovalTests::SystemUtils::getDirectorySeparator() + outputFile;
    }
    
    virtual std::string getApprovedFile(std::string extensionWithDot) override
    {
        return getFullFileNameWithExtraDirectory("approved", extensionWithDot);
    }
    
    virtual std::string getReceivedFile(std::string extensionWithDot) override
    {
        return getFullFileNameWithExtraDirectory("received", extensionWithDot);
    }
    
    static DefaultNamerDisposer useAsDefaultNamer()
    {
        return ApprovalTests::Approvals::useAsDefaultNamer([](){return std::make_shared<SeparateApprovedAndReceivedDirectoriesNamer>();});
    }

};

#endif // APPROVALTESTS_CPP_SEPARATEAPPROVEDANDRECEIVEDDIRECTORIESNAMER_H
