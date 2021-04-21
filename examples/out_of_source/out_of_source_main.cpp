#define APPROVALS_DOCTEST
#include "ApprovalTests.hpp"

#include "DocTestReporter.h"

#include "ghc/filesystem.hpp"
namespace fs = ghc::filesystem;

using namespace ApprovalTests;

//auto defaultReporterDisposer =
//    Approvals::useAsDefaultReporter(std::make_shared<TextDiffReporter>());

//auto defaultReporterDisposer =
//    Approvals::useAsDefaultReporter(std::make_shared<DocTestReporter>());

auto configChange = ApprovalTestNamer::setCheckBuildConfig(false);

bool isRunningInBuildEnvironment()
{
    ApprovalTestNamer namer;
    auto workingDirectory = fs::canonical(fs::path(".")).string();
    std::cout << "--- ApprovalTestNamer::getTestSourceDirectory(): "
              << namer.getTestSourceDirectory() << '\n';
    std::cout << "--- ApprovalTestNamer::getDirectory(): " << namer.getDirectory()
              << '\n';
    std::cout << "--- Current working directory: " << workingDirectory << '\n';

    std::string ending = "examples/out_of_source";
    ending = StringUtils::replaceAll(ending, "/", SystemUtils::getDirectorySeparator());
    return StringUtils::endsWith(workingDirectory, ending);
}

std::string getApprovedFilesLocation()
{
    std::string locationFromEnvVar =
        SystemUtils::safeGetEnv("APPROVED_FILES_ROOT_DIR");
    if (!locationFromEnvVar.empty())
    {
        return locationFromEnvVar + "/";
    }

    if (isRunningInBuildEnvironment())
    {
        return "{TestSourceDirectory}/";
    }

    return ""; // Use current working directory
}

auto default_namer_disposer = Approvals::useAsDefaultNamer([]() {
    std::string args =
        "{TestFileName}.{TestCaseName}.{ApprovedOrReceived}.{FileExtension}";

    std::string rootDir = getApprovedFilesLocation();
    return std::make_shared<TemplatedCustomNamer>(rootDir + args);
});
