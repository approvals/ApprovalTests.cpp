#include "doctest/doctest.h"
#include "ApprovalTests/comparators/ComparatorDisposer.h"
#include "ApprovalTests/core/ApprovalException.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/StringUtils.h"

#include "Approvals.h"
#include <fstream>
#include <iterator>
#include <memory>

using namespace ApprovalTests;

namespace
{
    class CaseInsensitiveComparator : public ApprovalComparator
    {
    public:
        bool contentsAreEquivalent(std::string receivedPath,
                                   std::string approvedPath) const override
        {
            std::ifstream receivedStream(receivedPath.c_str());
            std::ifstream approvedStream(approvedPath.c_str());

            using InputIter = std::istreambuf_iterator<char>;

            auto receivedText = std::string(InputIter{receivedStream}, InputIter{});
            auto approvedText = std::string(InputIter{approvedStream}, InputIter{});

            return StringUtils::toLower(receivedText) ==
                   StringUtils::toLower(approvedText);
        }
    };
}

TEST_CASE("Type traits of ComparatorDisposer")
{

    REQUIRE_FALSE(std::is_copy_constructible<ComparatorDisposer>::value);
    REQUIRE_FALSE(std::is_copy_assignable<ComparatorDisposer>::value);

    REQUIRE(std::is_move_constructible<ComparatorDisposer>::value);
    REQUIRE_FALSE(std::is_move_assignable<ComparatorDisposer>::value);
}

TEST_CASE("ComparatorDisposer object can be moved without disposing a "
          "comparator twice")
{
    FileUtils::writeToFile("a.txt", "foo");
    FileUtils::writeToFile("b.txt", "FOO");

    // Case-insensitive comparator is not registered - files are not equivalent
    REQUIRE_THROWS_AS(FileApprover::verify("a.txt", "b.txt"), ApprovalMismatchException);

    std::unique_ptr<ComparatorDisposer> disposer;

    {
        auto temporaryDisposer = FileApprover::registerComparatorForExtension(
            ".txt", std::make_shared<CaseInsensitiveComparator>());

        // The comparator is registered - files are equivalent
        REQUIRE_NOTHROW(FileApprover::verify("a.txt", "b.txt"));

        disposer.reset(new ComparatorDisposer(std::move(temporaryDisposer)));
    }

    // The comparator is still registered - files are equivalent
    REQUIRE_NOTHROW(FileApprover::verify("a.txt", "b.txt"));

    // Deregisters the comparator
    disposer.reset();

    // The comparator is no longer registered - files are not equivalent
    REQUIRE_THROWS_AS(FileApprover::verify("a.txt", "b.txt"), ApprovalMismatchException);
}
