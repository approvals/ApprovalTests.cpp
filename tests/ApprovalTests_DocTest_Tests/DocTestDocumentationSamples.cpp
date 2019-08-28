#include "doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/namers/NamerFactory.h"
#include <vector>

enum Nationality
{
    British,
    American,
    French
};

struct Greeting
{
    Nationality nationality;
    explicit Greeting() : nationality(British)
    {
    }

    explicit Greeting(Nationality nationality) : nationality(nationality)
    {
    }
    
    std::string getGreeting() const
    {
        return getGreetingFor(nationality);
    }

    std::string getGreetingFor(Nationality aNationality) const
    {
        switch(aNationality)
        {
            case British:
                return "Cheers";
            case American:
                return "Howdy";
            case French:
                return "Bonjour";
            default:
                return "Unknown";
        }
    }

    std::string getNationality() const
    {
        switch(nationality)
        {
            case British:
                return "British";
            case American:
                return "American";
            case French:
                return "French";
            default:
                return "Unknown";
        }
    }
};

// begin-snippet: doctest_multiple_output_files_hard_coded
TEST_CASE("MultipleOutputFiles-ForOneObject")
{
    Greeting object_under_test;
    SUBCASE("British")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(British));
    }
    SUBCASE("American")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(American));
    }
    SUBCASE("French")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(French));
    }
}
// end-snippet

// begin-snippet: approvals_multiple_output_files_dynamic
TEST_CASE("ApprovalTests-MultipleOutputFiles-DataDriven")
{
    // This is an example of how to write multiple different files in a single test.
    // Note: For data as small as this, in practice we would recommend passing the
    // greetings container in to Approvals::verifyAll(), with a lambda to format the output,
    // in order to write all data to a single file.
    std::vector<Greeting> greetings{ Greeting(British), Greeting(American), Greeting(French) };
    for(auto greeting: greetings)
    {
        auto section = ApprovalTests::NamerFactory::appendToOutputFilename(greeting.getNationality());
        ApprovalTests::Approvals::verify(greeting.getGreeting());
    }
}
// end-snippet

// begin-snippet: approvals_multiple_output_files_hard_coded
TEST_CASE("ApprovalTests-MultipleOutputFiles-ForOneObject")
{
    Greeting object_under_test;
    {
        auto section = ApprovalTests::NamerFactory::appendToOutputFilename("British");
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(British));
    }
    {
        auto section = ApprovalTests::NamerFactory::appendToOutputFilename("American");
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(American));
    }
    {
        auto section = ApprovalTests::NamerFactory::appendToOutputFilename("French");
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(French));
    }
}
// end-snippet
