#include "doctest/doctest.h"
#include "utilities/FileUtils.h"
#include "utilities/StringUtils.h"
#include "utilities/EmptyFileCreatorFactory.h"
#include "Approvals.h"

TEST_CASE("Empty File Creation Customization")
{
    // begin-snippet: use_empty_file_creator
    ApprovalTests::EmptyFileCreator jsonCreator = [](std::string fileName)
    {
        std::string contents = "";
        if (ApprovalTests::StringUtils::endsWith(fileName, ".json"))
        {
            contents = "{}";
        }
        ApprovalTests::StringWriter s(contents);
        s.write(fileName);
    };
    auto disposer = ApprovalTests::FileUtils::useEmptyFileCreator(jsonCreator);
    // end-snippet
}
