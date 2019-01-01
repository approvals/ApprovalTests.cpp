#ifndef APPROVALTESTS_CPP_APPROVALWRITER_H
#define APPROVALTESTS_CPP_APPROVALWRITER_H

class ApprovalWriter
{
public:
    virtual std::string GetFileExtension() = 0;
    virtual void Write(std::string path) = 0;
    virtual void CleanUpReceived(std::string receivedPath) = 0;
};

#endif //APPROVALTESTS_CPP_APPROVALWRITER_H
