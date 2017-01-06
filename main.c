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


int isnumber(const char*s) {
   char* e = NULL;
   (void) strtol(s, &e, 0);
   return e != NULL && *e == (char)0;
}

int main(int argc, char * argv[]){

	Elf32_Ehdr *header;
	Elf32_Shdr *shtab;
	Elf32_Sym *symtab;
	Elf32_Rel **Reltab;
	Elf32_Rela **Relatab;
	header = malloc(sizeof(Elf32_Ehdr));
	int erreur = 0;
	int indice_symtab;
	char * file_used = "ARM.o";
	char section[50];

	if(readHeader(file_used, header)){
		
		//aff_header(header);				/////////AFFICHAGE HEADER///////////
		
		shtab = malloc(sizeof(Elf32_Shdr)*header->e_shnum);

		if(readSectTab(shtab, header, file_used)){

			aff_Sheader(shtab, header, file_used);			/////////AFFICHAGE HEADER SECTIONS///////////
			printf("Choisir un nom ou un numero de section pour affichage complet :\n");
			scanf("%s", section);
			printf("\n");
			
			if(isnumber(section)){
				 
				read_section(file_used, *header, shtab, "", atoi(section)+1);		/////////AFFICHAGE UNE SECTION///////////
			}
			else{
				read_section(file_used, *header, shtab, section, 1);				/////////AFFICHAGE UNE SECTION///////////
			}
			
			indice_symtab = getIndSectionSymtab(header,shtab);
			
			symtab = malloc(sizeof(Elf32_Sym)*(shtab[indice_symtab].sh_size/shtab[indice_symtab].sh_entsize));

			if(readSymbtab(*header, shtab, symtab, file_used, indice_symtab)){
				
				aff_Symtable(shtab, *header, file_used, symtab, indice_symtab);
				// PARTIE REL/RELA
				Reltab = malloc(sizeof(Elf32_Rel*)*(nbIndSectionReltab(header, shtab)));
				Relatab = malloc(sizeof(Elf32_Rela*)*(nbIndSectionRelatab(header, shtab)));
				readReloc(Reltab, Relatab, header, shtab, symtab, file_used, 1);

			} else {
				erreur = 1;
			} 

		} else {
			erreur = 1;
		}
	
	} else {
		erreur = 1;
	}

	if (!erreur){
		return 1;
	}

	return 0;
}
