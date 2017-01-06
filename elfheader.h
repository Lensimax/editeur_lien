#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "util.h"
#include "filereader.h"


//affiche le contenu du Elf32_Ehdr * donné en parametre*/
void aff_header(Elf32_Ehdr *header);

/*prend en parametre le nom du'un fichier et un Elf32_Ehdr * qui sera rempli par effet de bord
il contient l'integralité du header donné*/
int readHeader(char *filePath, Elf32_Ehdr *header);
