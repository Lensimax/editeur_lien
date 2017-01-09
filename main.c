
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




int isnumber(const char*s);
int est_present(char ch[], int argc, char* argv[]);

int main(int argc, char* argv[]){

	ELF_STRUCT file;


	int num_section;

	if(argc == 1 || argc == 2){
		printf("Veuillez mettre des options pour utiliser la commande, le dernier argument doit etre le fichier\n");
		printf("%20s | pour tout afficher (meme chose que : -h -s -r -S)\n", "-a");
		printf("%20s | pour afficher les infos du header\n", "-h");
		printf("%20s | pour afficher les symboles\n", "-s");
		printf("%20s | pour afficher la section de ce nom ou numéro\n", "-x <nombre/nom>");
		printf("%20s | pour afficher les relocs\n", "-r");
		printf("%20s | pour afficher les sections header\n", "-S");

	} else {

		////// REMPLISSAGE //////

		//strcpy(argv[argc-1], argv[argc-1]);

		strcpy(file.file_name, argv[argc-1]);
		file.fileBytes = readFileBytes(argv[argc-1]);

		file.header = malloc(sizeof(Elf32_Ehdr));

		if(readHeader(file)){
			printf("Lecture header done!\n"); // DEBUG

			file.shtab = malloc(sizeof(Elf32_Shdr)*file.header->e_shnum);

			if(readSectTab(file)){
				printf("Lecture sections header done!\n"); // DEBUG

				file.indice_symtab = getIndSectionSymtab(file.header,file.shtab);
				file.symtab = malloc(sizeof(Elf32_Sym)*(file.shtab[file.indice_symtab].sh_size/file.shtab[file.indice_symtab].sh_entsize));

				if(readSymbtab(file)){
					printf("Lecture symbole tab done!\n"); // DEBUG

					file.Reltab = malloc(sizeof(Elf32_Rel*)*(nbIndSectionReltab(file.header, file.shtab)));

					if(readReloc(&file.Reltab, file.header, file.shtab, file.symtab, argv[argc-1])){
						printf("Lecture reloc done!\n"); // DEBUG



					} else {
						printf("[Error] Lecture Symbole tab\n"); // DEBUG
						return 1;
					}


				} else {
					printf("[Error] Lecture Symbole tab\n"); // DEBUG
					return 1;
				}

			} else {
				printf("[Error] Lecture SHTAB\n"); // DEBUG
				return 1;
			}

		} else {
			printf("[Error] Lecture HEADER\n"); // DEBUG
			return 1;
		}





		/////////////// AFFICHAGE DE TOUT ////////
		if(est_present("-a", argc, argv)){
			printf("\n\t\t\t[ Affichage du header ]\n\n");
			aff_header(file);
			printf("\n\t\t\t[ Affichage des sections header ]\n\n");
			aff_Sheader(file);
			printf("\n\t\t\t[ Affichage des symboles ]\n\n");
			aff_Symtable(file);
		} else {


			//////////// AFFICHAGE HEADER /////////
			if(est_present("-h", argc, argv)){
				printf("\n\t\t\t[ Affichage du header ]\n\n");
				aff_header(file);
			}

			/////// AFFICHAGE SECTION HEADER ////
			if(est_present("-S", argc, argv)){
				printf("\n\t\t\t[ Affichage des sections header ]\n\n");
				aff_Sheader(file);
			}

			//////////// AFFICHAGE DES SYMBOLES ////////
			if(est_present("-s", argc, argv)){
				printf("\n\t\t\t[ Affichage des symboles ]\n\n");
				aff_Symtable(file);
			}


			////////// AFFICHAGE DE LA SECTION DONNEE//////////
			num_section = est_present("-x", argc, argv);
			if(num_section){
				if(num_section+1<argc-1){
					printf("\n\t\t\t[ Affichage de la section %s ]\n\n", argv[num_section+1]);
					if(isnumber(argv[num_section+1])){
						aff_section(argv[argc-1], *file.header, file.shtab, "", atoi(argv[num_section+1]));
					} else {
						aff_section(argv[argc-1], *file.header, file.shtab, argv[num_section+1], 1);
					}
				} else {
					printf("[main.c] Error invalid section name\n");
				}
			}

			if(est_present("-r", argc, argv)){
				printf("\n\t\t\t[ Affichage des relocations ]\n\n");

				////// A CHANGER DANS LE ELFRELOC //// 

				//aff_Reloc(file); 
			}

			
		}
		free(file.header);
		free(file.shtab);
		free(file.symtab);
		free(file.Reltab);
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
int est_present(char ch[], int argc, char* argv[]){

	int i = 1;


	while(i<argc-1 && !strcmp(ch, argv[i])){
		i++;
	}

	if(!strcmp(ch, argv[i-1])){
		return i-1;
	} else {
		return 0;
	}

}

