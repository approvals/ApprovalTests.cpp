#pragma once

#include "ApprovalTests/utilities/EmptyFileCreatorFactory.h"

#include <map>
#include <string>

namespace ApprovalTests
{
    class EmptyFileCreatorByType
    {
    private:
        static std::map<std::string, EmptyFileCreator> creators_;

    public:
        static void registerCreator(const std::string& extensionWithDot,
                                    EmptyFileCreator creator);

        static void createFile(const std::string& fileName);
    };
}
