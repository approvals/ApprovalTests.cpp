#ifndef APPROVALTESTS_CPP_MACROS_H
#define APPROVALTESTS_CPP_MACROS_H

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

///////////////////////////////////////////////////////////////////////////////

#endif //APPROVALTESTS_CPP_MACROS_H
