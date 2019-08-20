#ifndef APPROVALTESTS_CPP_SEPARATEAPPROVEDANDRECEIVEDDIRECTORIESNAMER_H
#define APPROVALTESTS_CPP_SEPARATEAPPROVEDANDRECEIVEDDIRECTORIESNAMER_H

#include "ApprovalTestNamer.h"
#include "../Approvals.h"

class SeparateApprovedAndReceivedDirectoriesNamer : public ApprovalTestNamer
{
public:
    virtual ~SeparateApprovedAndReceivedDirectoriesNamer() = default;

    std::string getFullFileNameWithExtraDirectory(string approved, string extensionWithDot)
    {
        std::string outputDirectory = getDirectory() +  approved;
        SystemUtils::ensureDirectoryExists(outputDirectory);
    
        std::string outputFile = getFileName() + "." + getTestName() + extensionWithDot;
    
        return outputDirectory + SystemUtils::getDirectorySeparator() + outputFile;
    }
    
    virtual std::string getApprovedFile(string extensionWithDot) override
    {
        return getFullFileNameWithExtraDirectory("approved", extensionWithDot);
    }
    
    virtual std::string getReceivedFile(string extensionWithDot) override
    {
        return getFullFileNameWithExtraDirectory("received", extensionWithDot);
    }
    
    static DefaultNamerDisposer useAsDefaultNamer()
    {
        return Approvals::useAsDefaultNamer([](){return std::make_shared<SeparateApprovedAndReceivedDirectoriesNamer>();});
    }

};

#endif // APPROVALTESTS_CPP_SEPARATEAPPROVEDANDRECEIVEDDIRECTORIESNAMER_H
