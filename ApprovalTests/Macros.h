#ifndef APPROVALTESTS_CPP_MACROS_H
#define APPROVALTESTS_CPP_MACROS_H

#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////
#define APPROVAL_TESTS_MACROS_STATIC(type, name, defaultValue) \
static type &name(type *value = NULL) { \
    static type *staticValue; \
    if (value != NULL) \
    { \
        staticValue = value; \
    } \
    if (staticValue == NULL) \
    { \
        staticValue = defaultValue; \
    } \
    if ( staticValue == nullptr ) \
    { \
        const char* helpMessage = "The variable in " #name "() is not initialised"; \
        throw std::runtime_error( helpMessage ); \
    } \
    return *staticValue; \
}

// Use this in places where we have parameters that sometimes unused,
// e.g. because of #if
// See https://stackoverflow.com/a/1486931/104370
#define APPROVAL_TESTS_UNUSED(expr) do { (void)(expr); } while (0)

///////////////////////////////////////////////////////////////////////////////

#endif //APPROVALTESTS_CPP_MACROS_H
