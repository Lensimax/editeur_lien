#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "elfheader.h"
#include "elfsectiontab.h"

typedef struct {
	char name[256];
	int type, offset1, size1, offset2, size2, newnum, numorigin;
} sect_tab;

int sectfusion( ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT fileres, sect_tab * tab);
