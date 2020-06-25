#pragma once

#include <exception>
#include <string>

namespace ApprovalTests
{
    class ApprovalException : public std::exception
    {
    private:
        std::string message;

    public:
        explicit ApprovalException(const std::string& msg);

        virtual const char* what() const noexcept override;
    };

    class ApprovalMismatchException : public ApprovalException
    {
    private:
        std::string format(const std::string& received, const std::string& approved);

    public:
        ApprovalMismatchException(const std::string& received,
                                  const std::string& approved);
    };

    class ApprovalMissingException : public ApprovalException
    {
    private:
        std::string format(const std::string& file);

    public:
        ApprovalMissingException(const std::string& /*received*/,
                                 const std::string& approved);
    };
}
