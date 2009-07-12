//******************************************************************************
//    File: binfile.h
//    Description: Реализация кросс платформенного интрфейса
//                 для работы с фалами
//******************************************************************************
#ifndef __BINFILE_H__
#define __BINFILE_H__

#ifndef PLATFORM
#define PLATFORM WINNT32
#endif

#if (PLATFORM==WINNT32)
#include <windows.h>
#endif

#define BINFILE_READ_MODE    0x1
#define BINFILE_WRITE_MODE   0x2
#define BINFILE_ERROR_NO_ERROR   0x0
#define BINFILE_ERROR_OPEN_FILE  0x1
#define BINFILE_ERROR_READ_FILE  0x2
#define BINFILE_ERROR_SEEK_FILE  0x3
#define BINFILE_SEEK_MODE_BEGIN     0x0
#define BINFILE_SEEK_MODE_CURRENT   0x1
#define BINFILE_SEEK_MODE_END       0x2
class BINFILE_T
{
public:
	BINFILE_T(const char * FileName, int Mode);
	~BINFILE_T();
	char * FN;
#if (PLATFORM==WINNT32)
	HANDLE File;
#endif
	int Error;
	int Read(void * Buffer, int Size);
	int Seek(int Offset);
};


#endif
