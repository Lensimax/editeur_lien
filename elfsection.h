#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "elfheader.h"

Elf32_Shdr * readSectTab(Elf32_Ehdr header,char * filePath, int isVerbose);
