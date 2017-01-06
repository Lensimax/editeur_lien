#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "filereader.h"
#include "elfsectiontab.h"
#include "util.h"


int nbIndSectionReltab(Elf32_Ehdr * header, Elf32_Shdr * Shtab);
int nbIndSectionRelatab(Elf32_Ehdr * header, Elf32_Shdr * Shtab);
int readReloc(Elf32_Rel ** Reltab, Elf32_Rela ** Relatab, Elf32_Ehdr * header, Elf32_Shdr * Shtab, Elf32_Sym * Symtab, char * filePath,/* int Indice_Reltab, int Indice_Relatab,*/ int isVerbose);

int printReloc( Elf32_Sym * Symtab);
