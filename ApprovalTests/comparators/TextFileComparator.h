#pragma once

#include "ApprovalTests/core/ApprovalComparator.h"

#include <fstream>

namespace ApprovalTests
{
    class TextFileComparator : public ApprovalComparator
    {
    public:
        static std::ifstream::int_type getNextRelevantCharacter(std::ifstream& astream);

        virtual bool contentsAreEquivalent(std::string receivedPath,
                                           std::string approvedPath) const override;
    };
}
