/***
*excpt.h - defines exception values, types and routines
*
*	Copyright (c) 1990-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*	This file contains the definitions and prototypes for the compiler-
*	dependent intrinsics, support functions and keywords which implement
*	the structured exception handling extensions.
*
****/

#ifndef _INC_EXCPT

#ifdef __cplusplus
extern "C" {
#endif

#ifdef UNDER_CE

/* Define _CRTAPI1 (for compatibility with the NT SDK) */

#ifndef _CRTAPI1
#if	( (_MSC_VER >= 800) && (_M_IX86 >= 300) )
#define _CRTAPI1 __cdecl
#else
#define _CRTAPI1
#endif
#endif


/* Define _CRTAPI2 (for compatibility with the NT SDK) */

#ifndef _CRTAPI2
#if	( (_MSC_VER >= 800) && (_M_IX86 >= 300) )
#define _CRTAPI2 __cdecl
#else
#define _CRTAPI2
#endif
#endif


/* Define _CRTIMP */

#ifndef _CRTIMP
#ifdef	_NTSDK
/* definition compatible with NT SDK */
#define _CRTIMP
#else	/* ndef _NTSDK */
/* current definition */
#ifdef	_DLL
#define _CRTIMP __declspec(dllimport)
#else	/* ndef _DLL */
#define _CRTIMP
#endif	/* _DLL */
#endif	/* _NTSDK */
#endif	/* _CRTIMP */


/* Define __cdecl for non-Microsoft compilers */

#if	( !defined(_MSC_VER) && !defined(__cdecl) )
#define __cdecl
#endif

#endif	  /* UNDER_CE */


/*
 * Exception disposition return values.
 */
typedef enum _EXCEPTION_DISPOSITION {
    ExceptionContinueExecution,
    ExceptionContinueSearch,
    ExceptionNestedException,
    ExceptionCollidedUnwind

#ifdef UNDER_CE
    ,
    ExceptionExecuteHandler
#endif

} EXCEPTION_DISPOSITION;


/*
 * Prototype for SEH support function.
 */

#ifdef UNDER_CE

/*
 * Declarations to keep MIPS and ALPHA compiler happy
 */
typedef struct _EXCEPTION_POINTERS *Exception_info_ptr;
struct _EXCEPTION_RECORD;
struct _CONTEXT;
struct _RUNTIME_FUNCTION;
struct _EXCEPTION_REGISTRATION_RECORD;

typedef struct _DISPATCHER_CONTEXT {
#if x86
    struct _EXCEPTION_REGISTRATION_RECORD *RegistrationPointer;
    ULONG ControlPc;
#else
    ULONG ControlPc;
    struct _RUNTIME_FUNCTION *FunctionEntry;
    ULONG EstablisherFrame;
    PCONTEXT ContextRecord;
#endif
} DISPATCHER_CONTEXT, *PDISPATCHER_CONTEXT;

typedef EXCEPTION_DISPOSITION EXCEPTION_ROUTINE (
	struct _EXCEPTION_RECORD *ExceptionRecord,
	void *EstablisherFrame,
	struct _CONTEXT *ContextRecord,
	struct _DISPATCHER_CONTEXT *DispatcherContext
	);
typedef EXCEPTION_ROUTINE *PEXCEPTION_ROUTINE;

#if x86
EXCEPTION_ROUTINE _except_handler3;
#else
EXCEPTION_ROUTINE __C_specific_handler;
#endif

#else

#ifdef	_M_IX86

/*
 * Declarations to keep MS C 8 (386/486) compiler happy
 */
struct _EXCEPTION_RECORD;
struct _CONTEXT;

EXCEPTION_DISPOSITION __cdecl _except_handler (
	struct _EXCEPTION_RECORD *ExceptionRecord,
	void * EstablisherFrame,
	struct _CONTEXT *ContextRecord,
	void * DispatcherContext
	);

#endif
#endif	/* UNDER_CE */


/*
 * Keywords and intrinsics for SEH
 */

#ifdef	_MSC_VER

#if	!defined(__cplusplus)
#define try				__try
#define except				__except
#define finally 			__finally
#define leave				__leave
#endif

/**
 * This function retrieves a code that identifies the type of exception that occurred.
 * GetExceptionCode can be called only from within the filter expression or exception-handler block
 * of a try-except exception handler.
 *
 * @return The return value identifies the type of exception. Following are the exception codes
 *   likely to occur due to common programming errors: - EXCEPTION_ACCESS_VIOLATION: The thread
 *   attempted to read from or write to a virtual address for which it does not have the appropriate
 *   access. - EXCEPTION_BREAKPOINT: A breakpoint was encountered. - EXCEPTION_DATATYPE_MISALIGNMENT:
 *   The thread attempted to read or write data that is misaligned on hardware that does not provide
 *   alignment. For example, 16-bit values must be aligned on 2-byte boundaries, 32-bit values on
 *   4-byte boundaries, and so on. - EXCEPTION_SINGLE_STEP: A trace trap or other single-instruction
 *   mechanism signaled that one instruction has been executed. - EXCEPTION_ARRAY_BOUNDS_EXCEEDED: The
 *   thread attempted to access an array element that is out of bounds, and the underlying hardware
 *   supports bounds checking. - EXCEPTION_FLT_DENORMAL_OPERAND: One of the operands in a
 *   floating-point operation is denormal. A denormal value is one that is too small to represent as a
 *   standard floating-point value. - EXCEPTION_FLT_DIVIDE_BY_ZERO: The thread attempted to divide a
 *   floating-point value by a floating-point divisor of zero. - EXCEPTION_FLT_INEXACT_RESULT: The
 *   result of a floating-point operation cannot be represented exactly as a decimal fraction. -
 *   EXCEPTION_FLT_INVALID_OPERATION: This exception represents any floating-point exception not
 *   included in this list. - EXCEPTION_FLT_OVERFLOW: The exponent of a floating-point operation is
 *   greater than the magnitude allowed by the corresponding type. - EXCEPTION_FLT_STACK_CHECK: The
 *   stack overflowed or underflowed as the result of a floating-point operation. -
 *   EXCEPTION_FLT_UNDERFLOW: The exponent of a floating-point operation is less than the magnitude
 *   allowed by the corresponding type. - EXCEPTION_INT_DIVIDE_BY_ZERO: The thread attempted to divide
 *   an integer value by an integer divisor of zero. - EXCEPTION_INT_OVERFLOW: The result of an
 *   integer operation caused a carry out of the most significant bit of the result. -
 *   EXCEPTION_PRIV_INSTRUCTION: The thread attempted to execute an instruction whose operation is not
 *   allowed in the current machine mode. - EXCEPTION_NONCONTINUABLE_EXCEPTION: The thread attempted
 *   to continue execution after a noncontinuable exception occurred.
 *
 * The Excpt.h file has to be explicitly included in order to use GetExceptionCode.
 *
 * The GetExceptionCode function can be called only from within the filter expression or
 * exception-handler block of a try-except statement. The filter expression is evaluated if an
 * exception occurs during execution of the try block, and it determines whether the except block is
 * executed.
 *
 * The filter expression can invoke a filter function. The filter function cannot call
 * GetExceptionCode. However, the return value of GetExceptionCode can be passed as a parameter to a
 * filter function. The return value of the GetExceptionInformation function can also be passed as a
 * parameter to a filter function. GetExceptionInformation returns a pointer to a structure that
 * includes the exception-code information.
 *
 * The following code example shows the structure of a try-except statement.
 *
 *     try
 *     {
 *
 *         // try block
 *
 *     }
 *     except ( FilterFunction(GetExceptionCode() )
 *     {
 *
 *         // exception handler block
 *
 *     }
 *
 * In the case of nested try-except statements, each statement's filter expression is evaluated
 * until one is evaluated as EXCEPTION_EXECUTE_HANDLER or EXCEPTION_CONTINUE_EXECUTION. Each filter
 * expression can invoke GetExceptionCode to get the exception code.
 *
 * The exception code returned is the code generated by a hardware exception, or the code specified
 * in the RaiseException function for a software-generated exception.
 *
 * When handling the breakpoint exception, it is important to increment the instruction pointer in
 * the context record to continue from this exception.
 */
#define GetExceptionCode		_exception_code
#define exception_code			_exception_code
/**
 * This function retrieves a machine-independent description of an exception, and information about
 * the machine state that existed for the thread when the exception occurred.
 * GetExceptionInformation can be called only from within the filter expression of a try-except
 * exception handler.
 *
 * @return A pointer to an EXCEPTION_POINTERS structure that contains pointers to two other
 *   structures-an EXCEPTION_RECORD structure containing a description of the exception, and a CONTEXT
 *   structure containing the machine-state information-indicates success.
 *
 * The Excpt.h file must be explicitly included in order to use GetExceptionInformation.
 *
 * The filter expression (from which the function is called) is evaluated if an exception occurs
 * during execution of the try block, and it determines whether the except block is executed.
 *
 * The following code example shows the structure of a try-except statement.
 *
 *     try
 *     {
 *
 *         // try block
 *
 *     }
 *     except ( FilterFunction(GetExceptionInformation() )
 *     {
 *
 *         // exception handler block
 *
 *     }
 *
 * The filter expression can invoke a filter function. The filter function cannot call
 * GetExceptionInformation. However, the return value of GetExceptionInformation can be passed as a
 * parameter to a filter function.
 *
 * To pass the EXCEPTION_POINTERS information to the exception-handler block, the filter expression
 * or filter function must copy the pointer or the data to safe storage that the handler can later
 * access.
 *
 * In the case of nested try-except statements, each statement's filter expression is evaluated
 * until one is evaluated as EXCEPTION_EXECUTE_HANDLER or EXCEPTION_CONTINUE_EXECUTION. Each filter
 * expression can invoke GetExceptionInformation to get exception information.
 */
#define GetExceptionInformation 	(struct _EXCEPTION_POINTERS *)_exception_info
#define exception_info			(struct _EXCEPTION_POINTERS *)_exception_info
/**
 * This function indicates whether the try block of a try-finally statement terminated normally.
 * This function can be called only from within the finally block of a try-finally statement.
 *
 * @return Nonzero indicates that the try block of the try-finally statement terminated abnormally.
 *   Zero indicates that the try block of the try-finally statement terminated normally.
 *
 * The Excpt.h file has to be explicitly included in order to use this function.
 *
 * The try block terminates normally only if execution leaves the block sequentially after executing
 * the last statement in the block. Statements (such as return, goto, continue, or break) that cause
 * execution to leave the try block result in abnormal termination of the block. This is the case
 * even if such a statement is the last statement in the try block.
 *
 * Abnormal termination of a try block causes the system to search backward through all stack frames
 * to determine whether any termination handlers must be called. This can result in the execution of
 * hundreds of instructions, so it is important to avoid abnormal termination of a try block due to
 * a return, goto, continue, or break statement. Note that these statements do not generate an
 * exception, even though the termination is abnormal.
 *
 * To avoid abnormal termination of the try-finally block, execution should continue to the end of
 * the block. You can also execute the leave statement. The leave statement allows for immediate
 * termination of the try block without causing abnormal termination and its performance penalty.
 * Check your compiler documentation to determine if the leave statement is supported.
 */
#define AbnormalTermination		_abnormal_termination
#define abnormal_termination		_abnormal_termination

unsigned long __cdecl _exception_code(void);
void *	      __cdecl _exception_info(void);
int	      __cdecl _abnormal_termination(void);

#endif


/*
 * Legal values for expression in except().
 */

#define EXCEPTION_EXECUTE_HANDLER	 1
#define EXCEPTION_CONTINUE_SEARCH	 0
#define EXCEPTION_CONTINUE_EXECUTION	-1



#ifdef __cplusplus
}
#endif

#define _INC_EXCPT
#endif	/* _INC_EXCPT */
