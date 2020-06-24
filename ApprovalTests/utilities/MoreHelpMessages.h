#pragma once

#include <string>
#include <iostream>
#include "ApprovalTests/namers/ApprovalTestNamer.h"

namespace ApprovalTests
{
    class MoreHelpMessages
    {
    public:
        static void deprecatedFunctionCalled(const std::string& message,
                                             const std::string& file,
                                             int lineNumber)
        {
            std::cout << "\n***************** Deprecation Warning: ***************\n"
                      << "*\n"
                      << "* " << message << '\n'
                      << "*\n"
                      << "* Deprecated method:\n"
                      << "*    " << file << ":" << lineNumber << '\n'
                      << "* Called from:\n"
                      << "*    " << ApprovalTestNamer::getCurrentTest().getFileName()
                      << '\n'
                      << "*\n"
                      << "******************************************************\n\n";
        }
    };
}
