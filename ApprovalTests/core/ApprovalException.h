#pragma once

#include <exception>
#include <string>
#include <sstream>

namespace ApprovalTests
{
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
