#include "common.h"

void switchEndian(Elf32_Ehdr *hdr)
{
	CONV16(hdr->e_type);
	CONV16(hdr->e_machine);
	CONV32(hdr->e_version);
	CONV32(hdr->e_entry);
	CONV32(hdr->e_phoff);
	CONV32(hdr->e_shoff);
	CONV32(hdr->e_flags);
	CONV16(hdr->e_ehsize);
	CONV16(hdr->e_phentsize);
	CONV16(hdr->e_phnum);
	CONV16(hdr->e_shentsize);
	CONV16(hdr->e_shnum);
	CONV16(hdr->e_shstrndx);
}

void switchEndian(Elf32_Phdr *hdr)
{

	CONV32(hdr->p_type);
	CONV32(hdr->p_offset);
	CONV32(hdr->p_vaddr);
	CONV32(hdr->p_paddr);
	CONV32(hdr->p_filesz);
	CONV32(hdr->p_memsz);
	CONV32(hdr->p_flags);
	CONV32(hdr->p_align);
}

void switchEndian(Elf32_Shdr *hdr)
{
	CONV32(hdr->sh_name);
	CONV32(hdr->sh_type);
	CONV32(hdr->sh_flags);
	CONV32(hdr->sh_addr);
	CONV32(hdr->sh_offset);
	CONV32(hdr->sh_size);
	CONV32(hdr->sh_link);
	CONV32(hdr->sh_info);
	CONV32(hdr->sh_addralign);
	CONV32(hdr->sh_entsize);
}


void switchEndian(Elf32_Rel *rel)
{
	CONV32(rel->r_offset);
	CONV32(rel->r_info);
}

void switchEndian(Elf32_Sym *sym)
{
	CONV32(sym->st_name);
	CONV32(sym->st_value);
	CONV32(sym->st_size);
	CONV16(sym->st_shndx);
}

void switchEndian(Elf32_Dyn *dyn)
{
	CONV32(dyn->d_tag);
	CONV32(dyn->d_val);
}


__inline UINT64 E64( UINT64 x )
{
	x = x;

	__asm{
		mov	eax, [ebp+0x8]
		mov	edx, [ebp+0xC]
		xchg ah, al
		rol eax, 0x10
		xchg ah,al
		xchg edx, eax
		xchg ah, al
		rol eax, 0x10
		xchg ah,al	
	}

}

__inline UINT32 E32( UINT32 x )
{
	UINT32	res;

	__asm{
		mov	eax, x
		bswap eax
//		xchg ah,al
//		rol eax, 0x10
//		xchg ah,al
		mov	 res, eax
	}
	return res;
}

__inline UINT16 E16(UINT16 x)
{
	UINT16	res;

	__asm{
		xor  eax, eax
		mov	 ax, x
		xchg ah,al
		mov  res, ax
	}
	return res;
}
