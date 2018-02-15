#ifndef COMBINATIONAPPROVALS_H
#define COMBINATIONAPPROVALS_H

#include <string>
#include <functional>
#include <vector>
#include "reporters/DiffReporter.h"
#include "reporters/Reporter.h"
#include "Approvals.h"

#define EMPTY std::vector<int>{-424242}

class CombinationApprovals
{
public:
    CombinationApprovals() = delete;
    ~CombinationApprovals() = delete;

    template <typename Container1, typename Container2, typename ReturnType>
    static void verifyAllCombinations(
                          std::function<ReturnType (typename Container1::value_type, typename Container2::value_type)> converter,
                          const Container1& inputs1,
                          const Container2& inputs2,
                          const Reporter& reporter = DiffReporter())
    {
        auto empty = EMPTY;
        std::stringstream s;
        for (auto input1 : inputs1)
        {
            for (auto input2 : inputs2)
            {
                ReturnType result = converter(input1, input2);
                s << "(" << input1;
                if ( inputs2 != empty)
                {
                    s << ", " << input2;
                }
                s << ") => " << result << '\n';
            }
        }
        Approvals::verify(s.str(), reporter);
    }

    template <typename Container1, typename ReturnType>
    static void verifyAllCombinations(
            std::function<ReturnType (typename Container1::value_type)> converter,
            const Container1& inputs1,
            const Reporter& reporter = DiffReporter())
    {
        verifyAllCombinations<Container1, std::vector<int>, ReturnType>([&](typename Container1::value_type i1, int i2){return converter(i1);}, inputs1, EMPTY);
    }
};

#endif
