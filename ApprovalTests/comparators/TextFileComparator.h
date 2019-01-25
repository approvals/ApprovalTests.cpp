#ifndef APPROVALTESTS_CPP_TEXTFILECOMPARATOR_H
#define APPROVALTESTS_CPP_TEXTFILECOMPARATOR_H

#include "ApprovalComparator.h"

class TextFileComparator
{
public:
    static ApprovalComparator getComparator()
    {
        return &TextFileComparator::contentsAreEquivalent;
    }

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

    static bool contentsAreEquivalent(std::string receivedPath,
                                      std::string approvedPath)
    {
        std::ifstream astream(approvedPath.c_str(),
                              std::ios::binary | std::ifstream::in);
        std::ifstream rstream(receivedPath.c_str(),
                              std::ios::binary | std::ifstream::in);

        while (astream.good() && rstream.good()) {
            int a = getNextRelevantCharacter(astream);
            int r = getNextRelevantCharacter(rstream);

            if (a != r) {
                return false;
            }
        }
        return true;
    }
};
#endif //APPROVALTESTS_CPP_TEXTFILECOMPARATOR_H
