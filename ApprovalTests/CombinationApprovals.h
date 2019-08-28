#ifndef APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H
#define APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H

#include <functional>
#include <vector>
#include <ostream>
#include "reporters/DefaultReporter.h"
#include "reporters/Reporter.h"
#include "Approvals.h"

namespace ApprovalTests {
class Empty
{
public:
    template< typename Other>
    bool operator!=(const Other &/*rhs*/) const {
        return true;
    }

    bool operator!=(const Empty &/*rhs*/) const {
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Empty&) {
        os << "This should never be written - see Empty\n";
        return os;
    }

};

class CombinationApprovals
{
public:
    CombinationApprovals() = delete;
    ~CombinationApprovals() = delete;

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename Container6,
        typename Container7,
        typename Container8,
        typename Container9,
        typename = IsNotDerivedFromReporter<Container9>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Container6& inputs6,
        const Container7& inputs7,
        const Container8& inputs8,
        const Container9& inputs9,
        const Reporter& reporter = DefaultReporter())
    {
        Empty empty;
        std::stringstream s;
        for (auto input1 : inputs1)
        {
            for (auto input2 : inputs2)
            {
                for (auto input3 : inputs3)
                {
                    for (auto input4 : inputs4)
                    {
                        for (auto input5 : inputs5)
                        {
                            for (auto input6 : inputs6)
                            {
                                for (auto input7 : inputs7)
                                {
                                    for (auto input8 : inputs8)
                                    {
                                        for (auto input9 : inputs9)
                                        {
                                            s << "(" << input1;
                                            if (empty != input2) { s << ", " << input2; }
                                            if (empty != input3) { s << ", " << input3; }
                                            if (empty != input4) { s << ", " << input4; }
                                            if (empty != input5) { s << ", " << input5; }
                                            if (empty != input6) { s << ", " << input6; }
                                            if (empty != input7) { s << ", " << input7; }
                                            if (empty != input8) { s << ", " << input8; }
                                            if (empty != input9) { s << ", " << input9; }
                                            s << ") => " << converter(input1, input2, input3, input4, input5,
                                                                      input6, input7, input8, input9) << '\n';
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        Approvals::verify(s.str(), reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename Container6,
        typename Container7,
        typename Container8,
        typename = IsNotDerivedFromReporter<Container8>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Container6& inputs6,
        const Container7& inputs7,
        const Container8& inputs8,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                typename Container5::value_type i5,
                typename Container6::value_type i6,
                typename Container7::value_type i7,
                typename Container8::value_type i8,
                Empty){return converter(i1, i2, i3, i4, i5, i6, i7, i8);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            inputs5,
            inputs6,
            inputs7,
            inputs8,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename Container6,
        typename Container7,
        typename = IsNotDerivedFromReporter<Container7>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Container6& inputs6,
        const Container7& inputs7,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                typename Container5::value_type i5,
                typename Container6::value_type i6,
                typename Container7::value_type i7,
                Empty){return converter(i1, i2, i3, i4, i5, i6, i7);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            inputs5,
            inputs6,
            inputs7,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename Container6,
        typename = IsNotDerivedFromReporter<Container6>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Container6& inputs6,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                typename Container5::value_type i5,
                typename Container6::value_type i6,
                Empty){return converter(i1, i2, i3, i4, i5, i6);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            inputs5,
            inputs6,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename Container5,
        typename = IsNotDerivedFromReporter<Container5>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Container5& inputs5,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                typename Container5::value_type i5,
                Empty){return converter(i1, i2, i3, i4, i5);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            inputs5,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename Container4,
        typename = IsNotDerivedFromReporter<Container4>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Container4& inputs4,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                typename Container4::value_type i4,
                Empty){return converter(i1, i2, i3, i4);},
            inputs1,
            inputs2,
            inputs3,
            inputs4,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename Container3,
        typename = IsNotDerivedFromReporter<Container3>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Container3& inputs3,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                typename Container3::value_type i3,
                Empty){return converter(i1, i2, i3);},
            inputs1,
            inputs2,
            inputs3,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename Container2,
        typename = IsNotDerivedFromReporter<Container2>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Container2& inputs2,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                typename Container2::value_type i2,
                Empty){return converter(i1, i2);},
            inputs1,
            inputs2,
            empty(),
            reporter);
    }

    template <
        typename Function,
        typename Container1,
        typename = IsNotDerivedFromReporter<Container1>>
    static void verifyAllCombinations(
        Function converter,
        const Container1& inputs1,
        const Reporter& reporter = DefaultReporter())
    {
        verifyAllCombinations(
            [&](typename Container1::value_type i1,
                Empty){return converter(i1);},
            inputs1,
            empty(),
            reporter);
    }

    // Implementation details: these are left public to allow users
    // to write additional verifyAllCombinations overloads that take more
    // than 9 arguments - unlikely though that may be.
    using EmptyContainer = std::vector<Empty>;
    static EmptyContainer empty()
    {
        return EmptyContainer{Empty()};
    }
};
}

#endif
