#include "elfreloc.h"

Elf32_Sym * readReloc(Elf32_Ehdr header, Elf32_Shdr * Shtab, char * filePath, int isVerbose);
