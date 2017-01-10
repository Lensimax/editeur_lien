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
#include "fusion.h"
//#include "sectionfus.h"
#include "filereader.h"
#include "fill_struct.h"


int main(int argc, char * argv[]){

	ELF_STRUCT file1;
	ELF_STRUCT file2;
	ELF_STRUCT res;

	FILE *fich;

	if(argc == 1 || argc == 2 || argc == 3){
		printf("\nEntrer au moins trois fichiers en argument le dernier etant le fichier resultat!!!!!!\n\n");
	} else {

		fich = fopen(argv[argc+1], "w");

		if(fich){
			if(fill(&file1, argv[1]) && fill(&file2, argv[2])){



				int nbtab = sectfusion( file1, file2, res , tab);
				file1.header->e_shnum = nbtab;

				res.file=file1.file;
				res.header->e_shnum=nbtab;




			} else {
				printf("[E] Erreur lors du remplissage \n");
			}
			
		} else {
			printf("Erreur d\'ouverture du fichier resultat : %s\n", argv[3]);
		}

		fclose(fich);
	}


	
	


}
