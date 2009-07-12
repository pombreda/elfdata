//    ElfData main file


#include <stdio.h>
#include <conio.h>
#include "elfparser.h"
#include "binfile.h"


int PrintElfHeader(Elf32_Ehdr * h)
{
    
	printf("e_ident     { ");
				  printf("0 : 0x%.2X\n", h->e_ident[0]);
	printf("              1 : 0x%.2X '%c'\n", h->e_ident[1], h->e_ident[1]);
	printf("              2 : 0x%.2X '%c'\n", h->e_ident[2], h->e_ident[2]);
	printf("              3 : 0x%.2X '%c'\n", h->e_ident[3], h->e_ident[3]);
	printf("              4 : 0x%.2X ", h->e_ident[4]);
	switch(h->e_ident[4])
	{
		case ELFCLASSNONE:
		{
			printf("ELFCLASSNONE\n");
			break;
		}
		case ELFCLASS32:
		{
			printf("ELFCLASS32\n");
			break;
		}
		case ELFCLASS64:
		{
			printf("ELFCLASS64\n");
			break;
		}
		default:
		{
			printf("\n");
		}
	}
	printf("              5 : 0x%.2X ", h->e_ident[5]);
	switch(h->e_ident[5])
	{
		case ELFDATANONE:
		{
			printf("ELFDATANONE\n");
			break;
		}
		case ELFDATA2LSB:
		{
			printf("ELFDATA2LSB (LittleEndian - Intel-style)\n");
			break;
		}
		case ELFDATA2MSB:
		{
			printf("ELFDATA2MSB (BigEndian - Motorola-style)\n");
			break;
		}
		default:
		{
			printf("\n");
		}
	}
	printf("              6 : 0x%.2X ", h->e_ident[6]);
	switch(h->e_ident[6])
	{
		case EV_NONE:
		{
			printf("EV_NONE\n");
			break;
		}
		case EV_CURRENT:
		{
			printf("EV_CURRENT (Default)\n");
			break;
		}
		default:
		{
			printf("\n");
		}
	}
	printf("              7 : 0x%.2X \n", h->e_ident[7]);
	printf("              8 : 0x%.2X \n", h->e_ident[8]);
	printf("              9 : 0x%.2X \n", h->e_ident[9]);
	printf("              A : 0x%.2X \n", h->e_ident[10]);
	printf("              B : 0x%.2X \n", h->e_ident[11]);
	printf("              C : 0x%.2X \n", h->e_ident[12]);
	printf("              D : 0x%.2X \n", h->e_ident[13]);
	printf("              E : 0x%.2X \n", h->e_ident[14]);
	printf("              F : 0x%.2X }\n", h->e_ident[15]);
	printf("e_type      : %d\n",h->e_type);
	printf("e_machine   : %d ",h->e_machine);

	switch(h->e_machine)
	{                                                       
		case EM_NONE:                                       
		{                                                   
			printf("EM_NONE\n");                            
			break;
		}                                                   
		case EM_M32:                                        
		{                                                   
			printf("EM_M32 (AT&T WE 32100)\n");
			break;
		}
		case EM_SPARC:
		{
			printf("EM_SPARC (SPARC)\n");
			break;
		}
		case EM_386:
		{
			printf("EM_386 (Intel Architecture)\n");
			break;
		}
		case EM_68K:
		{
			printf("EM_68K (Motorola 68000)\n");
			break;
		}
		case EM_88K:
		{
			printf("EM_88K (Motorola 88000)\n");
			break;
		}
		case EM_860:
		{
			printf("EM_860 (Intel 80860)\n");
			break;
		}
		case EM_MIPS:
		{
			printf("EM_MIPS (MIPS RS3000 Big-Endian)\n");
			break;
		}
		case EM_MIPS_RS4_BE:
		{
			printf("EM_MIPS_RS4_BE (MIPS RS4000 Big-Endian)\n");
			break;
		}
		case EM_ARM:
		{
			printf("EM_ARM (ARM/Thumb Architecture)\n");
			break;
		}
		default:
		{
			printf("\n");
		}
	}
	printf("e_version   : %d ",h->e_version);
	switch(h->e_version)
	{
		case EV_NONE:
		{
			printf("EV_NONE\n");
			break;
		}
		case EV_CURRENT:
		{
			printf("EV_CURRENT (Default)\n");
			break;
		}
		default:
		{
			printf("\n");
		}
	}
	printf("e_entry     : 0x%.8X\n",h->e_entry);
	printf("e_phoff     : 0x%X (%d)\n",h->e_phoff,h->e_phoff);
	printf("e_shoff     : 0x%X (%d)\n",h->e_shoff,h->e_shoff);
	printf("e_flags     : 0x%X\n",h->e_flags);
	printf("e_ehsize    : 0x%X\n",h->e_ehsize);
	printf("e_phentsize : 0x%X\n",h->e_phentsize);
	printf("e_phnum     : 0x%X (%d)\n",h->e_phnum, h->e_phnum);
	printf("e_shentsize : 0x%X\n",h->e_shentsize);
	printf("e_shnum     : 0x%X (%d)\n",h->e_shnum, h->e_shnum);
	printf("e_shstrndx  : %d\n",h->e_shstrndx);
	printf("\n");
	return 0;
}

int PrintProgramHeader(Elf32_Phdr * h)
{
	printf("p_type   : 0x%X ", h->p_type);
	switch(h->p_type)
	{
		case PT_NULL:
		{
			printf("PT_NULL\n");
			break;
		}
		case PT_LOAD:
		{
			printf("PT_LOAD\n");
			break;
		}
		case PT_DYNAMIC:
		{
			printf("PT_DYNAMIC\n");
			break;
		}
		case PT_INTERP:
		{
			printf("PT_INTERP\n");
			break;
		}
		case PT_NOTE:
		{
			printf("PT_NOTE\n");
			break;
		}
		case PT_SHLIB:
		{
			printf("PT_SHLIB\n");
			break;
		}
		case PT_PHDR:
		{
			printf("PT_PHDR\n");
			break;
		}
		case PT_LOPROC:
		{
			printf("PT_LOPROC\n");
			break;
		}
		case PT_HIPROC:
		{
			printf("PT_HIPROC\n");
			break;
		}
		default:
		{
			printf("\n");
		}
	}
	printf("p_offset : 0x%X (%d)\n", h->p_offset, h->p_offset);
	printf("p_vaddr  : 0x%.8X \n", h->p_vaddr);
	printf("p_paddr  : 0x%.8X \n", h->p_paddr);
	printf("p_filesz : 0x%X (%d)\n", h->p_filesz, h->p_filesz);
	printf("p_memsz  : 0x%X (%d)\n", h->p_memsz, h->p_memsz);
	char cflags[32];
	strcpy(cflags, "");
	int f = h->p_flags;
	if(f&PF_X)
	{
		strcat(cflags, "PF_X");
	}
	if(f&PF_W)
	{
		if(strcmp(cflags, "")!=0) strcat(cflags, " | ");
		strcat(cflags, "PF_W");
	}
	if(f&PF_R)
	{
		if(strcmp(cflags, "")!=0) strcat(cflags, " | ");
		strcat(cflags, "PF_R");
	}
	printf("p_flags  : 0x%X (%s)\n", h->p_flags, cflags);
	printf("p_memsz  : 0x%X \n", h->p_align);
	printf("\n");
	return 0;
}

int PrintStringTable(ELF_T * Elf)
{
	int m = strlen(Elf->StringTable);
	int off=0;
	char * s;
	int i=0;                                                      
	while(off < m)
	{
		s = (char*)(Elf->StringTable + off);
		printf("#%d Index: %d Value: %s\n", i, off, s);
		off += strlen(s);
		i++;
	}
	return 0;
}

int PrintSectionHeader(Elf32_Shdr * h, ELF_T * Elf)
{
	printf("sh_name      : %d\n", h->sh_name);
	printf("sh_type      : %d ", h->sh_type);
	switch(h->sh_type)
	{
		case SHT_NULL:
		{
			printf("SHT_NULL\n");
			break;
		}
		case SHT_PROGBITS:
		{
			printf("SHT_PROGBITS\n");
			break;
		}
		case SHT_SYMTAB:
		{
			printf("SHT_SYMTAB\n");
			break;
		}
		case SHT_STRTAB:
		{
			printf("SHT_STRTAB\n");
			break;
		}
		case SHT_RELA:
		{
			printf("SHT_RELA\n");
			break;
		}
		case SHT_HASH:
		{
			printf("SHT_HASH\n");
			break;
		}
		case SHT_DYNAMIC:
		{
			printf("SHT_DYNAMIC\n");
			break;
		}
		case SHT_NOTE:
		{
			printf("SHT_NOTE\n");
			break;
		}
		case SHT_NOBITS:
		{
			printf("SHT_NOBITS\n");
			break;
		}
		case SHT_REL:
		{
			printf("SHT_REL\n");
			break;
		}
		case SHT_SHLIB:
		{
			printf("SHT_SHLIB\n");
			break;
		}
		case SHT_DYNSYM:
		{
			printf("SHT_DYNSYM\n");
			break;
		}
		default:
		{
			printf("\n");
		}
	}
	char cflags[32];
	strcpy(cflags, "");
	int f = h->sh_flags;
	if(f&SHF_WRITE)
	{
		strcat(cflags, "SHF_WRITE");
	}
	if(f&SHF_ALLOC)
	{
		if(strcmp(cflags, "")!=0) strcat(cflags, " | ");
		strcat(cflags, "SHF_ALLOC");
	}
	if(f&SHF_EXECINSTR)
	{
		if(strcmp(cflags, "")!=0) strcat(cflags, " | ");
		strcat(cflags, "SHF_EXECINSTR");
	}
	printf("sh_flags     : 0x%X (%s)\n", h->sh_flags, cflags);
	printf("sh_addr      : 0x%.8X\n", h->sh_addr);
	printf("sh_offset    : 0x%X (%d)\n", h->sh_offset, h->sh_offset);
	printf("sh_size      : 0x%X (%d)\n", h->sh_size, h->sh_size);
	printf("sh_link      : 0x%.8X\n", h->sh_link);
	printf("sh_info      : 0x%.8X\n", h->sh_info);
	printf("sh_addralign : 0x%.8X\n", h->sh_addralign);
	printf("sh_entsize   : 0x%X (%d)\n", h->sh_entsize, h->sh_entsize);

	printf("\n");
	return 0;
}

int main(int argc, char* argv[])
{
	int r=0;
	if(argc != 2 || strcmp(argv[1], "")==0)
	{
		printf("Error in parameters!\n");
		getch();
		return 0;
	}
	else
	{
		printf("Loading '%s'...\n", argv[1]);
	}
	ELF_T * Elf = OpenElf(argv[1]);
	ParseHeader(Elf);
	Elf32_Ehdr * h = &Elf->Header;
	printf("HEADER:\n");
	PrintElfHeader(h);

	ParseProgramHeaders(Elf);
	Elf32_Phdr * p;
	for(int i=0;i<Elf->Header.e_phnum;i++)
	{
		printf("PROGRAM HEADER #%d:\n", i);
		p = &Elf->ProgramHeaders[i];
		PrintProgramHeader(p);
	}

/*	ParseDynamicSegment(Elf);
	PrepareDynamicSegment(Elf);
	PrintStringTable(Elf);     */

	ParseSectionHeaders(Elf);
	Elf32_Shdr * s;
	for(int i=0;i<Elf->Header.e_shnum;i++)
	{
		printf("SECTION HEADER #%d:\n", i);
		s = &Elf->SectionHeaders[i];
		PrintSectionHeader(s, Elf);
	}

	delete Elf;
	getch();
	return 0;
}



