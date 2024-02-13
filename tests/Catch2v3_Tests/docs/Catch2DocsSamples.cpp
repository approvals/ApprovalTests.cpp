#include "ApprovalTests/Approvals.h"

#include <catch2/catch_test_macros.hpp>
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

TEST_CASE("MultipleOutputFiles-DataDriven")
{
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
