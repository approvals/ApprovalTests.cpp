#include "ApprovalTests/utilities/MoreHelpMessages.h"

#include <iostream>

namespace ApprovalTests
{
    void MoreHelpMessages::deprecatedFunctionCalled(const std::string& message,
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
                  << "*    " << ApprovalTestNamer::getCurrentTest().getFileName() << '\n'
                  << "*\n"
                  << "******************************************************\n\n";
    }
}
