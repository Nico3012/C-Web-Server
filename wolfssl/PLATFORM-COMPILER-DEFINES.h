#undef __CYGWIN__
#undef __MINGW32__



#undef _MSC_VER
#undef _WIN32



#undef __MINGW64_VERSION_MAJOR
#undef __MINGW64_VERSION_MINOR
#undef __MINGW64__



#undef __EMSCRIPTEN__



#undef __BCPLUSPLUS__





#undef __CYGWIN__
#undef __CYGWIN__
#undef __CYGWIN__
#undef __CYGWIN__
#undef __CYGWIN__
#undef __CYGWIN__
#undef __CYGWIN__










/*-----------------------------------------------------------------------*/
/* ARCHITECTURES */
/*-----------------------------------------------------------------------*/

// undef all architecture with sizeof(long) == 8:
#undef __alpha__
#undef __ia64__
#undef _ARCH_PPC64
#undef __x86_64__
#undef __s390x__
#undef sun
#undef __sun
#undef LP64
#undef _LP64
#undef __riscv_xlen
#undef __aarch64__
#undef __DCC__
#undef __LP64
#define SIZEOF_LONG 8

// undef all architecture with sizeof(long long) == 8:
#undef __i386__
#undef __CORTEX_M3__
// #define SIZEOF_LONG_LONG 8
