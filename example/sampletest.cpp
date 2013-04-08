#include <Approvals.h>
#include <igloo/igloo.h>

using namespace igloo;

Context( VerifyingTextWithApprovals )
{
    Spec( ItWorksWithIgloo )
    {
        Approvals::Verify( "Igloo is better with Approvals." );
    }
};

int main( int argc, char const *argv[] )
{
    DefaultTestResultsOutput output;
    TestRunner runner( output );

    IglooMetadataListener listener;
    runner.AddListener( &listener );
    MinimalProgressTestListener mpl;
    runner.AddListener( &mpl );

    return runner.Run();
}
