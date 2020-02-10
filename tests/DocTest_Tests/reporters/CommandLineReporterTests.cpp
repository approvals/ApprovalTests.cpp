#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/reporters/CustomReporter.h"
//#include "ApprovalTests/reporters/GenericDiffReporter.h"

#include <vector>

using namespace ApprovalTests;

TEST_CASE("Test Command Lines")
{
    std::stringstream stream;
    SystemUtils::debugCommandLines().isTest = true;
    std::vector<std::shared_ptr<GenericDiffReporter>> reporters = {
        std::make_shared<Mac::BeyondCompareReporter>(),
        std::make_shared<Mac::KaleidoscopeReporter>(),
    };
    for (const auto& reporter : reporters)
    {
        SystemUtils::debugCommandLines().lastCommand = "Not Run";
        reporter->report("a.txt", "b.txt");
        stream << "native: " << SystemUtils::debugCommandLines().lastCommand << '\n';

        reporter->checkForCygwin(true);
        SystemUtils::debugCommandLines().lastCommand = "Not Run";
        reporter->report("a.txt", "b.txt");
        stream << "cygwin: " << SystemUtils::debugCommandLines().lastCommand << '\n';
        stream << '\n';
    }
    SystemUtils::debugCommandLines().isTest = false;
    Approvals::verify(stream.str());
}
