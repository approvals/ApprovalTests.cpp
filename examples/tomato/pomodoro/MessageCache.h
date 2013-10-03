#ifndef MESSAGECACHE_H
#define MESSAGECACHE_H

#include <deque>
#include <sstream>
#include <string>
#include "LogListener.h"

class MessageCache : public LogListener
{
public:
    MessageCache( unsigned int size );
    void Insert( std::string message );
    std::string Messages();
private:
    unsigned int max;
    std::deque<std::string> cache;
};
#endif