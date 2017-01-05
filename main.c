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

int isnumber(const char*s) {
   char* e = NULL;
   (void) strtol(s, &e, 0);
   return e != NULL && *e == (char)0;
}

int main(int argc, char * argv[]){

	Elf32_Ehdr *header;
	Elf32_Shdr *shtab;
	header = malloc(sizeof(Elf32_Ehdr));

	char * file_used = "ARM.o";
	char section[50];

	if(readHeader(file_used, header)){
		
		//aff_header(header);
		
		shtab = malloc(sizeof(Elf32_Shdr)*header->e_shnum);

		if(readSectTab(shtab, header, file_used)){

			aff_Sheader(shtab, header, file_used);

			printf("Choisir un nom ou un numero de section pour affichage complet :\n");
			scanf("%s", section);
			printf("\n");
			if(isnumber(section)){
				 
				read_section(file_used, *header, shtab, "", atoi(section)+1);
			}
			else{
				read_section(file_used, *header, shtab, section, 1);
			}
		

		} else {
			return 1;
		}
	
	} else {
		return 1;
	}
	return 0;
}
