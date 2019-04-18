#ifndef APPROVALTESTS_CPP_APPROVALNAMER_H
#define APPROVALTESTS_CPP_APPROVALNAMER_H

#include <string>

using std::string;

class ApprovalNamer
{
public:
    virtual ~ApprovalNamer() = default;
    virtual string getApprovedFile(string extensionWithDot) = 0;
    virtual string getReceivedFile(string extensionWithDot) = 0;

};

#endif
