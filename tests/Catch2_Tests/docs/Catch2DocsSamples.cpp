#include "catch2/catch.hpp"
#include "ApprovalTests/Approvals.h"
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

    explicit Greeting(Nationality nationality_) : nationality(nationality_)
    {
    }

    std::string getGreeting() const
    {
        return getGreetingFor(nationality);
    }

    std::string getGreetingFor(Nationality aNationality) const
    {
        switch (aNationality)
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
        switch (nationality)
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

// begin-snippet: catch2_multiple_output_files_dynamic
TEST_CASE("MultipleOutputFiles-DataDriven")
{
    // This is an example of how to write multiple different files in a single test.
    // Note: For data as small as this, in practice we would recommend passing the
    // greetings container in to Approvals::verifyAll(), with a lambda to format the output,
    // in order to write all data to a single file.
    std::vector<Greeting> greetings{
        Greeting(British), Greeting(American), Greeting(French)};
    for (auto greeting : greetings)
    {
        SECTION(greeting.getNationality())
        {
            ApprovalTests::Approvals::verify(greeting.getGreeting());
        }
    }
}
// end-snippet

// begin-snippet: catch2_multiple_output_files_hard_coded
TEST_CASE("MultipleOutputFiles-ForOneObject")
{
    Greeting object_under_test;
    SECTION("British")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(British));
    }
    SECTION("American")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(American));
    }
    SECTION("French")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(French));
    }
}
// end-snippet
