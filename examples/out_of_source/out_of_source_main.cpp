#define APPROVALS_DOCTEST
#include "ApprovalTests.hpp"

#include "ghc/filesystem.hpp"
namespace fs = ghc::filesystem;

using namespace ApprovalTests;

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
        return locationFromEnvVar + "/{ApprovalsSubdirectory}/";
    }

    if (isRunningInBuildEnvironment())
    {
        return "{TestSourceDirectory}/";
    }

    return "{ApprovalsSubdirectory}/"; // Use current working directory
}

std::string getTemplateString()
{
    std::string args =
        "{TestFileName}.{TestCaseName}.{ApprovedOrReceived}.{FileExtension}";

    std::string rootDir = getApprovedFilesLocation();
    std::string templateString = rootDir + args;
    return templateString;
}

auto default_namer_disposer =
    TemplatedCustomNamer::useAsDefaultNamer(getTemplateString());

// TODO Test this out with some approved files in sub-directories - to confirm that the structure is retained
