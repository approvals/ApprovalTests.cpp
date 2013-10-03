#include "FileListener.h"

FileListener::FileListener( const char *path )
    : oh( path, std::ofstream::out )
{

}

void FileListener::Insert( std::string message )
{
    oh << message << std::endl;
}