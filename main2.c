#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <getopt.h>
#include <sys/stat.h>

#include "elfheader.h"
#include "elfsectiontab.h"
#include "elfsection.h"

int main(int argc, char * argv[]){

Elf32_Ehdr header;
Elf32_Shdr *Shtab;
int x;
char name [256];


	header = readHeader("example2.o",0);
	Shtab = readSectTab(header,"example2.o",1);
	printf ("Quelle section afficher ?\n 1: Par le numéro\n 2: par le nom\n");
	scanf ("%i", &x);
	switch (x) {
	case 1: 
		printf("Quel numéro ?\n");
		scanf("%i", &x);
		read_section("example2.o", header, Shtab, "\0", x);
		break;
	case 2:
		printf("Quel nom ?\n");
		scanf("%s", name);
		read_section("example2.o", header, Shtab, name, 0);
		break;
	default:
		printf("Entrez une réponse correcte !\n");
		break;
	}

return 0;
}
