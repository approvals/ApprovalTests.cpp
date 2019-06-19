

#ifndef APPROVALTESTS_CPP_MINGW_H
#define APPROVALTESTS_CPP_MINGW_H

// <SingleHpp unalterable>
//  This is to correct a method that is included but not exposed in MinGW
//  More at: https://stackoverflow.com/questions/51905596/does-mingw-w64-g-expose-microsoft-ucrts-implementation-of-c11-getenv-s-func

#if defined( __MINGW32__) || defined(__MINGW64__)
#ifdef __cplusplus

extern "C" {

#endif



#include <sec_api/stdlib_s.h> /* errno_t, size_t */

errno_t getenv_s(

        size_t     *ret_required_buf_size,

        char       *buf,

        size_t      buf_size_in_bytes,

        const char *name

);



#ifdef __cplusplus

}

#endif

#endif
// </SingleHpp>
#endif //APPROVALTESTS_CPP_MINGW_H
