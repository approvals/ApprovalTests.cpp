#ifndef APPROVALEXCEPTION_H
#define APPROVALEXCEPTION_H

#include <cstring>
#include <exception>
#include <string>
#include <stdio.h>

class ApprovalException : public std::exception
{
private:
    char *message;
protected:
    char *init( const char *msg )
    {
        size_t message_sz = std::strlen( msg );
        char *t = new char[message_sz + 1];
        std::strncpy( t, msg, message_sz + 1 );
        return t;
    };
public:
    ApprovalException( const char *msg ) : message( init( msg ) ) {}

    ApprovalException( const ApprovalException &a )
        : message( init( a.message ) )
    {
    }

    virtual ~ApprovalException() throw()
    {
        delete[] message;
    }

    virtual const char *what() const throw()
    {
        return message;
    }
};

class ApprovalMismatchException : public ApprovalException
{
private:
    char *format( const std::string &received, const std::string &approved )
    {
        size_t n = 2048;
        char s[n];
        int size = snprintf( s,
                             n,
                             "Failed Approval: Received file %s does not match approved file %s.",
                             received.c_str(),
                             approved.c_str() );
        char *t = new char[size + 1];
        std::strncpy( t, s, size + 1 );
        return t;
    }
public:
    ApprovalMismatchException( std::string received, std::string approved )
        : ApprovalException( format( received, approved ) )
    {
    }

    ApprovalMismatchException( const ApprovalMismatchException &a )
        : ApprovalException( a ) {}
};

class ApprovalMissingException : public ApprovalException
{
private:
    char *format( const std::string &file )
    {
        size_t n = 1024;
        char s[n];
        int size = snprintf( s,
                             n,
                             "Failed Approval: Approval File \"%s\" Not Found.",
                             file.c_str() );
        char *t = new char[size + 1];
        std::strncpy( t, s, size + 1 );
        return t;
    }
public:
    ApprovalMissingException( std::string received, std::string approved )
        : ApprovalException( format( approved ) )
    {
    }

    ApprovalMissingException( const ApprovalMissingException &a )
        : ApprovalException( a )
    {
    }
};

#endif