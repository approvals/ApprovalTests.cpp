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
public:
    using PathFunction = std::function<Path(CustomNamer)>;

private:
    ApprovalTestNamer namer_;
    PathFunction testFolder_ = [](CustomNamer namer) {
        return Path(namer.namer_.getTestSourceDirectory());
    };

public:
    Path getTestFolder() const
    {
        return testFolder_(*this);
    }

    CustomNamer withTestFolder(std::string value)
    {
        testFolder_ = [value](CustomNamer /*namer*/) { return Path(value); };
        return *this;
    }

    CustomNamer withTestFolder(PathFunction newMethod)
    {
        testFolder_ = newMethod;
        return *this;
    }

    Path getTestFolderForApproved() const
    {
        return getTestFolder();
    }

    Path getRelativePathOfSourceDirectoryFromSourceRootForApproved() const
    {
        return Path(namer_.getRelativePathOfSourceDirectoryFromSourceRootForApproved());
    }

    std::string getFileNameAndTestName() const
    {
        return namer_.getFileName() + "." + namer_.getTestName();
    }

    virtual std::string getApprovedFile(std::string extensionWithDot) const override
    {
        return (getTestFolderForApproved() /
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

namespace
{
    static std::string normalize(const std::string& custom)
    {
        return StringUtils::replaceAll(custom, "\\", "/");
    }
}

TEST_CASE("Default Behaviour")
{
    auto result = Approvals::getDefaultNamer()->getApprovedFile(".txt");
    auto custom = CustomNamer().getApprovedFile(".txt");
    REQUIRE(result == custom);
}

TEST_CASE("Behaviour with custom directory")
{
    auto custom =
        CustomNamer()
            .withTestFolder([](auto /*namer*/) { return Path("custom/location"); })
            .getApprovedFile(".txt");
    REQUIRE("custom/location/approval_tests/"
            "CustomNamerTests.Behaviour_with_custom_directory.approved.txt" ==
            normalize(custom));

    auto custom2 =
        CustomNamer().withTestFolder("custom/location").getApprovedFile(".txt");
    REQUIRE(custom == custom2);
}

//TEST_CASE("Test Every Customization")
//{
//    auto custom = CustomNamer()
//                       .withTestFolder("custom/location")
//                       .withTestFolderForApproved([](auto that) {
//                           return that.getTestFolder() / "approved_files";
//                       })
//                       .getApprovedFile(".txt");
//    REQUIRE("custom/location/approved_files/approval_tests/"
//            "CustomNamerTests.Behaviour_with_custom_directory.approved.txt" == normalize(custom));
//}
