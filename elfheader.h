#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "filereader.h"



void aff_header(Elf32_Ehdr *header);

int readHeader(char *filePath, Elf32_Ehdr *header);