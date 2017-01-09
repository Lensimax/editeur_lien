#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <getopt.h>
#include <sys/stat.h>
#include <string.h>
#include "editeur_lien/elfheader.h"
#include "editeur_lien/elfsectiontab.h"
#include "editeur_lien/elfsection.h"
#include "editeur_lien/util.h"
#include "editeur_lien/elfsymbtab.h"
#include "editeur_lien/elfreloc.h"
#include "editeur_lien/fusion.h"

int isnumber(const char*s) {
   char* e = NULL;
   (void) strtol(s, &e, 0);
   return e != NULL && *e == (char)0;
}

int main(int argc, char * argv[]){

	Elf32_Ehdr *header1;
	Elf32_Ehdr *header2;
	Elf32_Shdr *shtab1;
	Elf32_Shdr *shtab2;
	header1 = malloc(sizeof(Elf32_Ehdr));
	header2 = malloc(sizeof(Elf32_Ehdr));

	/*int erreur = 0;
	int indice_symtab;
	int indice_symtabDYN = 0;
	char * file_used = "hola";
	char section[50];*/

	Elf32_Shdr * shres = malloc(sizeof(Elf32_Shdr));
	sect_tab * tab = malloc(sizeof(sect_tab));

	readHeader("ARM.o", header1);
	readHeader("example2.o", header2);
	shtab1 = malloc(sizeof(Elf32_Shdr)*header1->e_shnum);
	readSectTab(shtab1, header1, "ARM.o");
	shtab2 = malloc(sizeof(Elf32_Shdr)*header2->e_shnum);
	readSectTab(shtab2, header2, "example2.o");



	int nbtab = sectfusion( header1, shtab1, "ARM.o", header2,  shtab2, "example2.o", shres , tab);
	Elf32_Ehdr *header= header1;
	header->e_shnum = nbtab;
	fusion( header, shres, tab, nbtab, "ARM.o",  "example2.o");
	aff_Sheader(shres, header, "ARM.o");


}
