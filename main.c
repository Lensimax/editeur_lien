#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <getopt.h>
#include <sys/stat.h>

#include "elfheader.h"
#include "elfsectiontab.h"

int main(int argc, char * argv[]){

Elf32_Ehdr header;


	header = readHeader("example2.o",0);
	readSectTab(header,"example2.o",1);


return 0;
}
