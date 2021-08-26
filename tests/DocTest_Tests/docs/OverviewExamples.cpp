#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

#include <sstream>
#include <vector>

class StringList
{
public:
    bool contains(const std::string& value) const
    {
        auto iter = std::find(contents.begin(), contents.end(), value);
        return (iter != contents.end());
    }
    std::string toString() const
    {
        std::stringstream os;
        bool written = false;
        os << "[";
        for (const auto& thing : contents)
        {
            if (written)
            {
                os << ", ";
            }
            else
            {
                written = true;
            }
            os << '"' << thing << '"';
        }
        os << "]";
        return os.str();
    }

public:
    using Contents = std::vector<std::string>;
    Contents contents;
};

class Sandwich
{
public:
    std::string getBread() const
    {
        return bread;
    }

    StringList getCondiments() const
    {
        return condiments;
    }

    StringList getFillings() const
    {
        return fillings;
    }

public:
    std::string bread;
    StringList condiments;
    StringList fillings;
};

static Sandwich createSandwichForTest()
{
    Sandwich result;
    result.bread = "Sourdough";
    result.condiments.contents = {"Mayo", "Pepper", "Olive Oil"};
    result.fillings.contents = {"Tomato", "Lettuce", "Cheddar"};
    return result;
}

std::ostream& operator<<(std::ostream& os, const Sandwich& sandwich)
{
    os << "sandwich {\n";
    os << "    bread: \"" << sandwich.bread << "\",\n";
    os << "    condiments: " << sandwich.condiments.toString() << ",\n";
    os << "    fillings: " << sandwich.fillings.toString() << "\n";
    os << "}";
    return os;
}

TEST_CASE("SandwichExampleWithRequires")
{
    // begin-snippet: sandwich_example_with_requires
    // Arrange, Act
    Sandwich s = createSandwichForTest();
    // Assert
    REQUIRE("Sourdough" == s.getBread());
    REQUIRE(s.getCondiments().contains("Mayo"));
    REQUIRE(s.getCondiments().contains("Pepper"));
    REQUIRE(s.getCondiments().contains("Olive Oil"));
    REQUIRE(s.getFillings().contains("Tomato"));
    REQUIRE(s.getFillings().contains("Lettuce"));
    REQUIRE(s.getFillings().contains("Cheddar"));
    // end-snippet
}

TEST_CASE("SandwichExampleWithApprovals")
{
    // begin-snippet: sandwich_example_with_approvals
    // Arrange, Act
    Sandwich s = createSandwichForTest();
    // Assert
    ApprovalTests::Approvals::verify(s);
    // end-snippet
}
