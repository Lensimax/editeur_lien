#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "filereader.h"
#include "elfsectiontab.h"
#include "util.h"
#include "elfstruct.h"
#include "elfsection.h"


int nbIndSectionReltab(ELF_STRUCT file);
int readReloc(ELF_STRUCT file);
void aff_Reloc(ELF_STRUCT file);
int IsIndSectionReltab(ELF_STRUCT file, int i);

