#define APPROVALS_DOCTEST
#include "ApprovalTests.hpp"

#include "DocTestReporter.h"

#include <filesystem>

using namespace ApprovalTests;

//auto defaultReporterDisposer =
//    Approvals::useAsDefaultReporter(std::make_shared<TextDiffReporter>());

//auto defaultReporterDisposer =
//    Approvals::useAsDefaultReporter(std::make_shared<DocTestReporter>());

auto configChange = ApprovalTestNamer::setCheckBuildConfig(false);

bool isRunningInBuildEnvironment()
{
    ApprovalTestNamer namer;
    auto path1 = std::filesystem::canonical(std::filesystem::path(".")).string();
    std::cout << "--- ApprovalTestNamer::getTestSourceDirectory(): "
              << namer.getTestSourceDirectory() << '\n';
    std::cout << "--- ApprovalTestNamer::getDirectory(): " << namer.getDirectory()
              << '\n';
    std::cout << "--- Current working directory: " << path1 << '\n';

    bool is_build_environment = StringUtils::endsWith(path1, "examples/out_of_source");
    return is_build_environment;
}

auto default_namer_disposer = Approvals::useAsDefaultNamer([]() {
    std::string args =
        "{TestFileName}.{TestCaseName}.{ApprovedOrReceived}.{FileExtension}";
        bool is_build_environment = isRunningInBuildEnvironment();

    if (is_build_environment)
    {
        args = "{TestSourceDirectory}/" + args;
    }
    else if (!SystemUtils::safeGetEnv("APPROVED_FILES_ROOT_DIR").empty())
    {
        args = SystemUtils::safeGetEnv("APPROVED_FILES_ROOT_DIR") + "/" + args;
    }
    return std::make_shared<TemplatedCustomNamer>(args);
});
