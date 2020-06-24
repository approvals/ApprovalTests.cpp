#pragma once

#include <sstream>
#include <exception>
#include <string>
#include <vector>
#include <functional>

namespace ApprovalTests
{
    class ExceptionCollector
    {
        std::vector<std::string> exceptionMessages;

    public:
        void gather(std::function<void(void)> functionThatThrows);

        ~ExceptionCollector();

        void release();
    };
}
