#ifndef APPROVALTESTS_CPP_DIFFINFO_H
#define APPROVALTESTS_CPP_DIFFINFO_H

#include <string>
#include "../FileUtils.h"

enum class Type { TEXT, IMAGE, TEXT_AND_IMAGE };

class StringUtils
{
public:
    // str -> inText, from -> find, to -> replaceWith
    static std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }
};

struct DiffInfo
{
    DiffInfo(std::string program, Type type) :
        program(program),
        arguments("%s %s"),
        type(type)
    {
    }
    DiffInfo(std::string program, std::string arguments, Type type) :
        program(program),
        arguments(arguments),
        type(type)
    {
    }
    std::string program;
    std::string arguments;
    Type type;

    std::string getProgramForOs() const
    {
       
        std::string result = program;
        if (result.rfind("{ProgramFiles}", 0) == 0) {
            auto result1 = StringUtils::replaceAll(result, "{ProgramFiles}", "c:\\Program Files\\");
       
            if (FileUtils::fileExists(result1)) {
                result = result1;
            }
            auto result2 = StringUtils::replaceAll(result, "{ProgramFiles}", "c:\\Program Files (x86)\\");
            if (FileUtils::fileExists(result2)) {
                result =  result2;
            }
        }
        return result;
    }
};


#endif //APPROVALTESTS_CPP_DIFFINFO_H
