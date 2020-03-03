#ifndef APPROVALTESTS_CPP_COMMANDREPORTER_H
#define APPROVALTESTS_CPP_COMMANDREPORTER_H

#include <utility>
#include <memory>
#include <numeric>
#include "ApprovalTests/launchers/CommandLauncher.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/core/Reporter.h"
#include "ConvertForCygwin.h"
#include "DiffInfo.h"

namespace ApprovalTests
{
    // Generic reporter to launch arbitrary command
    class CommandReporter : public Reporter
    {
    private:
        std::string cmd;
        std::string arguments = DiffInfo::getDefaultArguments();
        CommandLauncher* l;
        std::shared_ptr<ConvertForCygwin> converter;

        std::string assembleFullCommand(const std::string& received,
                                        const std::string& approved) const
        {
            auto convertedCommand = '"' + converter->convertProgramForCygwin(cmd) + '"';
            auto convertedReceived =
                '"' + converter->convertFileArgumentForCygwin(received) + '"';
            auto convertedApproved =
                '"' + converter->convertFileArgumentForCygwin(approved) + '"';

            std::string args;
            args = StringUtils::replaceAll(
                arguments, DiffInfo::receivedFileTemplate(), convertedReceived);
            args = StringUtils::replaceAll(
                args, DiffInfo::approvedFileTemplate(), convertedApproved);

            return convertedCommand + ' ' + args;
        }

    protected:
        CommandReporter(std::string command, CommandLauncher* launcher)
            : cmd(std::move(command)), l(launcher)
        {
            checkForCygwin();
        }

        CommandReporter(std::string command, std::string args, CommandLauncher* launcher)
            : cmd(std::move(command)), arguments(std::move(args)), l(launcher)
        {
            checkForCygwin();
        }

    public:
        static bool exists(const std::string& command)
        {
            bool foundByWhich = false;
            if (!SystemUtils::isWindowsOs())
            {
                std::string which = "which " + command + " > /dev/null 2>&1";
                int result = system(which.c_str());
                foundByWhich = (result == 0);
            }
            return foundByWhich || FileUtils::fileExists(command);
        }

        bool report(std::string received, std::string approved) const override
        {
            if (!exists(cmd))
            {
                return false;
            }
            FileUtils::ensureFileExists(approved);
            return l->launch(assembleFullCommand(received, approved));
        }

        std::string getCommandLine(const std::string& received,
                                   const std::string& approved) const
        {
            return l->getCommandLine(assembleFullCommand(received, approved));
        }

    public:
        void checkForCygwin()
        {
            useCygwinConversions(SystemUtils::isCygwin());
        }

        // Seam for testing
        void useCygwinConversions(bool useCygwin)
        {
            if (useCygwin)
            {
                converter = std::make_shared<ConvertForCygwin>();
            }
            else
            {
                converter = std::make_shared<DoNothing>();
            }
        }
    };
}
#endif //APPROVALTESTS_CPP_COMMANDREPORTER_H
