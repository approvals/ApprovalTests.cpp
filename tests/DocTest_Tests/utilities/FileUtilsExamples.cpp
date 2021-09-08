#include "utilities/EmptyFileCreatorByType.h"
#include "doctest/doctest.h"
#include "utilities/FileUtils.h"
#include "utilities/StringUtils.h"
#include "utilities/EmptyFileCreatorFactory.h"
#include "Approvals.h"

TEST_CASE("Empty File Creation Customization")
{
    // begin-snippet: use_empty_file_creator
    ApprovalTests::EmptyFileCreator htmlCreator = [](std::string fileName) {
        std::string contents = "";
        if (ApprovalTests::StringUtils::endsWith(fileName, ".html"))
        {
            contents = "<!doctype html><title>TITLE</title>";
        }
        ApprovalTests::StringWriter s(contents);
        s.write(fileName);
    };
    auto disposer = ApprovalTests::FileUtils::useEmptyFileCreator(htmlCreator);
    // end-snippet
}

TEST_CASE("Empty File Creation Register For File Type")
{
    // begin-snippet: register_html_creator
    ApprovalTests::EmptyFileCreator htmlCreator = [](std::string fileName) {
        ApprovalTests::StringWriter s("<!doctype html><title>TITLE</title>");
        s.write(fileName);
    };
    ApprovalTests::EmptyFileCreatorByType::registerCreator(".html", htmlCreator);
    // end-snippet
}
