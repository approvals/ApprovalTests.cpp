#include "ApprovalTests/core/ApprovalException.h"

#include <sstream>

namespace ApprovalTests
{
    ApprovalException::ApprovalException(const std::string& msg) : message(msg)
    {
    }

    const char* ApprovalException::what() const noexcept
    {
        return message.c_str();
    }

    std::string ApprovalMismatchException::format(const std::string& received,
                                                  const std::string& approved)
    {
        std::stringstream s;
        s << "Failed Approval: \n"
          << "Received does not match approved \n"
          << "Received : \"" << received << "\" \n"
          << "Approved : \"" << approved << "\"";
        return s.str();
    }

    ApprovalMismatchException::ApprovalMismatchException(const std::string& received,
                                                         const std::string& approved)
        : ApprovalException(format(received, approved))
    {
    }

    std::string ApprovalMissingException::format(const std::string& file)
    {
        std::stringstream s;
        s << "Failed Approval: \n"
          << "Approval File Not Found \n"
          << "File: \"" << file << '"';
        return s.str();
    }

    ApprovalMissingException::ApprovalMissingException(const std::string&,
                                                       const std::string& approved)
        : ApprovalException(format(approved))
    {
    }
}
