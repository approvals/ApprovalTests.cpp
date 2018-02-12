#ifndef APPROVALEXCEPTION_H
#define APPROVALEXCEPTION_H

#include <cstring>
#include <exception>
#include <string>
#include <stdio.h>
#include <sstream>

class ApprovalException : public std::exception
{
private:
    std::string message;
public:
    ApprovalException( const std::string& msg ) : message( msg ) {}

    virtual const char *what() const throw()
    {
        return message.c_str();
    }
};

class ApprovalMismatchException : public ApprovalException
{
private:
    char *format( const std::string &received, const std::string &approved )
    {
		static const int n = 2048;
        char s[n];
        int size = snprintf( s,
                             n,
                             "Failed Approval: \n"
                                     "Received does not match approved \n"
                                     "Received : \"%s\" \n"
                                     "Approved : \"%s\"",
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
    std::string format( const std::string &file )
    {
        std::stringstream s;
        s << "Failed Approval: \n"
          << "Approval File Not Found \n"
          << "File: \"" << file << '"';
        return s.str();
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