/* Variable arguments through clang's builtins, in place of the SDK's stdarg.h, which assumes the Microsoft SH compiler's stack layout. */
#ifndef _INC_STDARG
#define _INC_STDARG

typedef __builtin_va_list va_list;

#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, type)   __builtin_va_arg(ap, type)
#define va_end(ap)         __builtin_va_end(ap)
#define va_copy(to, from)  __builtin_va_copy(to, from)

#endif
