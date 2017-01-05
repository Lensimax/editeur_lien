#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>


#include "filereader.h"



void read_section(char * filePath, Elf32_Ehdr header, Elf32_Shdr *htab, char *section_name, int section_index);
char *nom_section(Elf32_Ehdr header, Elf32_Shdr *Shtab, int section_index, unsigned char* fileBytes, int *j);
