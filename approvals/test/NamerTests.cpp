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

    Spec( ItCanGiveYouTheTestName )
    {
        char buf[512];
        bzero( buf, 512 );
        ssize_t readlink_ok = readlink( "/proc/self/exe", buf, 512 );
        Assert::That( readlink_ok, IsGreaterThan( -1 ) );
        string exe( buf );
        unsigned slash = exe.find_last_of( "/" );
        exe = exe.substr( slash + 1, exe.size() + 1 );
        Assert::That( IglooNamerFactory::TestName(), Equals( exe ) );

    }

    Spec( ItCanGiveYouTheTestDirectory )
    {
        char buf[512];
        bzero( buf, 512 );
        ssize_t readlink_ok = readlink( "/proc/self/exe", buf, 512 );
        Assert::That( readlink_ok, IsGreaterThan( -1 ) );
        string dir( buf );
        unsigned slash = dir.find_last_of( "/" );
        dir = dir.substr( 0, slash );
        Assert::That( IglooNamerFactory::TestDirectory(), Equals( dir ) );
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
