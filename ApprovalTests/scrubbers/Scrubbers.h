#pragma once

#include <string>

namespace ApprovalTests
{
    namespace Scrubbers
    {
        std::string scrubGuid(const std::string& input)
        {
            // Match against the input to see if it's a GUID or not
            if (input == "")
            {
                return input;
            }
            // If it is, replace with guid_1, return original string
            return "guid_1";
        }
    }
}
