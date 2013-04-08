#ifndef NAMER_H
#define NAMER_H

#include <string>

class Namer
{
private:
    std::string approvalPath;
    std::string fileName;

    std::string CreatePath( std::string fileExtension, std::string fileType )
    {
        std::string name( fileName +
                          "." + fileType +
                          "." + EraseFirst( fileExtension, '.' ) );
        std::string p = approvalPath + "/" + name;
        return p;
    }

    std::string EraseFirst( std::string s, char c )
    {
        std::string::iterator it = s.begin();

        if ( *it == c )
        {
            s.erase( it );
        }

        return s;
    }

    std::string EraseLast( std::string s, char c )
    {
        std::string::iterator it = s.end();
        --it;

        if ( *it == c )
        {
            s.erase( it );
        }

        return s;
    }

    std::string NameClean( std::string name )
    {
        return EraseLast( name, '.' );
    }

    std::string PathClean( std::string path )
    {
        return EraseLast( path, '/' );
    }

public:
    Namer( std::string path, std::string name )
        : approvalPath( PathClean( path ) ), fileName( NameClean( name ) ) {}

    std::string GetApprovedFile( std::string fileExtension )
    {
        return CreatePath( fileExtension, "approved" );
    }

    std::string GetReceivedFile( std::string fileExtension )
    {
        return CreatePath( fileExtension, "received" );
    }
};


#endif
