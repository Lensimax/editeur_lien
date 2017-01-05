#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "filereader.h"
#include "elfsectiontab.h"
#include "util.h"


Elf32_Reloc readReloc(Elf32_rel * Reltab, Elf32_Ehdr header, Elf32_Shdr * Shtab, Elf32_Sym * Symtab, char * filePath, int isVerbose);

int printReloc( Elf32_Sym * Symtab);
