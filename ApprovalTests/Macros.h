#ifndef CATCHPLAYGROUND_MARCOS_H
#define CATCHPLAYGROUND_MARCOS_H

///////////////////////////////////////////////////////////////////////////////
#define STATIC(type, name, defaultValue) \
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

#endif //CATCHPLAYGROUND_MARCOS_H
