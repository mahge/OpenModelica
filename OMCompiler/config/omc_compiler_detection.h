
#ifndef OMC_COMPILER_DETECTION_H
#define OMC_COMPILER_DETECTION_H

#define OMC_COMPILER_IS_GNU 0
#define OMC_COMPILER_IS_Clang 0
#define OMC_COMPILER_IS_AppleClang 0
#define OMC_COMPILER_IS_ARMClang 0
#define OMC_COMPILER_IS_MSVC 0


#if defined(__clang__)
#  undef OMC_COMPILER_IS_Clang
#  define OMC_COMPILER_IS_Clang 1

#  if defined(__apple_build_version__)
#    undef OMC_COMPILER_IS_AppleClang
#    define OMC_COMPILER_IS_AppleClang 1
#  endif

#  if defined(__ARMCOMPILER_VERSION)
#    undef OMC_COMPILER_IS_ARMClang
#    define OMC_COMPILER_IS_ARMClang 1
#  endif
#endif

// Not clang but __GNUC__ and __GNUG__ are defined. It must be GCC.
#if !defined(__clang__) && (defined(__GNUC__) || defined(__GNUG__))
#  undef OMC_COMPILER_IS_GNU
#  define OMC_COMPILER_IS_GNU 1
#endif

#if defined(_MSC_VER)
#  undef OMC_COMPILER_IS_MSVC
#  define OMC_COMPILER_IS_MSVC 1
#endif

#if OMC_COMPILER_IS_GNU

#  if !((__GNUC__ * 100 + __GNUC_MINOR__) >= 404)
#    error Unsupported compiler version
#  endif

#  if defined(__GNUC__)
#    define OMC_COMPILER_VERSION_MAJOR (__GNUC__)
#  else
#    define OMC_COMPILER_VERSION_MAJOR (__GNUG__)
#  endif
#  if defined(__GNUC_MINOR__)
#    define OMC_COMPILER_VERSION_MINOR (__GNUC_MINOR__)
#  endif
#  if defined(__GNUC_PATCHLEVEL__)
#    define OMC_COMPILER_VERSION_PATCH (__GNUC_PATCHLEVEL__)
#  endif

#elif OMC_COMPILER_IS_Clang

#  if !(((__clang_major__ * 100) + __clang_minor__) >= 301)
#    error Unsupported compiler version
#  endif

#  define OMC_COMPILER_VERSION_MAJOR (__clang_major__)
#  define OMC_COMPILER_VERSION_MINOR (__clang_minor__)
#  define OMC_COMPILER_VERSION_PATCH (__clang_patchlevel__)
#  if defined(_MSC_VER)
/* _MSC_VER = VVRR */
#    define OMC_SIMULATE_VERSION_MAJOR (_MSC_VER / 100)
#    define OMC_SIMULATE_VERSION_MINOR (_MSC_VER % 100)
#  endif

#elif OMC_COMPILER_IS_MSVC

#  if !(_MSC_VER >= 1600)
#    error Unsupported compiler version
#  endif

/* _MSC_VER = VVRR */
#  define OMC_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#  define OMC_COMPILER_VERSION_MINOR (_MSC_VER % 100)
#  if defined(_MSC_FULL_VER)
#    if _MSC_VER >= 1400
/* _MSC_FULL_VER = VVRRPPPPP */
#      define OMC_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#    else
/* _MSC_FULL_VER = VVRRPPPP */
#      define OMC_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#    endif
#  endif
#  if defined(_MSC_BUILD)
#    define OMC_COMPILER_VERSION_TWEAK (_MSC_BUILD)
#  endif

#  if _MSC_VER >= 1600
#    define OMC_COMPILER_CXX_STATIC_ASSERT 1
#  else
#    define OMC_COMPILER_CXX_STATIC_ASSERT 0
#  endif

#else
#  error Unsupported compiler
#endif

#endif
