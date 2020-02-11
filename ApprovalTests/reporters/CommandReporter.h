#ifndef APPROVALTESTS_CPP_COMMANDREPORTER_H
#define APPROVALTESTS_CPP_COMMANDREPORTER_H

#include <utility>
#include <memory>
#include "ApprovalTests/launchers/CommandLauncher.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/core/Reporter.h"

namespace ApprovalTests
{
    using ConvertArgumentsFunctionPointer =
        std::vector<std::string> (*)(std::vector<std::string>);

    class ConvertForCygwin
    {
    public:
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
        virtual std::string convertProgramForCygwin(const std::string& filePath)
        {
            return filePath;
        }

        virtual std::string
        convertFileArgumentForCygwin(const std::string& filePath)
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
        bool report(std::string received, std::string approved) const override
        {
            FileUtils::ensureFileExists(approved);
            return l->launch(getFullCommand(received, approved));
        }

        std::string getCommandLine(const std::string& received,
                                   const std::string& approved) const
        {
            return l->getCommandLine(getFullCommand(received, approved));
        }

        std::vector<std::string>
        getFullCommand(const std::string& received,
                       const std::string& approved) const
        {
            std::vector<std::string> fullCommand;
            fullCommand.push_back(cmd);
            fullCommand.push_back(received);
            fullCommand.push_back(approved);

            fullCommand = convertForCygwin(fullCommand);

            return fullCommand;
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

        static std::vector<std::string> doNothing(std::vector<std::string> argv)
        {
            return argv;
        }

        std::vector<std::string>
        convertForCygwin(std::vector<std::string> argv) const
        {
            std::vector<std::string> copy = argv;
            for (size_t i = 0; i != argv.size(); ++i)
            {
                if (i == 0)
                {
                    const std::string& arg_value = argv[i];
                    copy[i] = converter->convertProgramForCygwin(arg_value);
                }
                else
                {
                    const std::string& arg_value = argv[i];
                    copy[i] =
                        converter->convertFileArgumentForCygwin(arg_value);
                }
            }
            return copy;
        }

    };
}
#endif //APPROVALTESTS_CPP_COMMANDREPORTER_H
