#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "filereader.h"
#include "elfsectiontab.h"

int readSymbtab(Elf32_Ehdr *header, Elf32_Shdr * Shtab,Elf32_Sym * Symtab ,char * filePath, int isVerbose);
