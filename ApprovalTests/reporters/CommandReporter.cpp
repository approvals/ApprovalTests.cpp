#include "ApprovalTests/reporters/CommandReporter.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"

namespace ApprovalTests
{
    std::string CommandReporter::assembleFullCommand(const std::string& received,
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

    CommandReporter::CommandReporter(std::string command, CommandLauncher* launcher)
        : cmd(std::move(command)), l(launcher)
    {
        checkForCygwin();
    }

    CommandReporter::CommandReporter(std::string command,
                                     std::string args,
                                     CommandLauncher* launcher)
        : cmd(std::move(command)), arguments(std::move(args)), l(launcher)
    {
        checkForCygwin();
    }

    bool CommandReporter::exists(const std::string& command)
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

    bool CommandReporter::report(std::string received, std::string approved) const
    {
        if (!exists(cmd))
        {
            return false;
        }
        FileUtils::ensureFileExists(approved);
        return l->launch(assembleFullCommand(received, approved));
    }

    std::string CommandReporter::getCommandLine(const std::string& received,
                                                const std::string& approved) const
    {
        return l->getCommandLine(assembleFullCommand(received, approved));
    }

    void CommandReporter::checkForCygwin()
    {
        useCygwinConversions(SystemUtils::isCygwin());
    }

    void CommandReporter::useCygwinConversions(bool useCygwin)
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
}
