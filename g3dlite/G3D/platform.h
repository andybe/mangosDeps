/**
 @file platform.h

 \#defines for platform specific issues.

 @maintainer Morgan McGuire, http://graphics.cs.williams.edu

 @created 2003-06-09
 @edited  2010-08-11
 */

#ifndef G3D_platform_h
#define G3D_platform_h

/**
 The version number of G3D in the form: MmmBB -> 
 version M.mm [beta BB]
 */
#define G3D_VER 80100

// fatal error for unsupported architectures
#if defined(__powerpc__)
#   error PowerPC is not supported by G3D!
#endif

#if defined(G3D_RELEASEDEBUG)
#   define G3D_DEBUGRELEASE
#endif

#if defined(G3D_DEBUGRELEASE) && defined(_DEBUG)
#   undef _DEBUG
#endif

/** @def G3D_DEBUG()
    Defined if G3D is built in debug mode. */
#if !defined(G3D_DEBUG) && (defined(_DEBUG) || defined(G3D_DEBUGRELEASE))
#   define G3D_DEBUG
#endif

/** These control the version of Winsock used by G3D.
    Version 2.0 is standard for G3D 6.09 and later.
    Version 1.1 is standard for G3D 6.08 and earlier.
 */
#define G3D_WINSOCK_MAJOR_VERSION 2
#define G3D_WINSOCK_MINOR_VERSION 0

#ifdef _MSC_VER 
    #define G3D_WIN32
#elif  defined(__FreeBSD__) || defined(__OpenBSD__)
    #define G3D_FREEBSD
    #define G3D_LINUX
#elif defined(__linux__)
    #define G3D_LINUX
#elif defined(__APPLE__)
    /** it's very unusual, but works on OSX since 2011
         remove #define G3D_OSX for
   */
    #define G3D_LINUX

   // Prevent OS X fp.h header from being included; it defines
   // pi as a constant, which creates a conflict with G3D
#define __FP__
#else
    #error Unknown platform 
#endif

// Detect 64-bit under various compilers
#if (defined(_M_X64) || defined(_WIN64) || defined(__LP64__) || defined(_LP64))
#    define G3D_64BIT
#else
#    define G3D_32BIT
#endif

// Strongly encourage inlining on gcc
#ifdef __GNUC__
#define inline __inline__
#endif


// Verify that the supported compilers are being used and that this is a known
// processor.

#ifdef G3D_LINUX
#   ifndef __GNUC__
#       error G3D only supports the gcc compiler on Linux.
#   endif
#endif

#ifdef G3D_OSX
#    ifndef __GNUC__
#        error G3D only supports the gcc compiler on OS X.
#    endif
    
#    if defined(__i386__)
#        define G3D_OSX_INTEL
#    elif defined(__PPC__)
#        define G3D_OSX_PPC
#    else
#        define G3D_OSX_UNKNOWN
#    endif

#endif


#ifdef _MSC_VER
// Microsoft Visual C++ 8.0 ("Express")       = 1400
// Microsoft Visual C++ 7.1    ("2003") _MSC_VER = 1310
// Microsoft Visual C++ 7.0    ("2002") _MSC_VER = 1300
// Microsoft Visual C++ 6.0    _MSC_VER          = 1200
// Microsoft Visual C++ 5.0    _MSC_VER          = 1100

// Turn off warnings about deprecated C routines
#   pragma warning (disable : 4996)

// Turn off "conditional expression is constant" warning; MSVC generates this
// for debug assertions in inlined methods.
#  pragma warning (disable : 4127)

/** @def G3D_DEPRECATED()
    Creates deprecated warning. */
#  define G3D_DEPRECATED __declspec(deprecated)

// Prevent Winsock conflicts by hiding the winsock API
#   ifndef _WINSOCKAPI_
#       define _G3D_INTERNAL_HIDE_WINSOCK_
#       define _WINSOCKAPI_
#   endif

// Disable 'name too long for browse information' warning
#   pragma warning (disable : 4786)
// TODO: remove
#   pragma warning (disable : 4244)

// #   define ZLIB_WINAPI /* G3DFIX: caused some unresolved external errors with MSVC */

#   define restrict

/** @def G3D_CHECK_PRINTF_METHOD_ARGS()
    Enables printf parameter validation on gcc. */
#   define G3D_CHECK_PRINTF_ARGS 

/** @def G3D_CHECK_PRINTF_METHOD_ARGS()
    Enables printf parameter validation on gcc. */
#   define G3D_CHECK_VPRINTF_ARGS

/** @def G3D_CHECK_PRINTF_METHOD_ARGS()
    Enables printf parameter validation on gcc. */
#   define G3D_CHECK_PRINTF_METHOD_ARGS 

/** @def G3D_CHECK_PRINTF_METHOD_ARGS()
    Enables printf parameter validation on gcc. */
#   define G3D_CHECK_VPRINTF_METHOD_ARGS

    // On MSVC, we need to link against the multithreaded DLL version of
    // the C++ runtime because that is what SDL and ZLIB are compiled
    // against.  This is not the default for MSVC, so we set the following
    // defines to force correct linking.  
    //
    // For documentation on compiler options, see:
    //  http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vccore/html/_core_.2f.md.2c_2f.ml.2c_2f.mt.2c_2f.ld.asp
    //  http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vccore98/HTML/_core_Compiler_Reference.asp
    //

    // DLL runtime
    #ifndef _DLL
        #define _DLL
    #endif

    // Multithreaded runtime
    #ifndef _MT
        #define _MT 1
    #endif

    // Ensure that we aren't forced into the static lib
    #ifdef _STATIC_CPPLIB
        #undef _STATIC_CPPLIB
    #endif

    #ifdef _DEBUG
        #pragma comment (linker, "/NODEFAULTLIB:LIBCMTD.LIB")
        #pragma comment (linker, "/NODEFAULTLIB:LIBCPMTD.LIB")
        #pragma comment (linker, "/NODEFAULTLIB:LIBCPD.LIB")
        #pragma comment (linker, "/DEFAULTLIB:MSVCPRTD.LIB")
        #pragma comment(linker, "/NODEFAULTLIB:LIBCD.LIB")
        #pragma comment(linker, "/DEFAULTLIB:MSVCRTD.LIB")
    #else
        #pragma comment(linker, "/NODEFAULTLIB:LIBC.LIB")
        #pragma comment(linker, "/DEFAULTLIB:MSVCRT.LIB")
        #pragma comment (linker, "/NODEFAULTLIB:LIBCMT.LIB")
        #pragma comment (linker, "/NODEFAULTLIB:LIBCPMT.LIB")
        #pragma comment(linker, "/NODEFAULTLIB:LIBCP.LIB")
        #pragma comment (linker, "/DEFAULTLIB:MSVCPRT.LIB")
    #endif

    // Now set up external linking

#    ifdef _DEBUG
        // zlib was linked against the release MSVCRT; force
        // the debug version.
#        pragma comment(linker, "/NODEFAULTLIB:MSVCRT.LIB")
#     endif


#    ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#    endif


#   define NOMINMAX 1
#   ifndef _WIN32_WINNT
#       define _WIN32_WINNT 0x0500
#   endif
#   include <windows.h>
#   undef WIN32_LEAN_AND_MEAN
#   undef NOMINMAX

#   ifdef _G3D_INTERNAL_HIDE_WINSOCK_
#      undef _G3D_INTERNAL_HIDE_WINSOCK_
#      undef _WINSOCKAPI_
#   endif


/** @def G3D_START_AT_MAIN()
    Defines necessary wrapper around WinMain on Windows to allow transfer of execution to main(). */
#   define G3D_START_AT_MAIN()\
int WINAPI G3D_WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw);\
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw) {\
    return G3D_WinMain(hInst, hPrev, szCmdLine, sw);\
}

#else

/** @def G3D_START_AT_MAIN()
    Defines necessary wrapper around WinMain on Windows to allow transfer of execution to main(). */
#   define G3D_START_AT_MAIN()

#endif  // win32

#ifdef __GNUC__

#    include <stdint.h>

#   if __STDC_VERSION__ < 199901
#        define restrict __restrict__
#   endif

/** @def G3D_DEPRECATED()
    Creates deprecated warning. */
#   define G3D_DEPRECATED __attribute__((__deprecated__))

// setup function calling conventions
#   if defined(__i386__) && ! defined(__x86_64__)

#       ifndef __cdecl
#           define __cdecl __attribute__((cdecl))
#       endif

#       ifndef __stdcall
#           define __stdcall __attribute__((stdcall))
#       endif

#   elif defined(__x86_64__)

#       ifndef __cdecl
#           define __cdecl
#       endif

#       ifndef __stdcall
#           define __stdcall
#       endif
#   elif defined(__arm__)
        // CDECL does not apply to arm.
#       define __cdecl
#   endif // calling conventions

/** @def G3D_CHECK_PRINTF_METHOD_ARGS()
    Enables printf parameter validation on gcc. */
#   define G3D_CHECK_PRINTF_METHOD_ARGS   __attribute__((__format__(__printf__, 2, 3)))

/** @def G3D_CHECK_PRINTF_METHOD_ARGS()
    Enables printf parameter validation on gcc. */
#   define G3D_CHECK_VPRINTF_METHOD_ARGS  __attribute__((__format__(__printf__, 2, 0)))

/** @def G3D_CHECK_PRINTF_METHOD_ARGS()
    Enables printf parameter validation on gcc. */
#   define G3D_CHECK_PRINTF_ARGS          __attribute__((__format__(__printf__, 1, 2)))

/** @def G3D_CHECK_PRINTF_METHOD_ARGS()
    Enables printf parameter validation on gcc. */
#   define G3D_CHECK_VPRINTF_ARGS         __attribute__((__format__(__printf__, 1, 0)))
#endif


/** 
  @def STR(expression)

  Creates a string from the expression.  Frequently used with G3D::Shader
  to express shading programs inline.  

  <CODE>STR(this becomes a string)\verbatim<PRE>\endverbatim evaluates the same as \verbatim<CODE>\endverbatim"this becomes a string"</CODE>
 */
#define STR(x) #x

/** @def PRAGMA(expression)
    \#pragma may not appear inside a macro, so this uses the pragma operator 
    to create an equivalent statement.*/
#ifdef _MSC_VER
// Microsoft's version http://msdn.microsoft.com/en-us/library/d9x1s805.aspx
#    define PRAGMA(x) __pragma(x)
#else
// C99 standard http://www.delorie.com/gnu/docs/gcc/cpp_45.html
#    define PRAGMA(x) _Pragma(#x)
#endif

/** @def G3D_BEGIN_PACKED_CLASS(byteAlign)
    Switch to tight alignment
    See G3D::Color3uint8 for an example.*/
#ifdef _MSC_VER
#    define G3D_BEGIN_PACKED_CLASS(byteAlign)  PRAGMA( pack(push, byteAlign) )
#else
#    define G3D_BEGIN_PACKED_CLASS(byteAlign)
#endif

/** @def G3D_END_PACKED_CLASS(byteAlign)
    End switch to tight alignment
    See G3D::Color3uint8 for an example.*/
#ifdef _MSC_VER
#    define G3D_END_PACKED_CLASS(byteAlign)  ; PRAGMA( pack(pop) )
#elif defined(__GNUC__)
#    define G3D_END_PACKED_CLASS(byteAlign)  __attribute((aligned(byteAlign))) ;
#else 
#    define G3D_END_PACKED_CLASS(byteAlign)  ;
#endif


// Header guard
#endif
