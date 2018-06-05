#ifndef APPROVALNAMER_H
#define APPROVALNAMER_H

#include <string>

using std::string;

class ApprovalNamer
{
public:
    virtual string getApprovedFile(string extentionWithDot) = 0;
    virtual string getReceivedFile(string extentionWithDot) = 0;

};

#endif
