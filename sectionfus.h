#ifndef _____SECT_FUS____
#define _____SECT_FUS____

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "elfheader.h"
#include "elfsectiontab.h"

typedef struct {
	char name[256];
	int offset1, size1, offset2, size2;
	int newnum, numorigin;
	int type, fusion, offset;
} sect_tab;

int sectfusion( ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT fileres, sect_tab * tab);

#endif
