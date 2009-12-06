
#ifndef COMMON_H
#define COMMON_H

#include "typedefs.h"
#include "elf.h"

extern bool bigend;

/*---------------------------------------------*\
|			Endianness operations				|
\*---------------------------------------------*/

void switchEndian(Elf32_Ehdr *hdr);
void switchEndian(Elf32_Shdr *hdr);
void switchEndian(Elf32_Phdr *hdr);
void switchEndian(Elf32_Sym *sym);
void switchEndian(Elf32_Dyn *dyn);
void switchEndian(Elf32_Rel *rel);

UINT64 E64( UINT64 x );
UINT32 E32( UINT32 x );
UINT16 E16(UINT16 x);


#define CONV16(x) ((x) = E16(x));
#define CONV32(x) ((x) = E32(x));



#endif