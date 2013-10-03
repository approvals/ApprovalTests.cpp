#include <iostream>
#include <string>
#include <unistd.h>
#include "Tomato.h"
using namespace std;

int main( int argc, char const *argv[] )
{
    FileListener out( "Tomato.txt" );
    MessageCache cache( 5 );
    LogManager logger;
    logger.AddListener( cache );
    logger.AddListener( out );

    Tomato pom( logger );

    while ( 1 )
    {
        char input;
        string response;
        cout << cache.Messages() << endl;
        cout << pom.Menu();

        while ( cin.get( input ) && input != ( char ) '\n' )
        {
            response.push_back( input );
        }

        Timer &t = pom.Next( response );

        while ( !t.IsExpired() )
        {
            cout << ".";
            cout.flush();
            sleep( 1 );
        }

        cout << endl;
    }

    return 0;
}