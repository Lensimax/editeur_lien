#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "filereader.h"
#include "elfsectiontab.h"

int getIndSectionSymtab(Elf32_Ehdr header,Elf32_Shdr* shtab);

int readSymbtab(Elf32_Ehdr header, Elf32_Shdr * Shtab,Elf32_Sym * Symtab ,char * filePath, int indice_symtab);

void aff_Symtable(Elf32_Shdr * shtab, Elf32_Ehdr header, char * filePath, Elf32_Sym * symtab, int indice_symtab);
