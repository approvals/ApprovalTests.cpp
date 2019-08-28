#include "Catch.hpp"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/utilities/StringUtils.h"

TEST_CASE("ItCanFixCaseOfFileNameOnWindows")
{
    if( ApprovalTests::SystemUtils::isWindowsOs())
    {
        const std::string original_filename = __FILE__;
        const std::string lowercased_filename = ApprovalTests::StringUtils::toLower(original_filename);
        const std::string fixed_filename = ApprovalTests::SystemUtils::checkFilenameCase(lowercased_filename);
        INFO("The 'fixed' filename is " << fixed_filename);

        REQUIRE(original_filename.length() == fixed_filename.length());
        CHECK(ApprovalTests::StringUtils::contains(fixed_filename, "SystemUtilsTests.cpp"));
        // The current implementation doesn't fix the case of folder names, only the file
        // So for now, check that the folder name is still present, but expect it
        // to be lower case
        CHECK(ApprovalTests::StringUtils::contains(fixed_filename, "catch2_tests"));
    }
}

TEST_CASE("ItCanGetEnvironmentVariable")
{
    const auto result = ApprovalTests::SystemUtils::safeGetEnv("PATH");
    REQUIRE(result.length() > 0);
}

TEST_CASE("ItCanGetNonExistentEnvironmentVariable")
{
    const auto result = ApprovalTests::SystemUtils::safeGetEnv("THIS_ENVIRONMENT_VARIABLE_SHOULD_NOT_EXIST");
    REQUIRE(result.length() == 0);
}

TEST_CASE("ItCanCreateSubDirectory")
{
    auto subdirectory = ApprovalTests::Approvals::useApprovalsSubdirectory("custom_approval");
    ApprovalTests::ApprovalTestNamer namer;
    auto directory = namer.getDirectory();
    REQUIRE(ApprovalTests::FileUtils::fileExists(directory) == true);
//    SystemUtils::removeDirectory(directory);
}
