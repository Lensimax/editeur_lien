#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "util.h"
#include "filereader.h"
#include "elfstruct.h"


//affiche le contenu du Elf32_Ehdr * donné en parametre*/
void aff_header(ELF_STRUCT file);

/*prend en parametre le nom du'un fichier et un Elf32_Ehdr * qui sera rempli par effet de bord
il contient l'integralité du header donné*/
int readHeader(ELF_STRUCT file);
