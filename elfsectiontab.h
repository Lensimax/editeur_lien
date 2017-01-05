#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "filereader.h"
#include "util.h"

int readSectTab(Elf32_Shdr * shtab, Elf32_Ehdr * header, char * filePath);

void aff_Sheader(Elf32_Shdr * shtab, Elf32_Ehdr * header, char * filePath);
