#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "filereader.h"
#include "elfsectiontab.h"

typedef struct {
	Elf32_Rel * Reltab;
	Elf32_Rela * Relatab;
} Elf32_Reloc;

Elf32_Reloc readReloc(Elf32_Ehdr header, Elf32_Shdr * Shtab, char * filePath, int isVerbose);

int printReloc( Elf32_Sym * Symtab);
