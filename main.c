#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <getopt.h>
#include <sys/stat.h>

#include "elfheader.h"
#include "elfsectiontab.h"

int main(int argc, char * argv[]){

	Elf32_Ehdr *header;

	header = malloc(sizeof(Elf32_Ehdr));


	if(readHeader("example2.o", header)){
		
		aff_header(header);
		






		return 0;
	} else {
		return 1;
	}

}
