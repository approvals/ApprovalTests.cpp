#include "catch.hpp"
#include <map>
#include <vector>
#include <string>
#include <ApprovalTests/reporters/BlockingReporter.h>
#include "PairUtilities.h"
#include "ApprovalTests/CombinationApprovals.h"
#include "reporters/FakeReporter.h"

using namespace ApprovalTests;

TEST_CASE("YouCanVerifyCombinationsOf1") {
    std::vector<std::string> words{"hello", "world"};
    CombinationApprovals::verifyAllCombinations([](const std::string& s){return s + "!";}, words);
}

TEST_CASE("YouCanVerifyCombinationsOf1WithTemplateParameters") {
    std::vector<std::string> words{"hello", "world"};
    CombinationApprovals::verifyAllCombinations([](const std::string& s){return s + "!";}, words);
}

FrontLoadedReporterDisposer clearFrontLoadedReporter()
{
    return Approvals::useAsFrontLoadedReporter(
            BlockingReporter::onMachineNamed("safadfasdfas"));
}

TEST_CASE("YouCanVerifyCombinationsOf1Reports")
{
    auto d = clearFrontLoadedReporter();
    std::vector<std::string> words{"hello", "world"};
    FakeReporter reporter;
    try
    {
        CombinationApprovals::verifyAllCombinations(reporter, [](const std::string& s){return s + "!";}, words);
    }
    catch(const ApprovalException&)
    {
        // ignore
    }
    REQUIRE(reporter.called == true);
}


// begin-snippet: YouCanVerifyCombinationsOf2
TEST_CASE("YouCanVerifyCombinationsOf2") {
    std::vector<std::string> v{"hello", "world"};
    std::vector<int> numbers{1, 2, 3};
    CombinationApprovals::verifyAllCombinations(
            [](std::string s, int i){return std::make_pair(s, i);},
            v,
            numbers);
}
// end-snippet

TEST_CASE("YouCanVerifyCombinationsOf9") {
    std::vector<std::string> letters{"a", "b"};
    CombinationApprovals::verifyAllCombinations([](
                                                               const std::string& s1,
                                                               const std::string& s2,
                                                               const std::string& s3,
                                                               const std::string& s4,
                                                               const std::string& s5,
                                                               const std::string& s6,
                                                               const std::string& s7,
                                                               const std::string& s8,
                                                               const std::string& s9)
                              {return s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9;}, letters, letters, letters, letters, letters, letters, letters, letters, letters);
}

TEST_CASE("YouCanVerifyCombinationsOf9Reports")
{
    auto d = clearFrontLoadedReporter();
    FakeReporter reporter;
    try
    {
        std::vector<std::string> letters{"a", "b"};
        CombinationApprovals::verifyAllCombinations(
            reporter,
            [](const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4, const std::string& s5,
               const std::string& s6, const std::string& s7, const std::string& s8, const std::string& s9)
            {return s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9;},
            letters, letters, letters, letters, letters, letters, letters, letters, letters
        );
    }
    catch(const ApprovalException&)
    {
        // ignore
    }
    REQUIRE(reporter.called == true);
}


TEST_CASE("YouCanVerifyCombinationsOf10") {
    std::vector<std::string> letters{"a", "b"};
    CombinationApprovals::verifyAllCombinations([](
                                                               const std::string& s1,
                                                               const std::string& s2,
                                                               const std::string& s3,
                                                               const std::string& s4,
                                                               const std::string& s5,
                                                               const std::string& s6,
                                                               const std::string& s7,
                                                               const std::string& s8,
                                                               const std::string& s9,
                                                               const std::string& s10)
                              {return s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10;}, letters, letters, letters, letters, letters, letters, letters, letters, letters, letters);
}
