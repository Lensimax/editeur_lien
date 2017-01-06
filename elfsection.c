#include "elfsection.h"

//////// RETOURNE LE NOM SELON L INDEX DONNEE

char *nom_section(Elf32_Ehdr header, Elf32_Shdr *Shtab, int section_index, unsigned char* fileBytes){
	int k = 0, ind_name;
	char *name;
	name = malloc(sizeof(char)*256);


	ind_name = Shtab[header.e_shstrndx].sh_offset;
	ind_name += Shtab[section_index-1].sh_name;
	while(fileBytes[ind_name] != '\0'){
		name[k] = fileBytes[ind_name];
		k++;
		ind_name++;
	}
	name[k]='\0';

	return name;
}


void read_section(char * filePath, Elf32_Ehdr header, Elf32_Shdr *Shtab, char *section_name, int section_index){

	int i, k, l, trouve, ind_name;
	unsigned char* fileBytes = readFileBytes(filePath);
	Elf32_Shdr section;
	int isValid = 1;
	char *name;

	////// RECHERCHE DE LA SECTION CORRESPONDANTE /////

	if(section_name[0] == '\0'){ // chaine vide faire avec l'index
		if(!(section_index > header.e_shnum)){
			section = Shtab[section_index-1];
		}
		else {
			printf("Veuillez choisir un numéro de section valable\n");
			isValid = 0;
		}
	} else { // sinon avec le nom de la section #galère
			// Searching the name of the section
		name = malloc(sizeof(char)*256);

		i = 0;
		trouve = 0;
		
		while(i<header.e_shnum && !trouve){
			ind_name = Shtab[header.e_shstrndx].sh_offset + Shtab[i].sh_name;
			k = 0;
			while(fileBytes[ind_name] != '\0'){
				name[k] = fileBytes[ind_name];
				k++;
				ind_name++;
			}

			name[k]='\0';
			trouve = strcmp(name, section_name);
			i++;
		}

		if(trouve){
			printf("Section trouve %s\n", section_name;
			isValid = 1;
		} else {
			printf("Fichier non trouve");
			trouve = 0;
		}
		
		section = Shtab[i];

	}
		////// AFFICHAGE ///////

	
	if (isValid == 1) {


		name = nom_section(header, Shtab, section_index, fileBytes);

		printf("Contenu de la section %s :\n", name); // a completer avec String Table

		for(i=section.sh_offset; i<section.sh_offset+section.sh_size; i+=16){ // ligne

			printf("0x%.8x | ", i-section.sh_offset); // affichage adresse ligne

			for(k=0; k<4; k++){ /// affichage de l'hexa
				l=i+k*4;
				while(l<i+(k+1)*4 && l<section.sh_offset+section.sh_size){
					printf("%.2x", fileBytes[l]);
					l++;
				}

				while(l<i+(k+1)*4){ // remplissage des vides 
					printf("  ");
					l++;
				}
				printf(" ");
			}

			printf("| ");

			for(k=0; k<4; k++){ //// affichage des caractère
				l=i+k*4;
				while(l<i+(k+1)*4 && l<section.sh_offset+section.sh_size){
					if(fileBytes[l] >= 33 && fileBytes[l] < 128){
						printf("%c", fileBytes[l]);						
					} else {
						printf(".");
					}
					l++;
				}
			}

			printf("\n");

		}

	}
	printf("\n");


}
