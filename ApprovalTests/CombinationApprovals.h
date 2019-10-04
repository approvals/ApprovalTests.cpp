#ifndef APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H
#define APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H

#include <functional>
#include <ostream>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include "reporters/DefaultReporter.h"
#include "ApprovalTests/core/Reporter.h"
#include "Approvals.h"

namespace ApprovalTests {
namespace CombinationApprovals {
namespace Detail {

// C++14 compatibility
template<bool B, class T=void>
using enable_if_t = typename std::enable_if<B, T>::type;

template<std::size_t... Is>
struct index_sequence {};

template<std::size_t N, std::size_t... Is>
struct make_index_sequence : make_index_sequence<N-1, N-1, Is...> {};

template<std::size_t... Is>
struct make_index_sequence<0, Is...> : index_sequence<Is...> {};
// End of C++14 compatibility

// Return the size of a tuple - constexpr for use as a template argument
template<class Tuple>
constexpr std::size_t tuple_size() {
    return std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
}

template<class Tuple>
using make_tuple_idxs = make_index_sequence<tuple_size<Tuple>()>;

// C++17 compatibility
template <class F, class Tuple, std::size_t... I>
constexpr auto apply_impl(F&& f, Tuple&& t, index_sequence<I...>)
    -> decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...))
{
    return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
}

template <class F, class Tuple>
auto apply(F&& f, Tuple&& t)
    -> decltype(apply_impl(std::forward<F>(f), std::forward<Tuple>(t), make_tuple_idxs<Tuple>{}))
{
    apply_impl(std::forward<F>(f), std::forward<Tuple>(t), make_tuple_idxs<Tuple>{});
}

// TODO What does disjunction do?
template<class...> struct disjunction : std::false_type {};
template<class B1> struct disjunction<B1> : B1 {};
template<class B1, class... Bn>
struct disjunction<B1, Bn...> : std::conditional<bool(B1::value), B1, disjunction<Bn...>>::type  {};
// End of C++17 compatibility

template <class Tuple, class F, std::size_t... Is>
void for_each_impl(Tuple&& t, F&& f, index_sequence<Is...>) {
    (void)std::initializer_list<int>{
        (std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t))), 0)...
    };
}

template <class Tuple, class F>
void for_each(Tuple&& t, F&& f) {
    for_each_impl(std::forward<Tuple>(t), std::forward<F>(f), make_tuple_idxs<Tuple>{});
}

template<class Tuple, class F, std::size_t... Is>
auto transform_impl(Tuple&& t, F&& f, index_sequence<Is...>)
    -> decltype(std::make_tuple(std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t)))...))
{
    return std::make_tuple(std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t)))...);
}

template<class F, class Tuple>
auto transform(Tuple&& t, F&& f = {})
    -> decltype(transform_impl(std::forward<Tuple>(t), std::forward<F>(f), make_tuple_idxs<Tuple>{}))
{
    return transform_impl(std::forward<Tuple>(t), std::forward<F>(f), make_tuple_idxs<Tuple>{});
}

template<class Predicate>
struct find_if_body {
    const Predicate& pred;
    std::size_t& index;
    std::size_t currentIndex = 0;
    bool found = false;

    find_if_body(const Predicate& p, std::size_t& i) : pred(p), index(i) {}

    template<typename T>
    void operator()(T&& value) {
        if (found) return;
        if (pred(std::forward<T>(value))) {
            index = currentIndex;
            found = true;
        }
        ++currentIndex;
    }
};

template<class Predicate, class Tuple>
std::size_t find_if(Tuple&& tuple, Predicate pred = {}) {
    std::size_t idx = tuple_size<Tuple>();
    for_each(std::forward<Tuple>(tuple), find_if_body<Predicate>(pred, idx));
    return idx;
}

template<class Predicate, class Tuple>
bool any_of(Tuple&& tuple, Predicate pred = {}) {
    return find_if(std::forward<Tuple>(tuple), pred) != tuple_size<Tuple>();
}

struct is_range_empty {
    template<class T>
    bool operator()(const T& range) const {
        using std::begin;
        using std::end;
        return begin(range) == end(range);
    }
};

// TODO Why is this needed?
struct dereference_iterator {
    template<class It>
    auto operator()(It&& it) const -> decltype(*std::forward<It>(it)) {
        return *std::forward<It>(it);
    }
};

// Move on to next row, for when only one input container was supplied
template<class Its, std::size_t I = tuple_size<Its>()-1>
enable_if_t<I == 0>
increment_iterator(Its& it, const Its&, const Its&) {
    ++std::get<I>(it);
}

// Move on to next row, for when more than one input container was supplied
template<class Its, std::size_t I = tuple_size<Its>()-1>
enable_if_t<I != 0>
increment_iterator(Its& its, const Its& begins, const Its& ends) {
    if (++std::get<I>(its) == std::get<I>(ends)) {
        std::get<I>(its) = std::get<I>(begins);
        increment_iterator<Its, I-1>(its, begins, ends);
    }
}

// This is what actually loops over all the containers, one element at a time
// It is called with a template type F that writes the inputs, and runs the converter, which writes the result(s)
// all for one set of container values - when called by verifyAllCombinations()
// More generally, F must have an operator() that acts on one set of input values.
template<class F, class... Ranges>
void cartesian_product(F&& f, const Ranges&... ranges) {
    using std::begin;
    using std::end;

    if (any_of<is_range_empty>(std::forward_as_tuple(ranges...)))
        return;

    const auto begins = std::make_tuple(begin(ranges)...);
    const auto ends = std::make_tuple(end(ranges)...);

    for (auto its = begins; std::get<0>(its) != std::get<0>(ends); increment_iterator(its, begins, ends)) {
        // Command-clicking on transform in CLion 2019.2.1 hangs with CLion with high CPU
        // 'Use clang tidy' is turned off.
        // Power-save turned on.
        // Mac
        Detail::apply(std::forward<F>(f), transform<dereference_iterator>(its));
    }
}

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
        for_each(std::forward_as_tuple(inputs...), print_input{out});
        out << ") => " << converter(input1, inputs...) << '\n';
    }
};
} // namespace Detail

template<class Converter, class Container, class... Containers>
void verifyAllCombinations(Converter&& converter, const Reporter& reporter, const Container& input0, const Containers&... inputs)
{
    std::stringstream s;
    Detail::cartesian_product(Detail::serialize<Converter>{s, std::forward<Converter>(converter)}, input0, inputs...);
    Approvals::verify(s.str(), reporter);
}

template<class Converter, class... Containers>
Detail::enable_if_t<!Detail::disjunction<std::is_base_of<Reporter, Containers>...>::value>
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
