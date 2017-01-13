#ifndef _____SECT_FUS____
#define _____SECT_FUS____

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "elfheader.h"
#include "elfsectiontab.h"
#include "elfstruct.h"


sect_tab * sectfusion( ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT * fileres, sect_tab * tab);

#endif
