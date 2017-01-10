#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "filereader.h"
#include "elfsymbtab.h"
#include "sectionfus.h"

int symbolfus(char * filePath_1, char * filePath_2, Elf32_Ehdr header_1, Elf32_Ehdr header_2, Elf32_Shdr * shtab_1, Elf32_Shdr * shtab_2, Elf32_Sym * symtab_1, Elf32_Sym * symtab_2, sect_tab * sect_fus, Elf32_Sym * symtab_final, int nb_sect_after_fusion, int * resultat_nb_symboles);
