#ifndef APPROVALTESTS_CPP_STRINGWRITER_H
#define APPROVALTESTS_CPP_STRINGWRITER_H

#include <string>
#include <fstream>
#include <exception>
#include "ApprovalWriter.h"

class StringWriter : public ApprovalWriter
{
private:
    std::string s;
    std::string ext;

public:
    StringWriter( std::string contents, std::string fileExtensionWithDot = ".txt" )
        : s( contents ), ext( fileExtensionWithDot ) {}

    std::string getFileExtensionWithDot() override
    {
        return ext;
    }

    void write( std::string path ) override
    {
        std::ofstream out( path.c_str(), std::ofstream::out );
        if ( ! out)
        {
            throw std::runtime_error("Unable to write file: " + path);
        }
        this->Write( out );
        out.close();
    }

    void Write( std::ostream &out )
    {
        out << s << "\n";
    }

    virtual void cleanUpReceived(std::string receivedPath) override {
        remove(receivedPath.c_str());
    }


};
#endif