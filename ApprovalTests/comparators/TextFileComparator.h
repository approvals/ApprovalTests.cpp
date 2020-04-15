#pragma once

#include "ApprovalTests/core/ApprovalComparator.h"

namespace ApprovalTests
{
    class TextFileComparator : public ApprovalComparator
    {
    public:
        static std::ifstream::int_type getNextRelevantCharacter(std::ifstream& astream)
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

        virtual bool contentsAreEquivalent(std::string receivedPath,
                                           std::string approvedPath) const override
        {
            std::ifstream astream(approvedPath.c_str(),
                                  std::ios::binary | std::ifstream::in);
            std::ifstream rstream(receivedPath.c_str(),
                                  std::ios::binary | std::ifstream::in);

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
    };
}
