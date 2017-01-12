#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <getopt.h>
#include <sys/stat.h>
#include <string.h>
#include "elfheader.h"
#include "elfsectiontab.h"
#include "elfsection.h"
#include "util.h"
#include "elfsymbtab.h"
#include "elfreloc.h"
#include "sectionfus.h"


void fusion(ELF_STRUCT file1, ELF_STRUCT file2 ,ELF_STRUCT * res, sect_tab * tab, int nbtab);

