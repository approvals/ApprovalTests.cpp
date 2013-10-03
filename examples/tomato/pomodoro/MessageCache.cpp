#include "MessageCache.h"

MessageCache::MessageCache( unsigned int size ) : max( size ) {}

void MessageCache::Insert( std::string message )
{
    cache.push_back( message );

    if ( max < cache.size() )
    {
        cache.pop_front();
    }
}

std::string MessageCache::Messages()
{
    std::stringstream t( "" );

    for ( std::deque<std::string>::iterator it = cache.begin();
            it != cache.end();
            ++it )
    {
        t << *it;
    }

    return t.str();
}