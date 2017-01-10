#include "elfsection.h"

//////// RETOURNE LE NOM SELON L INDEX DONNEE

char *nom_section(ELF_STRUCT file, int section_index){
	int k = 0, ind_name;
	char *name;
	name = malloc(sizeof(char)*256);


	ind_name = file.shtab[file.header->e_shstrndx].sh_offset;
	ind_name += file.shtab[section_index].sh_name;
	while(file.fileBytes[ind_name] != '\0'){
		name[k] = file.fileBytes[ind_name];
		k++;
		ind_name++;
	}
	name[k]='\0';

	return name;
}


void aff_section(ELF_STRUCT file, char *section_name, int section_index){

	int i, k, l, trouve, ind_name;
	Elf32_Shdr section;
	int isValid = 1;
	char *name;

	////// RECHERCHE DE LA SECTION CORRESPONDANTE /////


	if(section_name[0] == '\0'){ // chaine vide faire avec l'index
		if(!(section_index > file.header->e_shnum)){
			section = file.shtab[section_index];
			name = nom_section(file, section_index);
			printf("Nom section %s\n", name);
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
		
		while(i<file.header->e_shnum && !trouve){
			ind_name = file.shtab[file.header->e_shstrndx].sh_offset + file.shtab[i].sh_name;
			k = 0;
			while(file.fileBytes[ind_name] != '\0'){
				name[k] = file.fileBytes[ind_name];
				k++;
				ind_name++;
			}

			name[k]='\0';
			if(!strcmp(name, section_name)){
				trouve = 1;
			}
			i++;
		}

		if(trouve){
			
			isValid = 1;
		} else {
			trouve = 0;
			isValid = 0;
			printf("[Error] nom de section invalide\n");
		}
		section = file.shtab[i-1];


	}
		////// AFFICHAGE ///////

	
	if (isValid == 1) {

		printf("Contenu de la section << %s >>\n", name); // a completer avec String Table

		for(i=section.sh_offset; i<section.sh_offset+section.sh_size; i+=16){ // ligne

			printf("0x%.8x | ", i-section.sh_offset); // affichage adresse ligne

			for(k=0; k<4; k++){ /// affichage de l'hexa
				l=i+k*4;
				while(l<i+(k+1)*4 && l<section.sh_offset+section.sh_size){
					printf("%.2x", file.fileBytes[l]);
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
					if(file.fileBytes[l] >= 33 && file.fileBytes[l] < 128){
						printf("%c", file.fileBytes[l]);						
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

	free(name);

}
