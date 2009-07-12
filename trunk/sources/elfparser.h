//******************************************************************************
//    File: elfparser.h
//    Description: Парсинг файла ELF
//******************************************************************************
#ifndef __ELFPARSER_H__
#define __ELFPARSER_H__



#ifndef PLATFORM
#define PLATFORM WINNT32
#endif

#if (PLATFORM==WINNT32)
#include <windows.h>
#endif

#include "binfile.h"
#include "elf.h"

#define ELF_PARSER_RETURN_OK                    0x0
#define ELF_PARSER_RETURN_ERROR                 0x1
#define ELF_PARSER_RETURN_CANT_CREATE_ELF       0x10
#define ELF_PARSER_RETURN_CANT_CREATE_BINFILE   0x11
#define ELF_PARSER_RETURN_ELF_DOESNT_CREATED    0x12
#define ELF_PARSER_RETURN_ERROR_READ_FILE       0x13
#define ELF_PARSER_RETURN_ERROR_SEEK_FILE       0x14
#define ELF_PARSER_RETURN_ERROR_ALLOC_MEM_PH    0x15
#define ELF_PARSER_RETURN_DYNPH_DOESNT_FOUND    0x16
#define ELF_PARSER_RETURN_ERROR_ALLOC_MEM_DS    0x17
#define ELF_PARSER_RETURN_PH_DOESNT_FOUND       0x18
#define ELF_PARSER_RETURN_PTR_DOESNT_ALLOC      0x19
#define ELF_PARSER_RETURN_DYNSEG_DOESNT_FOUND   0x1A
//#define ELF_PARSER_RETURN_DYNSEG_DOESNT_FOUND   0x1A
//#define ELF_PARSER_RETURN_DYNSEG_DOESNT_FOUND   0x1A
//#define ELF_PARSER_RETURN_DYNSEG_DOESNT_FOUND   0x1A



typedef struct
{
	BINFILE_T     * File;
	Elf32_Ehdr      Header;
	Elf32_Phdr    * ProgramHeaders;
	Elf32_Shdr    * SectionHeaders;
	Elf32_Phdr    * DynPH;
	void          * DynamicSegment;
	Elf32_Word      DynamicTags[DT_MAX_TAG+1];
	Elf32_Sym	  * DynamicSymbolTable;
	char          * StringTable;
} ELF_T;

ELF_T * OpenElf(const char * FileName);
int CloseElf(ELF_T * Elf);
int ParseHeader(ELF_T * Elf);
int ParseProgramHeaders(ELF_T * Elf);
int ParseSectionHeaders(ELF_T * Elf);
int ParseDynamicSegment(ELF_T * Elf);
int LoadProgramSegment(ELF_T * Elf, Elf32_Phdr * PH, void * ptr);
int PrepareDynamicSegment(ELF_T * Elf);

#endif


