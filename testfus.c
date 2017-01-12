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
#include "sectionfus.h"
#include "filereader.h"
#include "fill_struct.h"
#include "filewriter.h"
#include "symbolfus.h"
#include "fusrel.h"


void affichage_struct(ELF_STRUCT file);

int main(int argc, char * argv[]){

	ELF_STRUCT file1;
	ELF_STRUCT file2;
	ELF_STRUCT res;
	sect_tab *tab;
	//sect_tab **tab2=&tab;

	int nombre_section_apres_fusion;

	FILE *fich;

	if(argc == 1 || argc == 2 || argc == 3){
		printf("\nEntrer au moins trois fichiers en argument le dernier etant le fichier resultat!!!!!!\n\n");
	} else {

		fich = fopen(argv[argc-1], "w");
		strcpy(res.file_name,argv[argc-1]);
		if(fich){
			if(fill(&file1, argv[1]) && fill(&file2, argv[2])){

				// affichage_struct(file1);

				tab = malloc(sizeof(sect_tab));
				res.shtab = malloc(sizeof(Elf32_Shdr));
				res.symtab = malloc(sizeof(STRUCT_SYM));


				tab = sectfusion(file1, file2, &res, tab);
				nombre_section_apres_fusion=res.header->e_shnum;

				/*for (int i = 0; i< nombre_section_apres_fusion; i++){

					printf("offset après %d % d \n", tab[i].offset1 ,i );
				}*/

				printf("Nombre section %d\n", nombre_section_apres_fusion);
				//symbolfus(file1,file2, &res, tab, nombre_section_apres_fusion);				
				//relfus(file1, file2, &res);
				
				fusion(file1,file2,res,tab,nombre_section_apres_fusion);
			
				//affichage_struct(res);

				/*if(Write_file(file1, fich)){
					printf("Ecriture faites\n");
				} else {
					printf("Ecriture echouée\n");
				}*/


			} else {
				printf("[E] Erreur lors du remplissage \n");
			}
			
		} else {
			printf("Erreur d\'ouverture du fichier resultat : %s\n", argv[3]);
		}

		fclose(fich);
	/*	free(res.symtab);
		free(res.shtab);
		free(res.tabrel);*/
	}





	return 0;


}


void affichage_struct(ELF_STRUCT file){
	printf("\n\t\t\t[ Affichage du header ]\n\n");
	aff_header(file);
	printf("\n\t\t\t[ Affichage des sections header ]\n\n");
	aff_Sheader(file);
	printf("\n\t\t\t[ Affichage des symboles ]\n\n");
	aff_Symtable(file);
	/*printf("\n\t\t\t[ Affichage des relocations ]\n\n");
	aff_Reloc(file); */	
}
