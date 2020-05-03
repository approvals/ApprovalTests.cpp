#pragma once

namespace ApprovalTests
{
    /*! \brief Write the object being verified to file.

     \see For more information, see
     \userguide{Writers,Writers}
     */
    class ApprovalWriter
    {
    public:
        virtual ~ApprovalWriter() = default;
        virtual std::string getFileExtensionWithDot() const = 0;
        virtual void write(std::string path) const = 0;
        virtual void cleanUpReceived(std::string receivedPath) const = 0;
    };
}
