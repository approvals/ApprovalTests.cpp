#include <igloo/igloo.h>
#include "../ApprovalException.h"

using namespace igloo;
using namespace std;

Context( DescribeApprovalExceptions )
{
    Spec( ApprovalMissingExceptionHasAMessage )
    {
        ApprovalMissingException a( "r.txt", "a.txt" );
        Assert::That( a.what(),
                      Equals( "Failed Approval: Approval File \"a.txt\" Not Found." ) );
    }

    Spec( ApprovalMismatchExceptionHasAMessage )
    {
        ApprovalMismatchException a( "r.txt", "a.txt" );
        Assert::That( a.what(),
                      Equals( "Failed Approval: Received file r.txt does not match approved file a.txt." ) );
    }
};

int main( int argc, char const *argv[] )
{
    return TestRunner::RunAllTests();
}