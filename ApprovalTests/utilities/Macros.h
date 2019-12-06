#ifndef APPROVALTESTS_CPP_MACROS_H
#define APPROVALTESTS_CPP_MACROS_H

// Use this in places where we have parameters that are sometimes unused,
// e.g. because of #if
// See https://stackoverflow.com/a/1486931/104370
#define APPROVAL_TESTS_UNUSED(expr) do { (void)(expr); } while (0)

#if __cplusplus >= 201703L
    #define APPROVAL_TESTS_NO_DISCARD [[nodiscard]]
#else
    #define APPROVAL_TESTS_NO_DISCARD
#endif

#endif //APPROVALTESTS_CPP_MACROS_H
