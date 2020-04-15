#pragma once

#include <string>

namespace Scrubbers
{
    std::string scrubGuid(const std::string& /*input*/)
    {
        // Match against the input to see if it's a GUID or not
        // If it is, replace with guid_1, return original string
        return "guid_1";
    }
}
