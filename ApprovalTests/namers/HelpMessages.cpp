#include "ApprovalTests/namers/HelpMessages.h"
#include "ApprovalTests/utilities/StringUtils.h"

#include <sstream>

namespace ApprovalTests
{

    std::string HelpMessages::getMisconfiguredBuildHelp(const std::string& fileName)
    {
        std::string helpMessage = R"(* Welcome to Approval Tests.
*
* There seems to be a problem with your build configuration.
* We cannot find the test source file at:
*   [fileName]
*
* For details on how to fix this, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md
*
* For advanced users only:
* If you believe you have reached this message in error, you can bypass
* the check by calling ApprovalTestNamer::setCheckBuildConfig(false);
)";
        return StringUtils::replaceAll(
            topAndTailHelpMessage(helpMessage), "[fileName]", fileName);
    }

    std::string HelpMessages::getMisconfiguredMainHelp()
    {
        std::string helpMessage = R"(* Welcome to Approval Tests.
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
* To do this in Boost.Test, add the following to your main.cpp:
*
*     #define APPROVALS_BOOSTTEST
*     #include "ApprovalTests.hpp"
*
* To do this in CppUTest, add the following to your main.cpp:
*
*     #define APPROVALS_CPPUTEST
*     #include "ApprovalTests.hpp"
*
* To do this in [Boost].UT, add the following to your main.cpp:
*
*     #define APPROVALS_UT
*     #include "ApprovalTests.hpp"
*
* For more information, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredMain.md
)";
        return topAndTailHelpMessage(helpMessage);
    }

    std::string HelpMessages::getUnconfiguredRootDirectory()
    {
        std::string helpMessage = R"(* Hello from Approval Tests.
*
* It looks like your program is calling some code that requires knowledge of
* the location of the main() in your source tree.
*
* To do this, add the following to your main.cpp file:
*
*     APPROVAL_TESTS_REGISTER_MAIN_DIRECTORY
*
* Currently, this is only required if you are using TemplatedCustomNamer's
* {RelativeTestSourceDirectory}.
)";
        return topAndTailHelpMessage(helpMessage);
    }

    std::string
    HelpMessages::getUnknownEnvVarReporterHelp(const std::string& envVarName,
                                               const std::string& selected,
                                               const std::vector<std::string>& knowns)
    {
        std::string helpMessage =
            R"(* The environment variable [envVarName] contains the value
* [selected]
*
* This reporter is not recognised.
*
* Please unset the environment value, or change it to refer to one of the
* known reporters:
*
[known]*
* For more information, see:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/how_tos/SelectReporterWithEnvironmentVariable.md
)";

        return envVarErrorMessage(envVarName, selected, knowns, helpMessage);
    }

    std::string
    HelpMessages::getInvalidEnvVarReporterHelp(const std::string& envVarName,
                                               const std::string& selected,
                                               const std::vector<std::string>& knowns)
    {
        std::string helpMessage =
            R"(* The environment variable [envVarName] contains the value
* [selected]
*
* This reporter is recognised, but cannot be found on this machine.
*
* Please unset the environment value, or change it to refer to a working
* reporter:
*
[known]*
* For more information, see:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/how_tos/SelectReporterWithEnvironmentVariable.md
)";

        return envVarErrorMessage(envVarName, selected, knowns, helpMessage);
    }

    std::string HelpMessages::envVarErrorMessage(const std::string& envVarName,
                                                 const std::string& selected,
                                                 const std::vector<std::string>& knowns,
                                                 std::string& helpMessage)
    {
        std::stringstream ss;
        for (auto& known : knowns)
        {
            ss << "* " << known << '\n';
        }
        helpMessage = StringUtils::replaceAll(helpMessage, "[selected]", selected);
        helpMessage = StringUtils::replaceAll(helpMessage, "[envVarName]", envVarName);
        return topAndTailHelpMessage(
            StringUtils::replaceAll(helpMessage, "[known]", ss.str()));
    }

    std::string HelpMessages::topAndTailHelpMessage(const std::string& message)
    {
        const std::string lineBreak =
            "**************************************************************"
            "***************";
        const std::string lineBuffer =
            "*                                                             "
            "              *\n";
        return lineBreak + '\n' + lineBuffer + message + lineBuffer + lineBreak;
    }
}
