#ifndef APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H
#define APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H

#include <type_traits>
#include "reporters/DefaultReporter.h"
#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/utilities/CartesianProduct.h"
#include "Approvals.h"

namespace ApprovalTests
{
    namespace CombinationApprovals
    {
        namespace Detail
        {

            // Write out second or subsequent input value, with preceding comma and space
            struct print_input
            {
                std::ostream& out;
                template <class T> void operator()(const T& input)
                {
                    out << ", " << input;
                }
            };

            // Write out one row of output
            template <class Converter> struct serialize
            {
                std::ostream& out;
                Converter converter;
                template <class T, class... Ts>
                void operator()(T&& input1, Ts&&... inputs)
                {
                    // First value is printed without trailing comma
                    out << "(" << input1;
                    // Remaining values are printed with prefix of a comma
                    CartesianProduct::Detail::for_each(std::forward_as_tuple(inputs...),
                                                       print_input{out});
                    out << ") => " << converter(input1, inputs...) << '\n';
                }
            };
        } // namespace Detail

        template <class Converter, class Container, class... Containers>
        void verifyAllCombinations(const Reporter& reporter,
                                   Converter&& converter,
                                   const Container& input0,
                                   const Containers&... inputs)
        {
            std::stringstream s;
            CartesianProduct::cartesian_product(
                Detail::serialize<Converter>{s, std::forward<Converter>(converter)},
                input0,
                inputs...);
            Approvals::verify(s.str(), reporter);
        }

        template <class Converter, class... Containers>
        ApprovalTests::Detail::EnableIfNotDerivedFromReporter<Converter>
        verifyAllCombinations(Converter&& converter, const Containers&... inputs)
        {
            verifyAllCombinations(
                DefaultReporter(), std::forward<Converter>(converter), inputs...);
        }

    } // namespace CombinationApprovals
} // namespace ApprovalTests

#endif // APPROVALTESTS_CPP_COMBINATIONAPPROVALS_H
