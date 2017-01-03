#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "filereader.h"

Elf32_Ehdr readHeader(char * filePath, int isVerbose);
