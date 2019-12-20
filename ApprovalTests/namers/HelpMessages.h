#ifndef APPROVALTESTS_CPP_HELPMESSAGES_H
#define APPROVALTESTS_CPP_HELPMESSAGES_H

#include <string>
#include "ApprovalTests/utilities/StringUtils.h"

// <SingleHpp unalterable>
namespace ApprovalTests {
    class HelpMessages {
    public:

        static std::string getMisconfiguredBuildHelp(const std::string& fileName)
        {
            std::string lineBreak = "************************************************************************************\n";
            std::string lineBuffer = "*                                                                                  *\n";
            std::string helpMessage =
                    "\n\n" + lineBreak + lineBuffer +
                    R"(* Welcome to Approval Tests.
*
* There seems to be a problem with your build configuration.
* We cannot find the test source file at:
*   [fileName]
*
* For details on how to fix this, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md
)" +
                    lineBuffer + lineBreak + '\n';
            return StringUtils::replaceAll(helpMessage, "[fileName]", fileName);
        }
        static std::string getMisconfiguredMainHelp()
        {
            std::string lineBreak = "************************************************************************************\n";
            std::string lineBuffer = "*                                                                                  *\n";
            std::string helpMessage =
                    "\n\n" + lineBreak + lineBuffer +
                    R"(* Welcome to Approval Tests.
*
* You have forgotten to configure your test framework for Approval Tests.
*
* To do this in Catch, add the following to your main.cpp:
*
*     #define APPROVALS_CATCH
*     #include "ApprovalTests.hpp"
*
* To do this in Google Test, add the following to your main.cpp:
*
*     #define APPROVALS_GOOGLETEST
*     #include "ApprovalTests.hpp"
*
* To do this in doctest, add the following to your main.cpp:
*
*     #define APPROVALS_DOCTEST
*     #include "ApprovalTests.hpp"
*
* To do this in [Boost].UT, add the following to your main.cpp:
*
*     #define APPROVALS_UT
*     #include "ApprovalTests.hpp"
*
* For more information, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/GettingStarted.md
)" +
                    lineBuffer + lineBreak + '\n';
            return helpMessage;
        }
    };
}
// </SingleHpp>

#endif //APPROVALTESTS_CPP_HELPMESSAGES_H
