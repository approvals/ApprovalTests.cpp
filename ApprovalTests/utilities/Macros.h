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

#if ((__cplusplus >= 201402L) && defined(APPROVALS_SHOW_DEPRECATION_WARNINGS))
#define APPROVAL_TESTS_DEPRECATED(text) [[deprecated(text)]]
#else
#define APPROVAL_TESTS_DEPRECATED(text)
#endif
