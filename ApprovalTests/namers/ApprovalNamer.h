#ifndef APPROVALNAMER_H
#define APPROVALNAMER_H

#include <string>

using std::string;

class ApprovalNamer
{
public:
    virtual string getApprovedFile(string extensionWithDot) = 0;
    virtual string getReceivedFile(string extensionWithDot) = 0;

};

#endif
