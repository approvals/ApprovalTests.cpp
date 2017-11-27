#include <igloo/igloo.h>
#include <sstream>
#include "../namers/Namer.h"
#include "../namers/IglooNamerFactory.h"

using namespace igloo;
using namespace std;

Context( DescribeAnIglooNamerFactory )
{
    Spec( ItCanGiveYouTheSpecName )
    {
        Assert::That( IglooNamerFactory::SpecName(),
                      Equals( "ItCanGiveYouTheSpecName" ) );
    }

    Spec( ItCanGiveYouTheContextName )
    {
        Assert::That( IglooNamerFactory::ContextName(), Equals( Name() ) );
    }

    Spec( ItCanGiveYouTheTestFileName )
    {
        Assert::That( IglooNamerFactory::TestName(), Equals( "NamerTests" ) );

    }

    Spec( ItCanGiveYouTheTestDirectory )
    {
        Assert::That( IglooNamerFactory::TestDirectory(), EndsWith("approvals/./test/bin") );
    }

    Spec( ItIncludesFileContextAndSpecNames )
    {
        stringstream expected;
        expected << IglooNamerFactory::TestDirectory() << "/NamerTests" <<
                 ".DescribeAnIglooNamerFactory" <<
                 ".ItIncludesFileContextAndSpecNames" <<
                 ".approved.txt";

        Namer n = IglooNamerFactory::GetCurrentNamer();
        Assert::That( n.GetApprovedFile( ".txt" ), Equals( expected.str() ) );
    }
};

Context( DescribeANamer )
{
    Context( Normalization )
    {
        Spec( ItCleansInput )
        {
            Assert::That( n->GetApprovedFile( ".txt" ),
                          Equals( "/tmp/foo.cpp.approved.txt" ) );
        }

        // cppcheck-suppress unusedFunction
        void SetUp()
        {
            n = new Namer( "/tmp/", "foo.cpp." );
        }

        // cppcheck-suppress unusedFunction
        void TearDown()
        {
            delete n;
        }

        Namer *n;
    };

    Context( BasicFunctionality )
    {
        Spec( ItProvidesTheApprovedFilename )
        {
            Assert::That( n->GetApprovedFile( "png" ),
                          Equals( "/tmp/foo.cpp.approved.png" ) );
        }

        Spec( ItProvidesTheReceivedFilename )
        {
            Assert::That( n->GetReceivedFile( "txt" ),
                          Equals( "/tmp/foo.cpp.received.txt" ) );
        }

        void SetUp()
        {
            path = string( "/tmp" );
            name = string( "foo.cpp" );
            n = new Namer( path, name );
        }

        void TearDown()
        {
            delete n;
        }

        string name;
        string path;
        Namer *n;
    };
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
