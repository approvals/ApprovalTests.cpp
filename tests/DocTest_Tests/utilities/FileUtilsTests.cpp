#include "doctest/doctest.h"
#include "utilities/FileUtils.h"
#include "namers/ApprovalTestNamer.h"
#include "Approvals.h"
#include "reporters/DiffReporter.h"

using namespace ApprovalTests;

TEST_CASE("It reads sample_file.txt correctly")
{
    ApprovalTestNamer namer;
    const auto directory = namer.getDirectory();
    const std::string inputFile = directory + "sample_file.txt";

    Approvals::verify(ApprovalTests::FileUtils::readFileThrowIfMissing(inputFile),
                      Options(DiffReporter()));
}

TEST_CASE("readFileThrowIfMissing() throws if file is missing")
{
    bool exceptionThrown = false;
    try
    {
        ApprovalTests::FileUtils::readFileThrowIfMissing(
            "some file name that does not exist 1234567890.txt");
    }
    catch (const std::exception&)
    {
        exceptionThrown = true;
    }
    REQUIRE(exceptionThrown);
}

TEST_CASE("readFileReturnEmptyIfMissing() returns empty string if file is missing")
{
    REQUIRE("" == ApprovalTests::FileUtils::readFileReturnEmptyIfMissing(
                      "some file name that does not exist 1234567890.txt"));
}

TEST_CASE("check impossible directories don't explode")
{
    CHECK(!FileUtils::fileExists(
        "../../../../../../../../../../../../../../../../../../../../../a.txt"));
}

TEST_CASE("Empty File Creation")
{
    std::string called = "";
    auto disposer = ApprovalTests::FileUtils::useEmptyFileCreator(
        [&](std::string fileName) { called = fileName; });
    std::string filePath = "/this/file/will/not/exist.txt";
    FileUtils::ensureFileExists(filePath);
    REQUIRE(filePath == called);
}
