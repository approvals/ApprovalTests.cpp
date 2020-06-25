#include "ApprovalTests/comparators/TextFileComparator.h"

#include <fstream>

namespace ApprovalTests
{
    std::ifstream::int_type
    TextFileComparator::getNextRelevantCharacter(std::ifstream& astream)
    {
        auto ch = astream.get();
        if (ch == '\r')
        {
            return astream.get();
        }
        else
        {
            return ch;
        }
    }

    bool TextFileComparator::contentsAreEquivalent(std::string receivedPath,
                                                   std::string approvedPath) const
    {
        std::ifstream astream(approvedPath.c_str(), std::ios::binary | std::ifstream::in);
        std::ifstream rstream(receivedPath.c_str(), std::ios::binary | std::ifstream::in);

        while (astream.good() && rstream.good())
        {
            int a = getNextRelevantCharacter(astream);
            int r = getNextRelevantCharacter(rstream);

            if (a != r)
            {
                return false;
            }
        }
        return true;
    }
}
