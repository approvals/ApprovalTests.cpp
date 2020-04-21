#pragma once

// Use this in places where we have parameters that are sometimes unused,
// e.g. because of #if
// See https://stackoverflow.com/a/1486931/104370
#define APPROVAL_TESTS_UNUSED(expr)                                                      \
    do                                                                                   \
    {                                                                                    \
        (void)(expr);                                                                    \
    } while (0)

#if __cplusplus >= 201703L
#define APPROVAL_TESTS_NO_DISCARD [[nodiscard]]
#else
#define APPROVAL_TESTS_NO_DISCARD
#endif

#if defined(APPROVALS_SHOW_DEPRECATION_WARNINGS)
#if (__cplusplus >= 201402L)
#define APPROVAL_TESTS_DEPRECATED(text) [[deprecated(text)]]
#define APPROVAL_TESTS_DEPRECATED_CPP11(text)
#else
#define APPROVAL_TESTS_DEPRECATED(text)
#define APPROVAL_TESTS_DEPRECATED_CPP11(text)                                            \
    MoreHelpMessages::deprecatedFunctionCalled(text, __FILE__, __LINE__);
#endif
#else
#define APPROVAL_TESTS_DEPRECATED(text)
#define APPROVAL_TESTS_DEPRECATED_CPP11(text)
#endif

#define APPROVAL_TESTS_DEPRECATED_USE_OPTIONS                                            \
    APPROVAL_TESTS_DEPRECATED("use Options(reporter) instead")

#define APPROVAL_TESTS_DEPRECATED_USE_OPTIONS_CPP11                                      \
    APPROVAL_TESTS_DEPRECATED_CPP11("use Options(reporter) instead")
