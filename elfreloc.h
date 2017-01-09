#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "filereader.h"
#include "elfsectiontab.h"
#include "util.h"
#include "elfstruct.h"
#include "elfsection.h"


int nbIndSectionReltab(Elf32_Ehdr * header, Elf32_Shdr * Shtab);
int readReloc(Elf32_Rel ** Reltab, Elf32_Ehdr * header, Elf32_Shdr * Shtab, Elf32_Sym * Symtab, char * filePath);
void aff_Reloc(ELF_STRUCT file);

