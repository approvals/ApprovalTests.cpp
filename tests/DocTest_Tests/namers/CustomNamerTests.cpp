#include "doctest/doctest.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/namers/NamerFactory.h"
#include "ApprovalTests/utilities/Path.h"
#include "ApprovalTests/utilities/SystemUtils.h"

//#include <filesystem>
#include <iostream>
#include <memory>

using namespace ApprovalTests;

class CustomNamer : public ApprovalTestNamer
{

public:
    std::string getTestFolder() const
    {
        return getTestSourceDirectory();
    }

    std::string getTestFolderForApproved() const
    {
        return getTestFolder();
    }

    std::string getRelativePathOfSourceDirectoryFromSourceRootForApproved() const
    {
        return ApprovalTestNamer::
            getRelativePathOfSourceDirectoryFromSourceRootForApproved();
    }

    std::string getFileNameAndTestName() const
    {
        return getFileName() + "." + getTestName();
    }

    virtual std::string getApprovedFile(std::string extensionWithDot) const override
    {
        return (Path(getTestFolderForApproved()) /
                    getRelativePathOfSourceDirectoryFromSourceRootForApproved() /
                    getFileNameAndTestName() +
                ".approved" + extensionWithDot)
            .toString();
    }

    virtual std::string getReceivedFile(std::string /*extensionWithDot*/) const override
    {
        return "my.received";
    }
};

TEST_CASE("Default Behaviour")
{
    auto result = Approvals::getDefaultNamer()->getApprovedFile(".txt");
    auto custom = CustomNamer().getApprovedFile(".txt");
    REQUIRE(result == custom);
}
