#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>


#include "filereader.h"


/*prend en entrée un nom de fichier, un Elf32_Ehdr, un Elf32_Shdr ainsi qu'un char* et un int
elle affiche la section recherchée soit par son nom soit par son index (si le nom est vide) et rempli ces deux champs par effet de bord */
void aff_section(char * filePath, Elf32_Ehdr header, Elf32_Shdr *Shtab, char *section_name, int section_index);

char *nom_section(Elf32_Ehdr header, Elf32_Shdr *Shtab, int section_index, unsigned char* fileBytes);
