#pragma once

inline void require_ends_with(const std::string& text, const std::string& endsWith)
{
    INFO("\n'" << text << "'\ndidn't end with\n'" << endsWith << "'"
               << "\n");
    REQUIRE(ApprovalTests::StringUtils::endsWith(text, endsWith));
}
