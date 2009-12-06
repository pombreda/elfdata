#ifndef SDK_TYPEDEFS_H
#define SDK_TYPEDEFS_H


#ifdef WIN32
	#include <basetsd.h>
	#include <windows.h>
	#include <memory.h>

	// system types conflict workaround

	/*#define INT32					ELFINT32
	#define UINT32					ELFUINT32
	#define INT64					ELFINT64
	#define BOOL					ELFBOOL
	#define WCHAR					ELFWCHAR*/
#endif

typedef signed char				INT8;
typedef unsigned char			UINT8;
typedef signed short			INT16;
typedef unsigned short			UINT16;
//typedef signed long				INT32;
//typedef unsigned long			UINT32;

#ifdef WIN32
	typedef signed __int64			INT64;
	typedef unsigned __int64		UINT64;
#else
	typedef signed long long		INT64;
	typedef unsigned long long		UINT64;
#endif

/*typedef UINT8					BOOL;
typedef UINT8					BOOLEAN;
typedef UINT16					WCHAR;
typedef UINT16					W_CHAR;
typedef UINT8					BYTE;*/


#define SYN_NULL   0


#ifndef WIN32
	#define TRUE					(BOOL)(1)
	#define FALSE					(BOOL)(0)
#endif


#define true					(BOOL)(1)
#define false					(BOOL)(0)

#define RESULT_OK				(0)
#define RESULT_FAIL				(1)

#ifndef WIN32
	#define NULL					(0)
#endif



#endif // SDK_TYPEDEFS_H
