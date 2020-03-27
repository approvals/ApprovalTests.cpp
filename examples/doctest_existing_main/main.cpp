#define APPROVALS_DOCTEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

int main(int argc, char** argv)
{
    return doctest::Context(argc, argv).run();
}
