#pragma once
#include "doctest/doctest.h"
#include "ApprovalTests/utilities/StringUtils.h"

inline void require_ends_with(const std::string& text, const std::string& endsWith)
{
    INFO("\n'" << text << "'\ndidn't end with\n'" << endsWith << "'"
               << "\n");
    REQUIRE(ApprovalTests::StringUtils::endsWith(text, endsWith));
}
