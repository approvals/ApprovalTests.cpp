#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/utilities/StringUtils.h"

using namespace ApprovalTests;

TEST_CASE("ItCanFixCaseOfFileNameOnWindows")
{
    if (SystemUtils::isWindowsOs())
    {
        const std::string original_filename = __FILE__;
        const std::string lowercased_filename = StringUtils::toLower(original_filename);
        const std::string fixed_filename =
            SystemUtils::checkFilenameCase(lowercased_filename);
        INFO("The 'fixed' filename is " << fixed_filename);

        REQUIRE(original_filename.length() == fixed_filename.length());
        CHECK(StringUtils::contains(fixed_filename, "SystemUtilsTests.cpp"));
        // The current implementation doesn't fix the case of folder names, only the file
        // So for now, check that the folder name is still present, but expect it
        // to be lower case
        CHECK(StringUtils::contains(fixed_filename, "doctest_tests"));
    }
}

TEST_CASE("ItCanGetEnvironmentVariable")
{
    const auto result = SystemUtils::safeGetEnv("PATH");
    REQUIRE(result.length() > 0);
}

TEST_CASE("ItCanGetNonExistentEnvironmentVariable")
{
    const auto result =
        SystemUtils::safeGetEnv("THIS_ENVIRONMENT_VARIABLE_SHOULD_NOT_EXIST");
    REQUIRE(result.length() == 0);
}

TEST_CASE("ItCanCreateSubDirectory")
{
    auto subdirectory = Approvals::useApprovalsSubdirectory("custom_approval");
    ApprovalTestNamer namer;
    auto directory = namer.getDirectory();
    REQUIRE(FileUtils::fileExists(directory) == true);
    //    SystemUtils::removeDirectory(directory);
}
