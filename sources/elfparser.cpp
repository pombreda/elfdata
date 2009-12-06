//******************************************************************************
//    File: elfparser.cpp
//    Description: Парсинг файла ELF
//******************************************************************************

#include "elfparser.h"
#include "common.h"
#include <stdio.h>
//#include <conio.h>
//#include <windows.h>


ELF_T * OpenElf(const char * FileName)
{
	ELF_T * Elf = new ELF_T;
	if(Elf == NULL)
	{
		return NULL;
	}
	Elf->ProgramHeaders = NULL;
	Elf->File = NULL;
	Elf->File = new BINFILE_T(FileName, BINFILE_READ_MODE);
	if(Elf->File == NULL)
	{
		delete Elf;
		return NULL;
	}
	return Elf;
}

int CloseElf(ELF_T * Elf)
{
	if(Elf)
	{
		if(Elf->File)
		{
			delete Elf->File;
		}
		if(Elf->ProgramHeaders)
		{
			delete [] Elf->ProgramHeaders;
		}
		if(Elf->SectionHeaders)
		{
			delete [] Elf->SectionHeaders;
		}
		delete Elf;
		return ELF_PARSER_RETURN_OK;
	}
	return ELF_PARSER_RETURN_ERROR;
}

int ParseHeader(ELF_T * Elf)
{
	if(!Elf)
	{
		return ELF_PARSER_RETURN_ELF_DOESNT_CREATED;
	}
	int read = Elf->File->Read( &(Elf->Header), sizeof(Elf32_Ehdr) );
	if( (read < sizeof(Elf32_Ehdr)) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_READ_FILE;
	}
	bigend = ( Elf->Header.e_ident[5] == ELFDATA2MSB );
	if ( bigend ) switchEndian( &(Elf->Header) );
	return ELF_PARSER_RETURN_OK;
}

int ParseProgramHeaders(ELF_T * Elf)
{
	if(!Elf)
	{
		return ELF_PARSER_RETURN_ELF_DOESNT_CREATED;
	}
	int seek = Elf->File->Seek(Elf->Header.e_phoff);
	if( (seek != (int)Elf->Header.e_phoff) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_SEEK_FILE;
	}
	Elf->ProgramHeaders = new Elf32_Phdr[Elf->Header.e_phnum];
	if(Elf->ProgramHeaders == NULL)
	{
		return ELF_PARSER_RETURN_ERROR_ALLOC_MEM_PH;
	}
	int read = Elf->File->Read( Elf->ProgramHeaders, Elf->Header.e_phnum * sizeof(Elf32_Phdr) );
	if( (read < (int)(Elf->Header.e_phnum * sizeof(Elf32_Phdr))) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_READ_FILE;
	}
	
	for(int i=0;i<Elf->Header.e_phnum;i++)
	{
		if ( bigend ) switchEndian( &(Elf->ProgramHeaders[i]) );
		if(Elf->ProgramHeaders[i].p_type == PT_DYNAMIC)
		{
			Elf->DynPH = &Elf->ProgramHeaders[i];
			break;
		}
    }
	return ELF_PARSER_RETURN_OK;
}

int ParseSectionHeaders(ELF_T * Elf)
{
	if(!Elf)
	{
		return ELF_PARSER_RETURN_ELF_DOESNT_CREATED;
	}
	int seek = Elf->File->Seek(Elf->Header.e_shoff);
	if( (seek != (int)Elf->Header.e_shoff) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_SEEK_FILE;
	}
	Elf->SectionHeaders = new Elf32_Shdr[Elf->Header.e_shnum];
	if(Elf->SectionHeaders == NULL)
	{
		return ELF_PARSER_RETURN_ERROR_ALLOC_MEM_PH;
	}
	int read = Elf->File->Read( Elf->SectionHeaders, Elf->Header.e_shnum * sizeof(Elf32_Shdr) );
	if( (read < (int)(Elf->Header.e_shnum * sizeof(Elf32_Shdr))) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_READ_FILE;
	}
	for(int i=0;i<Elf->Header.e_shnum;i++)
	{
		if ( bigend ) switchEndian( &(Elf->SectionHeaders[i]) );
	}
	return ELF_PARSER_RETURN_OK;
}

int ParseDynamicSegment(ELF_T * Elf)
{
	if(!Elf)
	{
		return ELF_PARSER_RETURN_ELF_DOESNT_CREATED;
	}
	if(!Elf->DynPH)
	{
		return ELF_PARSER_RETURN_DYNPH_DOESNT_FOUND;
	}
	Elf->DynamicSegment = malloc(Elf->DynPH->p_memsz);
	if(Elf->DynamicSegment == NULL)
	{
		return ELF_PARSER_RETURN_ERROR_ALLOC_MEM_DS;
	}
	int seek = Elf->File->Seek(Elf->DynPH->p_offset);
	if( (seek != (int)Elf->DynPH->p_offset) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_SEEK_FILE;
	}
	int read = Elf->File->Read( Elf->DynamicSegment, Elf->DynPH->p_filesz );
	if( (read < (int)(Elf->DynPH->p_filesz)) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_READ_FILE;
	}
	
	return ELF_PARSER_RETURN_OK;
}

int LoadProgramSegment(ELF_T * Elf, Elf32_Phdr * PH, void * ptr)
{
	if(!Elf)
	{
		return ELF_PARSER_RETURN_ELF_DOESNT_CREATED;
	}
	if(!PH)
	{
		return ELF_PARSER_RETURN_PH_DOESNT_FOUND;
	}
	if(!ptr)
	{
		return ELF_PARSER_RETURN_PTR_DOESNT_ALLOC;
	}
	int seek = Elf->File->Seek(PH->p_offset);
	if( (seek != (int)PH->p_offset) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_SEEK_FILE;
	}
	int read = Elf->File->Read(ptr, PH->p_filesz);
	if( (read < (int)PH->p_filesz) || (Elf->File->Error) )
	{
		return ELF_PARSER_RETURN_ERROR_READ_FILE;
	}
	return ELF_PARSER_RETURN_OK;
}

int PrepareDynamicSegment(ELF_T * Elf)
{
	if(!Elf)
	{
		return ELF_PARSER_RETURN_ELF_DOESNT_CREATED;
	}
	if(!Elf->DynamicSegment)
	{
		return ELF_PARSER_RETURN_DYNSEG_DOESNT_FOUND;
	}
	if(!Elf->DynPH)
	{
		return ELF_PARSER_RETURN_DYNPH_DOESNT_FOUND;
	}
	Elf32_Dyn * tag;
	//Elf->DynTagsCount = 0;

	memset( Elf->DynamicTags, 0, (DT_MAX_TAG+1)*sizeof(Elf32_Word) );
	for (int i=0; i<Elf->DynPH->p_memsz/sizeof(Elf32_Dyn); i++)
	{
		tag = &((Elf32_Dyn*)Elf->DynamicSegment)[i];
		if ( bigend ) switchEndian( tag );
		//printf("Tag[%i], d_tag = %i, val = 0x%X (%d)\n", i, tag->d_tag, tag->d_val, tag->d_val );
		if(tag->d_tag == DT_NULL) break;    // конец
		if(tag->d_tag == DT_NEEDED)
		{
			// загрузка требуемой библиотеки
		}
		//else
		{
			if ( tag->d_tag < DT_MAX_TAG+1 )
				Elf->DynamicTags[tag->d_tag] = tag->d_val;
		}
		//Elf->DynTagsCount++;
	}
	

	Elf->DynamicSymbolTable = (Elf32_Sym*)( (unsigned long)Elf->DynamicSegment +
											Elf->DynamicTags[DT_SYMTAB] -
											Elf->DynPH->p_offset );

	Elf->StringTable = (char*)( (unsigned long)Elf->DynamicSegment +
								Elf->DynamicTags[DT_STRTAB] -
								Elf->DynPH->p_offset );

	//printf( "Elf->StringTable = %d\n", Elf->StringTable );

	return ELF_PARSER_RETURN_OK;
}


