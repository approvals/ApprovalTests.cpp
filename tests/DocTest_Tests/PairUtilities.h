#ifndef APPROVALTESTS_CPP_PAIR_UTILITIES_HPP
#define APPROVALTESTS_CPP_PAIR_UTILITIES_HPP

#include <map>
#include <ostream>

namespace ApprovalTests
{
    inline std::ostream& operator<<(std::ostream& os,
                                    const std::pair<std::string, int>& pair)
    {
        os << "(" << pair.first << ", " << pair.second << ")";
        return os;
    }
}PP
