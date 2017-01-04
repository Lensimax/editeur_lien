#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>


#include "filereader.h"



void read_section(char * filePath, Elf32_Ehdr header, Elf32_Shdr *htab, char *section_name, int section_index);
