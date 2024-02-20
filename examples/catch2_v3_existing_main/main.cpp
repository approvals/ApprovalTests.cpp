// begin-snippet: catch2_v3_existing_main
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_CATCH2_V3
#include "ApprovalTests.hpp"
#include <catch2/catch_session.hpp>
// end-snippet

#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "macros defined:\n";
#ifdef _WIN32
    std::cout << "_WIN32 defined\n";
#endif

#ifdef __CYGWIN__
    std::cout << "__CYGWIN__ defined\n";
#endif

#ifdef __APPLE__
    std::cout << "__APPLE__ defined\n";
#endif

    // your existing setup...
    int result = Catch::Session().run(argc, argv);

    // your existing clean-up...
    return result;
}
