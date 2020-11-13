
#include "omcompiler_config.h"

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
int omc_time_ctime(char *buf, size_t bufsz, const time_t* timer );


// Upon successful completion, 0 shall be returned. Otherwise, -1 shall be returned, 
// the current working directory shall remain unchanged, and errno shall be set to indicate the error.
int omc_file_chdir(const char* path);

/// Upon successful completion function shall return 0. Otherwise, it shall return -1
int omc_file_rename(const char *source, const char *dest);
