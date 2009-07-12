//******************************************************************************
//    File: binfile.cpp
//    Description: Реализация кросс платформенного интрфейса
//                 для работы с фалами
//******************************************************************************

#include "binfile.h"

BINFILE_T::BINFILE_T(const char * FileName, int Mode)
{
    FN = NULL;
    FN = new char[strlen(FileName)+1];
	strcpy(FN, FileName);
    Error = BINFILE_ERROR_NO_ERROR;
    File = NULL;
#if (PLATFORM==WINNT32)
    File = CreateFile( FN,
                       ( (Mode&BINFILE_READ_MODE  ? GENERIC_READ  : NULL) |
                         (Mode&BINFILE_WRITE_MODE ? GENERIC_WRITE : NULL)   ),
                       FILE_SHARE_READ,
                       NULL,
                       OPEN_EXISTING,
                       FILE_FLAG_RANDOM_ACCESS,
                       0 );
#endif
    if(File == NULL) Error = BINFILE_ERROR_OPEN_FILE;
}

BINFILE_T::~BINFILE_T()
{
    if(FN) delete [] FN;
#if (PLATFORM==WINNT32)
    CloseHandle(File);
#endif
}

int BINFILE_T::Read(void * Buffer, int Size)
{
    int BytesRead;
#if (PLATFORM==WINNT32)
	bool r = ::ReadFile(File, Buffer, Size, (DWORD*)(&BytesRead), 0);
    if(r == false) Error = BINFILE_ERROR_READ_FILE;
#endif
    return BytesRead;
}

int BINFILE_T::Seek(int Offset)
{
    int result;
#if (PLATFORM==WINNT32)
    result = SetFilePointer(File, Offset, NULL, 0);
    if(result == INVALID_SET_FILE_POINTER) Error = BINFILE_ERROR_SEEK_FILE;
#endif
    return result;
}
