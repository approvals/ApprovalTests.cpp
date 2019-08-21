#include "doctest.h"
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
        Approvals::verify(object_under_test.getGreetingFor(British));
    }
    SUBCASE("American")
    {
        Approvals::verify(object_under_test.getGreetingFor(American));
    }
    SUBCASE("French")
    {
        Approvals::verify(object_under_test.getGreetingFor(French));
    }
}
// end-snippet
