#ifndef COMBINATIONAPPROVALS_H
#define COMBINATIONAPPROVALS_H

#include <string>
#include <functional>
#include "reporters/DiffReporter.h"
#include "reporters/Reporter.h"
#include "Approvals.h"

class CombinationApprovals
{
public:
    CombinationApprovals() = delete;
    ~CombinationApprovals() = delete;

    template <typename Container1, typename ReturnType>
    static void verifyAllCombinations(
                          std::function<ReturnType (typename Container1::value_type)> converter,
                          const Container1& inputs1,
                          const Reporter& reporter = DiffReporter())
    {
        std::stringstream s;
        for (auto input1 : inputs1)
        {
            ReturnType result = converter(input1);
            s << "(" << input1 << ") => " << result << '\n';
        }
        Approvals::verify(s.str(), reporter);
    }

    template <typename Container1, typename Container2, typename ReturnType>
    static void verifyAllCombinations(
                          std::function<ReturnType (typename Container1::value_type, typename Container2::value_type)> converter,
                          const Container1& inputs1,
                          const Container2& inputs2,
                          const Reporter& reporter = DiffReporter())
    {
        std::stringstream s;
        for (auto input1 : inputs1)
        {
            for (auto input2 : inputs2)
            {
                ReturnType result = converter(input1, input2);
                s << "(" << input1 << ", " << input2 << ") => " << result << '\n';
            }
        }
        Approvals::verify(s.str(), reporter);
    }

};

#endif
