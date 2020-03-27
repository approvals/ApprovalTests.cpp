// begin-snippet: doctest_existing_main
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_DOCTEST_EXISTING_MAIN
#include "ApprovalTests.hpp"
// end-snippet

int main(int argc, char** argv)
{
    return doctest::Context(argc, argv).run();
}
