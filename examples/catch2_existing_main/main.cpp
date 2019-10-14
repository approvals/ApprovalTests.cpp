// begin-snippet: catch_existing_main
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_CATCH_EXISTING_MAIN
#include "ApprovalTests.hpp"
// end-snippet

int main( int argc, char* argv[] )
{
    // your existing setup...
    int result = Catch::Session().run( argc, argv );
    // your existing clean-up...
    return result;
}
