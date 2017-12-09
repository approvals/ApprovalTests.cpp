#ifndef APPROVALTESTS_CPP_DIFFINFO_H
#define APPROVALTESTS_CPP_DIFFINFO_H

#include <string>

enum class Type {TEXT, IMAGE, TEXT_AND_IMAGE};

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
};


#endif //APPROVALTESTS_CPP_DIFFINFO_H
