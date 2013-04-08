#ifndef FILEAPPROVER_H
#define FILEAPPROVER_H

#include <fstream>
#include <sys/stat.h>
#include "ApprovalException.h"
#include "namers/Namer.h"
#include "StringWriter.h"
#include "reporters/Reporter.h"

class FileApprover
{
protected:
    FileApprover() {};
    ~FileApprover() {};

    static ApprovalException *Verify( std::string receivedPath,
                                      std::string approvedPath )
    {
        int asize = FileSize( approvedPath );

        if ( -1 == asize )
        {
            return new ApprovalMissingException( receivedPath, approvedPath );
        }

        int rsize = FileSize( receivedPath );

        if ( -1 == rsize )
        {
            return new ApprovalMissingException( approvedPath, receivedPath );
        }

        if ( asize != rsize )
        {
            return new ApprovalMismatchException( receivedPath, approvedPath );
        }

        std::ifstream astream( approvedPath.c_str(),
                               std::ios::binary | std::ifstream::in );
        std::ifstream rstream( receivedPath.c_str(),
                               std::ios::binary | std::ifstream::in );

        while ( astream.good() && rstream.good() )
        {
            int a = astream.get();
            int r = rstream.get();

            if ( a != r )
            {
                return new ApprovalMismatchException( receivedPath, approvedPath );
            }
        }

        remove( receivedPath.c_str() );
        return NULL;
    }

public:
    static bool FileExists( std::string path )
    {
        return FileSize( path ) != -1;
    }

    static int FileSize( std::string path )
    {
        struct stat statbuf;
        int stat_ok = stat( path.c_str(), &statbuf );

        if ( stat_ok == -1 )
        {
            return -1;
        }

        return int( statbuf.st_size );
    }

    static void Verify( Namer n, StringWriter s, Reporter r )
    {
        std::string approvedPath = n.GetApprovedFile( ".txt" );
        std::string receivedPath = n.GetReceivedFile( ".txt" );
        s.Write( receivedPath );
        ApprovalException *ae = Verify( receivedPath, approvedPath );

        if ( ae != NULL )
        {
            r.Report( receivedPath, approvedPath );
            ApprovalException e( *ae );
            delete ae;
            throw e;
        }
    }
};

#endif