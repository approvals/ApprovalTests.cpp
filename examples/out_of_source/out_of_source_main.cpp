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
    auto workingDirectory = fs::canonical(fs::path(".")).string();
    std::string ending = "examples/out_of_source";
    ending = StringUtils::replaceAll(ending, "/", SystemUtils::getDirectorySeparator());
    return StringUtils::endsWith(workingDirectory, ending);
}

std::string getApprovedFilesLocation()
{
    std::string locationFromEnvVar = SystemUtils::safeGetEnv("APPROVED_FILES_ROOT_DIR");
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

// TODO Remove the need to calculate root dir on every call to the the namer
// TODO Test this out with some approved files in sub-directories - to confirm that the structure is retained
