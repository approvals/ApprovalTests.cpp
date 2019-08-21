#include "Catch.hpp"
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
        }
    }
};

TEST_CASE("MultipleOutputFiles-DataDriven")
{
    // This is an example of how to write multiple different files in a single test.
    // Note: For data as small as this, in practice we would recommend passing the
    // greetings container in to Approvals::verifyAll(), with a lambda to format the output,
    // in order to write all data to a single file.
    std::vector<Greeting> greetings{ Greeting(British), Greeting(American), Greeting(French) };
    for(auto greeting: greetings)
    {
        SECTION(greeting.getNationality())
        {
            Approvals::verify(greeting.getGreeting());
        }
    }
}

TEST_CASE("MultipleOutputFiles-ForSystemUnderTest")
{
    Greeting greeting;
    SECTION("British")
    {
        Approvals::verify(greeting.getGreetingFor(British));
    }
    SECTION("American")
    {
        Approvals::verify(greeting.getGreetingFor(American));
    }
    SECTION("French")
    {
        Approvals::verify(greeting.getGreetingFor(French));
    }
}

struct Dinner
{
    Dinner(const std::string&, int)
    {};

    std::string printBusinessReceipt()
    {
        return "Dinner: $59.00";
    }

    std::string printPersonalReceipt()
    {
        return "Wine: $59.00";
    }

    void writeAllReceipts()
    {

    }
};
TEST_CASE("MultipleOutputFiles2")
{
    Dinner dinner("Wine", 59);
    SECTION("BusinessReceipt")
    {
        Approvals::verify("Dinner: $59.00");
    }
    SECTION("PersonalReceipt")
    {
        Approvals::verify("Wine: $59.00");
    }
}

TEST_CASE("MultipleOutputFiles1")
{
    Dinner dinner("Wine", 59);
    SECTION("BusinessReceipt")
    {
        Approvals::verify(dinner.printBusinessReceipt());
    }
    SECTION("PersonalReceipt")
    {
        Approvals::verify(dinner.printPersonalReceipt());
    }
}



TEST_CASE("MultipleOutputFiles3")
{
    Dinner dinner("Wine", 59);
    dinner.writeAllReceipts();
    SECTION("BusinessReceipt")
    {
       // Approvals::verifyExistingFile("file1.txt");
        Approvals::verify(readFile("file1.txt"));
    }
    SECTION("PersonalReceipt")
    {
        //Approvals::verifyExistingFile("file2.txt");
          Approvals::verify(readFile("file2.txt"));
    }
}
