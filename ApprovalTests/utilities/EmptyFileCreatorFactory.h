#pragma once
#include <functional>

namespace ApprovalTests
{
    using EmptyFileCreator = std::function<void(std::string)>;

    class EmptyFileCreatorFactory
    {
    public:
        static void defaultCreator(std::string fullFilePath);
        static EmptyFileCreator currentCreator;
    };
}
