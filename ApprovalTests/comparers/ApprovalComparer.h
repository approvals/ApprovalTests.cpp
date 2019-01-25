#ifndef APPROVALTESTS_CPP_APPROVALCOMPARER_H
#define APPROVALTESTS_CPP_APPROVALCOMPARER_H

#include <string>

class ApprovalComparer
{
public:
    virtual bool contentsAreEquivalent(std::string receivedPath,
                                       std::string approvedPath) const = 0;
};

#endif //APPROVALTESTS_CPP_APPROVALCOMPARER_H
