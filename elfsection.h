#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#ifndef __FILE_READER__
#define  __FILE_READER__
#include "filereader.h"
#endif


void affichage_section(char * filePath, Elf32_Shdr *tab);
