#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "filereader.h"
#include "elfsymbtab.h"
#include "sectionfus.h"

int symbolfus(ELF_STRUCT file_1, ELF_STRUCT file_2, ELF_STRUCT * file_final, sect_tab * sect_fus, int nb_sect_after_fusion);
