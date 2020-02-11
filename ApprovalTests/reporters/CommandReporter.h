#ifndef APPROVALTESTS_CPP_COMMANDREPORTER_H
#define APPROVALTESTS_CPP_COMMANDREPORTER_H

#include <utility>
#include <memory>
#include <numeric>
#include "ApprovalTests/launchers/CommandLauncher.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/core/Reporter.h"

namespace ApprovalTests
{
    class ConvertForCygwin
    {
    public:
        virtual ~ConvertForCygwin() = default;

        virtual std::string convertProgramForCygwin(const std::string& filePath)
        {
            return "$(cygpath '" + filePath + "')";
        }

        virtual std::string
        convertFileArgumentForCygwin(const std::string& filePath)
        {
            return "$(cygpath -aw '" + filePath + "')";
        }
    };

    class DoNothing : public ConvertForCygwin
    {
    public:
        std::string
        convertProgramForCygwin(const std::string& filePath) override
        {
            return filePath;
        }

        std::string
        convertFileArgumentForCygwin(const std::string& filePath) override
        {
            return filePath;
        }
    };

    // Generic reporter to launch arbitrary command
    class CommandReporter : public Reporter
    {
    private:
        std::string cmd;
        CommandLauncher* l;
        std::shared_ptr<ConvertForCygwin> converter;

    protected:
        CommandReporter(std::string command, CommandLauncher* launcher)
            : cmd(std::move(command)), l(launcher)
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
            return l->launch(getFullCommand(received, approved));
        }

        std::string getCommandLine(const std::string& received,
                                   const std::string& approved) const
        {
            return l->getCommandLine(getFullCommand(received, approved));
        }

        std::string getFullCommand(const std::string& received,
                                   const std::string& approved) const
        {
            auto convertedCommand = converter->convertProgramForCygwin(cmd);
            auto convertedReceived =
                converter->convertFileArgumentForCygwin(received);
            auto convertedApproved =
                converter->convertFileArgumentForCygwin(approved);
            std::vector<std::string> fullCommand;
            fullCommand.push_back(convertedCommand);
            fullCommand.push_back(convertedReceived);
            fullCommand.push_back(convertedApproved);

            std::string command =
                std::accumulate(fullCommand.begin(),
                                fullCommand.end(),
                                std::string(""),
                                [](const std::string& a, const std::string& b) {
                                    return a + " " + "\"" + b + "\"";
                                });
            return command;
        }

        void checkForCygwin()
        {
            useCygwinConversions(SystemUtils::isCygwin());
        }

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
