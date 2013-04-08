#include <igloo/igloo.h>
#include <fstream>
#include "../StringWriter.h"

using namespace igloo;
using namespace std;


Context( DescribeAStringWriter )
{
    Spec( ItWritesTheContentsToAFile )
    {
        StringWriter s( "Hello" );
        s.Write( "out.txt" );

        ifstream in( "out.txt", ifstream::in );
        stringstream written;
        written << in.rdbuf();
        in.close();
        remove( "out.txt" );
        Assert::That( written.str(), Equals( "Hello" ) );
    }

    Spec( ItWritesTheContentsToAStream )
    {
        stringstream out;
        StringWriter s( "Hello" );
        s.Write( out );
        Assert::That( out.str(), Equals( "Hello" ) );
    }

    Spec( TheDefaultExtensionIsText )
    {
        StringWriter s( "Hello" );
        Assert::That( s.GetFileExtension(), Equals( "txt" ) );
    }

    Spec( TheExtensionIsConfigurable )
    {
        StringWriter s( "Hello", "html" );
        Assert::That( s.GetFileExtension(), Equals( "html" ) );
    }
};

int main( int argc, char const *argv[] )
{
    return TestRunner::RunAllTests();
}