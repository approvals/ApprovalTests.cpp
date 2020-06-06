#include "doctest/doctest.h"
#include "ApprovalTests/core/Options.h"

#include "ApprovalTests/reporters/QuietReporter.h"
#include "ApprovalTests/Approvals.h"

#include <list>

using namespace ApprovalTests;

namespace
{
    void checkSameType(std::type_info const& type1,
                       std::type_info const& type2,
                       const std::string& message)
    {
        CHECK_MESSAGE(std::string(type1.name()) == std::string(type2.name()), message);
    }
}

TEST_CASE("Options - Reporter features")
{
    Options options;
    const Reporter& initialReporter = options.getReporter();

    checkSameType(typeid(initialReporter),
                  typeid(DefaultReporter),
                  "Initial reporter was not expected type");

    // Check that setting the reporter gets back the same object
    {
        QuietReporter new_reporter;
        const Options& options3 = options.withReporter(new_reporter);
        const Reporter& reporter3 = options3.getReporter();
        CHECK(&reporter3 == &new_reporter);
    }
}

TEST_CASE("Options - FileExtension features")
{
    Options options;
    const Reporter& initialReporter = options.getReporter();

    CHECK(options.fileOptions().getFileExtension() == ".txt");
    CHECK(options.fileOptions()
              .withFileExtension(".xyz")
              .fileOptions()
              .getFileExtension() == ".xyz");

    // Check that setting the file extension does not change the reporter instance:
    {
        const Reporter& reporter2 =
            options.fileOptions().withFileExtension(".abc").getReporter();
        CHECK(&initialReporter == &reporter2);
    }
}

TEST_CASE("copying")
{
    // Options.with... returns new Options, containing new FileOptions
    // Options.fileOptions()... returns local FileOptions - but with options poi
    // Options.fileOptions().with... returns new Options containing new FileOptions

    // FileOptions contains a non-owning pointer to its parent Options
    Options o1;
    Options o2 = o1;

    Options::FileOptions fo = Options().fileOptions();
}

TEST_CASE("Options - FileExtension Example")
{
    // begin-snippet: basic_approval_with_file_extension
    Approvals::verify("text to be verified",
                      Options().fileOptions().withFileExtension(".xyz"));
    // end-snippet
}

TEST_CASE("verify with optional args")
{
    const Options options;
    const std::string contents("Hello World");
    StringWriter writer(contents);

    // Normally having multiple verify calls in the same scope is an error,
    // if they have different expected output.
    // In this case it's fine, as all these overloads give the same output.
    Approvals::verify(contents, options);
    Approvals::verify(writer, options);
    Approvals::verify<std::string>(contents, options);
    Approvals::verify(
        contents, [](const auto& p, auto& os) { os << p; }, options);
}

TEST_CASE("verifyAll with optional args")
{
    const Options options;
    const std::vector<int> valuesVector{1, 2, 3, 4, 5};
    const std::list<int> valuesList{1, 2, 3, 4, 5};
    const std::string header("header");
    auto converter = [](auto input, auto& stream) { stream << input; };

    {
        SUBCASE("with converter")
        Approvals::verifyAll(
            header, valuesList.cbegin(), valuesList.cend(), converter, options);
        Approvals::verifyAll(header, valuesList, converter, options);
        Approvals::verifyAll(header, valuesVector, converter, options);
    }

    {
        SUBCASE("vector and header")
        Approvals::verifyAll(header, valuesVector, options);
    }

    {
        SUBCASE("vector")
        Approvals::verifyAll(valuesVector, options);
    }
}
