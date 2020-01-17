#include <catch2/catch.hpp>
#include <ApprovalTests.hpp>

TEST_CASE("test hello-world")
{
    ApprovalTests::Approvals::verify("Hello World");
}
