#ifndef FILELISTENER_H
#define FILELISTENER_H

#include <fstream>
#include "LogListener.h"

class FileListener : public LogListener
{
private:
    std::ofstream oh;

public:
    FileListener( const char *path );
    void Insert( std::string message );
};
#endif