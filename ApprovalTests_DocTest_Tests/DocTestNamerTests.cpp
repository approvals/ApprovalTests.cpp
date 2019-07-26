#include "doctest.hpp"

TEST_CASE("first passing doctest test")
{
    CHECK(1 == 1);
}

#include "ApprovalTests/namers/ApprovalTestNamer.h"
//#include "ApprovalTests/StringUtils.h"
#include "ApprovalTests/Approvals.h"
//
//using namespace std;
//using Catch::Matchers::EndsWith;
//
TEST_CASE("ItCanGiveYouTheSpecName") {

    ApprovalTestNamer namer;
    REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName");

    DOCTEST_SUBCASE("andSectionNames") {
        REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames");
        DOCTEST_SUBCASE("andEvenMoreSectionNames") {
            REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames.andEvenMoreSectionNames");
        }
    }
}

TEST_CASE("ItCanGiveYouTheTestFileName") {
    ApprovalTestNamer namer;
    REQUIRE(namer.getFileName() == "DocTestNamerTests");
}

TEST_CASE("It can verify tests with spaces")
{
    // DON'T SAVE REPORTER!!!!!
    Approvals::verify("hello world");
//    Approvals::verify("hello world", Windows::AraxisMergeReporter());
}


//TEST_CASE("Clean Up Filename Transforms")
//{
//    std::vector<std::string> names = { "CleanUpFilenameTransforms", "Spaces In File \\" };
//    Approvals::verifyAll("File Names", names, [&](std::string name, std::ostream &s) {s << name << " => " << ApprovalTestNamer::convertToFileName(name); });
//}
//
//TEST_CASE("Use sub-directory")
//{
//    auto subdirectory = Approvals::useApprovalsSubdirectory("approved_files");
//    auto namer = Approvals::getDefaultNamer();
//    REQUIRE_THAT( namer->getApprovedFile(".txt"), Catch::Matchers::Contains( "approved_files" ) );
//}
//
//TEST_CASE("Use sub-directories clean to previous results")
//{
//    auto subdirectory = Approvals::useApprovalsSubdirectory("outer");
//    auto namer = Approvals::getDefaultNamer();
//
//    {
//        auto subdirectory2 = Approvals::useApprovalsSubdirectory("inner");
//        REQUIRE_THAT( namer->getApprovedFile(".txt"), Catch::Matchers::Contains( "inner" ) );
//    }
//
//    REQUIRE_THAT( namer->getApprovedFile(".txt"), Catch::Matchers::Contains( "outer" ) );
//}
