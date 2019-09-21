// begin-snippet: catch_existing_main
// main.cpp:

// Add these two lines to your main:
#define APPROVALS_CATCH_EXISTING_MAIN
#include "ApprovalTests.hpp"

int main( int argc, char* argv[] )
{
    // your existing setup...
    int result = Catch::Session().run( argc, argv );
    // your existing clean-up...
    return result;
}
// end-snippet
