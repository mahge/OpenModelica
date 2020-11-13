
#include "omc_portability.h"
#include "assert.h"

#define OMC_NOT_YET_SUPPORTED(name) assert(0 && #name "is not yet supported on this configuration");


#if defined(__MINGW32__) || OMC_COMPILER_IS_MSVC
  #include <windows.h>
#elif OMC_COMPILER_IS_GNU || OMC_COMPILER_IS_Clang
  #include <unistd.h>
  #include <stdio.h>
  #include <time.h>
#else
  #error "Unknown compiler ID"
#endif


/// zero on success (in which case the string representation of time has been
/// written out to the array pointed to by buf), or non-zero on failure.
/// Extra effects of ctime_s (when used) still apply (buf[0] can be set to null terminating character.)
int omc_time_ctime(char *buf, size_t bufsz, const time_t* timer ) {

#if HAVE_CTIME_S

    return ctime_s(buf, sizeof(buf), timer);

#elif HAVE_CTIME_R

    char* stat = ctime_r(timer, buf);
    return stat == NULL;

#else
    OMC_NOT_YET_SUPPORTED(omc_time_ctime)
#endif

}


/// Upon successful completion, 0 shall be returned. Otherwise, -1 shall be returned, 
/// the current working directory shall remain unchanged, and errno shall be set to indicate the error.
int omc_file_chdir(const char* path)
{

#if defined(__MINGW32__) || OMC_COMPILER_IS_MSVC

  MULTIBYTE_TO_WIDECHAR_LENGTH(path, unicodePathLength);
  MULTIBYTE_TO_WIDECHAR_VAR(path, unicodePath, unicodePathLength);

  if (!SetCurrentDirectoryW(unicodePath)) {
    MULTIBYTE_OR_WIDECHAR_VAR_FREE(unicodePath);
    return -1;
  }

  MULTIBYTE_OR_WIDECHAR_VAR_FREE(unicodePath);
  return 0;

#elif HAVE_UNISTD_H

    return chdir(path);

#else
    #error "Unsupported function omc_file_chdir"

#endif
}

/// Upon successful completion function shall return 0. Otherwise, it shall return -1
int omc_file_rename(const char *source, const char *dest) {

#if defined(__MINGW32__) || OMC_COMPILER_IS_MSVC

    return MoveFileEx(source, dest, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);

#elif OMC_COMPILER_IS_GNU || OMC_COMPILER_IS_Clang

    return rename(source, dest) == 0;

#else
    #error "Unsupported function omc_file_rename"
#endif

}