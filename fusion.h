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


void affichebin1(unsigned char n);


void affichebin2(Elf32_Word n);


void affichebin4(Elf32_Half n);



void fusion(Elf32_Ehdr * header, sect_tab * tab, int nbtab,char *filePath1, char *filePath2);

