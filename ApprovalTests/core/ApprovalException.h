#pragma once

#include <exception>
#include <string>
#include <sstream>

namespace ApprovalTests
{
    //! Base class for ApprovalTest-specific exceptions
    class ApprovalException : public std::exception
    {
    private:
        std::string message;

    public:
        explicit ApprovalException(const std::string& msg) : message(msg)
        {
        }

        virtual const char* what() const noexcept override
        {
            return message.c_str();
        }
    };

    //! Exception that is thrown if received and approved files differ
    class ApprovalMismatchException : public ApprovalException
    {
    private:
        std::string format(const std::string& received, const std::string& approved)
        {
            std::stringstream s;
            s << "Failed Approval: \n"
              << "Received does not match approved \n"
              << "Received : \"" << received << "\" \n"
              << "Approved : \"" << approved << "\"";
            return s.str();
        }

    public:
        ApprovalMismatchException(const std::string& received,
                                  const std::string& approved)
            : ApprovalException(format(received, approved))
        {
        }
    };

    //! Exception that is thrown if the approved file is missing - typically on first run of a new test.
    class ApprovalMissingException : public ApprovalException
    {
    private:
        std::string format(const std::string& file)
        {
            std::stringstream s;
            s << "Failed Approval: \n"
              << "Approval File Not Found \n"
              << "File: \"" << file << '"';
            return s.str();
        }

    public:
        ApprovalMissingException(const std::string& /*received*/,
                                 const std::string& approved)
            : ApprovalException(format(approved))
        {
        }
    };
}
