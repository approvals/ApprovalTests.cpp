#include <igloo/igloo.h>
#include <approvals/Approvals.h>
#include <Menus.h>

using namespace igloo;

Context( DescribeTheMainMenu )
{
    Spec( ItOffersToStartATomato )
    {
        Menus m;
        Approvals::Verify( m.MainMenu() );
    }
};

Context( DescribeTheTomatoFinishedMenu )
{
    Spec( ItAsksYouWhatYouDid )
    {
        Menus m;
        Approvals::Verify( m.TomatoFinishedMenu() );
    }
};

Context( DescribeTheBreakMenu )
{
    Spec( ItOffersSeveralBreakOptions )
    {
        Menus m;
        Approvals::Verify( m.BreakMenu() );
    }
};

Context( DescribeBackToWorkPrompt )
{
    Spec( ItOffersToStartATomato )
    {
        Menus m;
        Approvals::Verify( m.BackToWorkMenu() );
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