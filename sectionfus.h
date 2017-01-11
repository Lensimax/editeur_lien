#ifndef _____SECT_FUS____
#define _____SECT_FUS____

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "elfheader.h"
#include "elfsectiontab.h"

typedef struct {
	char name[256]; // nom de la section
	int offset1, size1; // information de la première section
	int offset2, size2; // information de la deuxième section
	int newnum, numorigin;
	int type, fusion, offset; // si fusion==1 deux sections fusionnées
} sect_tab;

int sectfusion( ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT fileres, sect_tab * tab);

#endif
