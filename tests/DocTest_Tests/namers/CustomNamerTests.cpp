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

class CustomNamer : public ApprovalNamer
{
private:
    ApprovalTestNamer namer_;
    std::function<std::string(void)> testFolder_ = [&]() {
        return namer_.getTestSourceDirectory();
    };

public:
    std::string getTestFolder() const
    {
        return testFolder_();
    }

    CustomNamer withTestFolder(std::string value)
    {
        testFolder_ = [value]() { return value; };
        return *this;
    }

    CustomNamer withTestFolder(std::function<std::string(void)> newMethod)
    {
        testFolder_ = newMethod;
        return *this;
    }

    std::string getTestFolderForApproved() const
    {
        return getTestFolder();
    }

    std::string getRelativePathOfSourceDirectoryFromSourceRootForApproved() const
    {
        return namer_.getRelativePathOfSourceDirectoryFromSourceRootForApproved();
    }

    std::string getFileNameAndTestName() const
    {
        return namer_.getFileName() + "." + namer_.getTestName();
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

TEST_CASE("Behaviour with custom directory")
{
    auto custom = CustomNamer()
                      .withTestFolder([]() { return "custom/location"; })
                      .getApprovedFile(".txt");
    auto custom2 =
        CustomNamer().withTestFolder("custom/location").getApprovedFile(".txt");
    REQUIRE("custom/location/approval_tests/"
            "CustomNamerTests.Behaviour_with_custom_directory.approved.txt" == custom);
    REQUIRE(custom == custom2);
}
