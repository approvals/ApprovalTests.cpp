#ifndef APPROVALTESTS_CPP_APPROVALWRITER_H
#define APPROVALTESTS_CPP_APPROVALWRITER_H

namespace ApprovalTests {
class ApprovalWriter
{
public:
    virtual ~ApprovalWriter() = default;
    virtual std::string getFileExtensionWithDot() const = 0;
    virtual void write(std::string path) const = 0;
    virtual void cleanUpReceived(std::string receivedPath) const = 0;
};
}

#endif //APPROVALTESTS_CPP_APPROVALWRITER_H
