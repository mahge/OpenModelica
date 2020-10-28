
#include "../../build_cmake/omc_compiler_detection.h"

#if defined(__MINGW32__) || OMC_COMPILER_IS_MSVC
  #include <windows.h>
#elif OMC_COMPILER_IS_GNU || OMC_COMPILER_IS_Clang
  #include <time.h>
  #include <stdio.h>
#else
  #error "Unknown compiler ID"
#endif


/// zero on success (in which case the string representation of time has been
/// written out to the array pointed to by buf), or non-zero on failure.
/// Extra effects of ctime_s (when used) still apply (buf[0] can be set to null terminating character.)
int omc_time_ctime(char *buf, size_t bufsz, const time_t* timer ) {

#if defined(__MINGW32__) || OMC_COMPILER_IS_MSVC

    return ctime_s(buf, sizeof(buf), timer);

#elif OMC_COMPILER_IS_GNU || OMC_COMPILER_IS_Clang

    char* stat = ctime_r(timer, buf);
    return stat == NULL;

#else
    #error "Unexpected compiler id omc_time_ctime"
#endif

}


/// Upon successful completion function shall return 0. Otherwise, it shall return -1
int omc_file_rename(const char *source, const char *dest) {

#if defined(__MINGW32__) || OMC_COMPILER_IS_MSVC

    return MoveFileEx(source, dest, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);

#elif OMC_COMPILER_IS_GNU || OMC_COMPILER_IS_Clang

    return rename(source, dest) == 0;

#else
    #error "Unexpected compiler id omc_file_rename"
#endif

}