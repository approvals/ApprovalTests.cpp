#include "doctest/doctest.h"
#include "../../DocTest_Tests/reporters/TestReporter.h"
#include "ApprovalTests/core/ApprovalException.h"
#include "ApprovalTests/core/FileApprover.h"

// begin-snippet: create_custom_comparator
class LengthComparator : public ApprovalTests::ApprovalComparator
{
public:
    bool contentsAreEquivalent(std::string receivedPath,
                               std::string approvedPath) const override
    {
        return ApprovalTests::FileUtils::fileSize(receivedPath) ==
               ApprovalTests::FileUtils::fileSize(approvedPath);
    }
};
// end-snippet

TEST_CASE("ItUsesCustomComparator")
{
    using namespace ApprovalTests;

    FileUtils::writeToFile("a.length", "12345");
    FileUtils::writeToFile("b.length", "56789");

    // begin-snippet: use_custom_comparator
    auto disposer = FileApprover::registerComparatorForExtension(
        ".length", std::make_shared<LengthComparator>());
    // end-snippet

    FileApprover::verify("a.length", "b.length");
}
