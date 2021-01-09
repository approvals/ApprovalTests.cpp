#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/CombinationApprovals.h"

#include <deque>

using namespace ApprovalTests;

// By using private inheritance, we hide everything supplied by STL containers
// except the things that we explicitly expose via using statements.
//
// This allows us to:
// 1. see exactly what is required by our template methods.
// 2. detect in future if we ever accidentally change the requirements
// 3. optionally, add snippets here to document method requirements

namespace VerifyAllOnContainer
{
    using ContainerType = std::deque<int>;

    class MinimalContainerInterfaceForVerifyAll : private ContainerType
    {
    public:
        // Any container with these can be passed Approvals::verifyAll()
        using ContainerType::const_iterator;
        using ContainerType::value_type;
        using ContainerType::begin;
        using ContainerType::end;

        MinimalContainerInterfaceForVerifyAll()
        {
            push_back(10);
            push_back(20);
            push_back(30);
        }
    };

    TEST_CASE("Required interface for verifyAll on container")
    {
        MinimalContainerInterfaceForVerifyAll container;
        Approvals::verifyAll(container);
    }
}

namespace VerifyAllOnIterators
{
    using ContainerType = std::deque<int>;

    class MinimalIteratorInterfaceForVerifyAll : private ContainerType
    {
    public:
        // If passing iterators and a lambda to Approvals::verifyAll(),
        // only these are required:
        using ContainerType::begin;
        using ContainerType::end;

        MinimalIteratorInterfaceForVerifyAll()
        {
            push_back(10);
            push_back(20);
            push_back(30);
        }
    };

    TEST_CASE("Required interface for verifyAll on iterators")
    {
        MinimalIteratorInterfaceForVerifyAll container;
        Approvals::verifyAll("TITLE",
                             container.begin(),
                             container.end(),
                             [](auto value, auto& stream) { stream << value; });
    }
}

namespace VerifyAllOnArray
{
    TEST_CASE("Required interface for verifyAll on C array")
    {
        // If using C-style arrays, we can use the iterator overload of
        // Approvals::verifyAll in conjunction with std::begin() and std::end():
        using ContainerType = int[3];
        ContainerType container = {10, 20, 30};
        Approvals::verifyAll("TITLE",
                             std::begin(container),
                             std::end(container),
                             [](auto value, auto& stream) { stream << value; });
    }
}

namespace VerifyAllCombinationsOnContainer
{
    using ContainerType = std::deque<int>;

    class MinimalContainerInterfaceForVerifyAllCombinations : private ContainerType
    {
    public:
        // Any container with these can be used with
        // CombinationApprovals::verifyAllCombinations()
        using ContainerType::begin;
        using ContainerType::end;

        MinimalContainerInterfaceForVerifyAllCombinations()
        {
            push_back(10);
            push_back(20);
            push_back(30);
        }
    };

    TEST_CASE("Required interface for verifyAllCombinations")
    {
        MinimalContainerInterfaceForVerifyAllCombinations container;

        CombinationApprovals::verifyAllCombinations(
            [](auto value1, auto value2) {
                return std::to_string(value1) + "," + std::to_string(value2);
            },
            container,
            container);
    }
}
