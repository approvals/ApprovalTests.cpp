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
    template <typename TCompileTimeOptions> class TCombinationApprovals
    {
    private:
        // Write out second or subsequent input value, with preceding comma and space
        struct print_input
        {
            std::ostream& out;
            template <class T> void operator()(const T& input)
            {
                out << ", " << TCompileTimeOptions::ToStringConverter::toString(input);
            }
        };

        // Write out one row of output
        template <class Converter> struct serialize
        {
            std::ostream& out;
            Converter converter;
            template <class T, class... Ts> void operator()(T&& input1_, Ts&&... inputs)
            {
                // First value is printed without trailing comma
                out << "(" << TCompileTimeOptions::ToStringConverter::toString(input1_);
                // Remaining values are printed with prefix of a comma
                CartesianProduct::Detail::for_each(std::forward_as_tuple(inputs...),
                                                   print_input{out});
                out << ") => " << converter(input1_, inputs...) << '\n';
            }
        };

    public:
        /**@name Verifying combinations of objects

         See \userguide{TestingCombinations,Testing combinations}
         */
        template <class Converter, class Container, class... Containers>
        static void verifyAllCombinations(const Options& options,
                                          Converter&& converter,
                                          const Container& input0,
                                          const Containers&... inputs)
        {
            std::stringstream s;
            CartesianProduct::cartesian_product(
                serialize<Converter>{s, std::forward<Converter>(converter)},
                input0,
                inputs...);
            Approvals::verify(s.str(), options);
        }

        template <class Converter, class... Containers>
        ApprovalTests::Detail::EnableIfNotOptionsOrReporter<
            Converter> static verifyAllCombinations(Converter&& converter,
                                                    const Containers&... inputs)
        {
            verifyAllCombinations(
                Options(), std::forward<Converter>(converter), inputs...);
        }
        ///@}

#if !APPROVAL_TESTS_HIDE_DEPRECATED_CODE
        /**@name Deprecated method

         This method pre-dates the Options class, and will be removed in a future
         release.

         For help updating your code, see:
            - \userguide{how_tos/ToggleDeprecatedCode,How to Toggle Enabling or Disabling of Deprecated Code}
            - \userguide{explanations/WhyWeAreConvertingToOptions,how-to-update-calls-to-deprecated-code,How to Update Calls to Deprecated Code}
         */
        ///@{
        template <class Converter, class Container, class... Containers>
        static APPROVAL_TESTS_DEPRECATED_USE_OPTIONS void
        verifyAllCombinations(const Reporter& reporter,
                              Converter&& converter,
                              const Container& input0,
                              const Containers&... inputs)
        {
            APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11
            verifyAllCombinations(Options(reporter), converter, input0, inputs...);
        }
        ///@}
#endif
    };

    using CombinationApprovals = TCombinationApprovals<
        ToStringCompileTimeOptions<APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER>>;

} // namespace ApprovalTests
