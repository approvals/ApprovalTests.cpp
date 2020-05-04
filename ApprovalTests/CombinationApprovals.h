#pragma once

#include <type_traits>
#include <utility>
#include "ApprovalTests/ApprovalsMacroDefaults.h"
#include "reporters/DefaultReporter.h"
#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/core/Options.h"
#include "ApprovalTests/utilities/CartesianProduct.h"
#include "ApprovalTests/utilities/MoreHelpMessages.h"
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
                    out << ", " << OStreamToString::toString(input);
                }
            };

            // Write out one row of output
            template <class Converter> struct serialize
            {
                std::ostream& out;
                Converter converter;
                template <class T, class... Ts>
                void operator()(T&& input1_, Ts&&... inputs)
                {
                    // First value is printed without trailing comma
                    out << "(" << OStreamToString::toString(input1_);
                    // Remaining values are printed with prefix of a comma
                    CartesianProduct::Detail::for_each(std::forward_as_tuple(inputs...),
                                                       print_input{out});
                    out << ") => " << converter(input1_, inputs...) << '\n';
                }
            };
        } // namespace Detail

        template <class Converter, class Container, class... Containers>
        void verifyAllCombinations(const Options& options,
                                   Converter&& converter,
                                   const Container& input0,
                                   const Containers&... inputs)
        {
            std::stringstream s;
            CartesianProduct::cartesian_product(
                Detail::serialize<Converter>{s, std::forward<Converter>(converter)},
                input0,
                inputs...);
            Approvals::verify(s.str(), options);
        }

#if !APPROVAL_TESTS_HIDE_DEPRECATED_CODE
        template <class Converter, class Container, class... Containers>
        APPROVAL_TESTS_DEPRECATED_USE_OPTIONS void
        verifyAllCombinations(const Reporter& reporter,
                              Converter&& converter,
                              const Container& input0,
                              const Containers&... inputs)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyAllCombinations(Options(reporter), converter, input0, inputs...);
        }
#endif

        template <class Converter, class... Containers>
        ApprovalTests::Detail::EnableIfNotOptionsOrReporter<Converter>
        verifyAllCombinations(Converter&& converter, const Containers&... inputs)
        {
            verifyAllCombinations(
                Options(), std::forward<Converter>(converter), inputs...);
        }

    } // namespace CombinationApprovals
} // namespace ApprovalTests
