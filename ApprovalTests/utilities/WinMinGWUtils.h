#pragma once

#if (defined(__MINGW32__) || defined(__MINGW64__))
#define APPROVAL_TESTS_MINGW
#endif

#ifdef APPROVAL_TESTS_MINGW
#ifdef __cplusplus
extern "C"
{
#endif

#include <sec_api/stdlib_s.h> /* errno_t, size_t */

//    errno_t getenv_s(size_t* ret_required_buf_size,
//                     char* buf,
//                     size_t buf_size_in_bytes,
//                     const char* name);

#ifdef __cplusplus
}
#endif

#endif // APPROVAL_TESTS_MINGW
