#ifndef APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H
#define APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H

#include <type_traits>
#include "reporters/DefaultReporter.h"
#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/utilities/CartesianProduct.h"
#include "Approvals.h"

namespace ApprovalTests {
namespace CombinationApprovals {
namespace Detail {

// C++17 compatibility
// TODO What does disjunction do?
template<class...> struct disjunction : std::false_type {};
template<class B1> struct disjunction<B1> : B1 {};
template<class B1, class... Bn>
struct disjunction<B1, Bn...> : std::conditional<bool(B1::value), B1, disjunction<Bn...>>::type  {};
// End of C++17 compatibility

// Write out second or subsequent input value, with preceding comma and space
struct print_input {
    std::ostream& out;
    template<class T>
    void operator()(const T& input) {
        out << ", " << input;
    }
};

// Write out one row of output
template<class Converter>
struct serialize {
    std::ostream& out;
    Converter converter;
    template<class T, class... Ts>
    void operator()(T&& input1, Ts&&... inputs) {
        // First value is printed without trailing comma
        out << "(" << input1;
        // Remaining values are printed with prefix of a comma
        CartesianProduct::Detail::for_each(std::forward_as_tuple(inputs...), print_input{out});
        out << ") => " << converter(input1, inputs...) << '\n';
    }
};
} // namespace Detail

template<class Converter, class Container, class... Containers>
void verifyAllCombinations(Converter&& converter, const Reporter& reporter, const Container& input0, const Containers&... inputs)
{
    std::stringstream s;
    CartesianProduct::cartesian_product(Detail::serialize<Converter>{s, std::forward<Converter>(converter)}, input0, inputs...);
    Approvals::verify(s.str(), reporter);
}

template<class Converter, class... Containers>
CartesianProduct::Detail::enable_if_t<!Detail::disjunction<std::is_base_of<Reporter, Containers>...>::value>
verifyAllCombinations(Converter&& converter, const Containers&... inputs)
{
    verifyAllCombinations(std::forward<Converter>(converter), DefaultReporter(), inputs...);
}

// These are here for backwards compatibility
// Maybe they should be deprecated and removed in the future?
template<class Converter, class C1>
void verifyAllCombinations(Converter&& converter, const C1& i1, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1);
}

template<class Converter, class C1, class C2>
void verifyAllCombinations(Converter&& converter, const C1& i1, const C2& i2, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1, i2);
}

template<class Converter, class C1, class C2, class C3>
void verifyAllCombinations(Converter&& converter, const C1& i1, const C2& i2, const C3& i3, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1, i2, i3);
}

template<class Converter, class C1, class C2, class C3, class C4>
void verifyAllCombinations(Converter&& converter, const C1& i1, const C2& i2, const C3& i3, const C4& i4, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1, i2, i3, i4);
}

template<class Converter, class C1, class C2, class C3, class C4, class C5>
void verifyAllCombinations(Converter&& converter, const C1& i1, const C2& i2, const C3& i3, const C4& i4, const C5& i5, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1, i2, i3, i4, i5);
}

template<class Converter, class C1, class C2, class C3, class C4, class C5, class C6>
void verifyAllCombinations(Converter&& converter, const C1& i1, const C2& i2, const C3& i3, const C4& i4, const C5& i5, const C6& i6, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1, i2, i3, i4, i5, i6);
}

template<class Converter, class C1, class C2, class C3, class C4, class C5, class C6, class C7>
void verifyAllCombinations(Converter&& converter, const C1& i1, const C2& i2, const C3& i3, const C4& i4, const C5& i5, const C6& i6, const C7& i7, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1, i2, i3, i4, i5, i6, i7);
}

template<class Converter, class C1, class C2, class C3, class C4, class C5, class C6, class C7, class C8>
void verifyAllCombinations(Converter&& converter, const C1& i1, const C2& i2, const C3& i3, const C4& i4, const C5& i5, const C6& i6, const C7& i7, const C8& i8, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1, i2, i3, i4, i5, i6, i7, i8);
}

template<class Converter, class C1, class C2, class C3, class C4, class C5, class C6, class C7, class C8, class C9>
void verifyAllCombinations(Converter&& converter, const C1& i1, const C2& i2, const C3& i3, const C4& i4, const C5& i5, const C6& i6, const C7& i7, const C8& i8, const C9& i9, const Reporter& reporter)
{
    verifyAllCombinations(std::forward<Converter>(converter), reporter, i1, i2, i3, i4, i5, i6, i7, i8, i9);
}

} // namespace CombinationApprovals
} // namespace ApprovalTests

#endif
