
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
#include "elfstruct.h"
#include "elfreloc.h"
#include "fill_struct.h"




int isnumber(const char*s);
int est_present(char ch[], int argc, char* argv[]);

int main(int argc, char* argv[]){

	ELF_STRUCT file;


	int num_section;

	if(argc == 1 || argc == 2){
		printf("\nVeuillez mettre des options pour utiliser la commande, le dernier argument doit etre le fichier\n");
		printf("%20s | pour tout afficher (meme chose que : -h -s -r -S)\n", "-a");
		printf("%20s | pour afficher les infos du header\n", "-h");
		printf("%20s | pour afficher les symboles\n", "-s");
		printf("%20s | pour afficher la section de ce nom ou numéro\n", "-x <nombre/nom>");
		printf("%20s | pour afficher le contenu de toutes les sections\n", "-X");
		printf("%20s | pour afficher les relocs\n", "-r");
		printf("%20s | pour afficher les sections header\n\n", "-S");

	} else {

		////// REMPLISSAGE //////

		if(fill(&file, argv[argc-1])){
			

			/////////////// AFFICHAGE DE TOUT ////////
			if(est_present("-a", argc, argv) != 0){
				printf("\n\t\t\t[ Affichage du header ]\n\n");
				aff_header(file);
				printf("\n\t\t\t[ Affichage des sections header ]\n\n");
				aff_Sheader(file);
				printf("\n\t\t\t[ Affichage des symboles ]\n\n");
				aff_Symtable(file);
				printf("\n\t\t\t[ Affichage des relocations ]\n\n");
				aff_Reloc(file); 
			} else {


				//////////// AFFICHAGE HEADER /////////
				if(est_present("-h", argc, argv) != 0){
					printf("\n\t\t\t[ Affichage du header ]\n\n");
					aff_header(file);
				}

				/////// AFFICHAGE SECTION HEADER ////
				if(est_present("-S", argc, argv) != 0){
					printf("\n\t\t\t[ Affichage des sections header ]\n\n");
					aff_Sheader(file);
				}

				//////////// AFFICHAGE DES SYMBOLES ////////
				if(est_present("-s", argc, argv) != 0){
					printf("\n\t\t\t[ Affichage des symboles ]\n\n");
					aff_Symtable(file);
				}

				if(est_present("-X", argc, argv) != 0){
					printf("\n\t\t\t[ Affichage du contenu des sections ]\n\n");
					for(int i=0; i<file.header->e_shnum; i++){
						aff_section(file, "", i);
					}
				}


				////////// AFFICHAGE DE LA SECTION DONNEE//////////
				num_section = est_present("-x", argc, argv);
				if(num_section != 0){
					if(num_section+1<argc-1){
						printf("\n\t\t\t[ Affichage de la section %s ]\n\n", argv[num_section+1]);
						if(isnumber(argv[num_section+1])){
							aff_section(file, "", atoi(argv[num_section+1]));
						} else {
							aff_section(file, argv[num_section+1], 1);
						}
					} else {
						printf("[main.c] Error invalid section name\n");
					}
				}

				if(est_present("-r", argc, argv)){
					printf("\n\t\t\t[ Affichage des relocations ]\n\n");
					aff_Reloc(file); 
				}

				
			}
			free(file.header);
			free(file.shtab);
			free(file.symtab);
			for(int i=0;i<nbIndSectionReltab(file);i++){
				free(file.tabrel[i].reltab);
			}
			free(file.tabrel);
		} else {
			printf("Erreur de lecture fichiers\n");
			return 1;
		}
	}


	return 0;
}


////// FIN MAIN ///////


 // renvoie si la chaine est un nombre
int isnumber(const char*s) {
   char* e = NULL;
   (void) strtol(s, &e, 0);
   return e != NULL && *e == (char)0;
}


// renvoie l'indice de l'option si elle est presente sinon 0
int est_present(char ch[], int argc, char *argv[]){
	int i = 1;

	while(i<argc-1 && strcmp(ch, argv[i])){
		i++;
	} 

	if(strcmp(ch, argv[i]) == 0){
		return i;
	} else {
		return 0;
	}

}

