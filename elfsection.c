#include "elfsection.h"

int getindxsct(char * name, Elf32_Ehdr header, ){
	
}

void affichage_section(char * filePath, Elf32_Ehdr header, Elf32_Shdr *tab, char *section_name, int section_index){

	int i,ind_name;
	unsigned char* fileBytes = readFileBytes(filePath);
	Elf32_Shdr section;
	int isValid = 1;

	if(section_name[0] == '\0'){ // chaine vide faire avec l'index
		if(!(section_index > header.e_shnum)){
			section = tab[section_index-1];
		}
		else {
			printf("Veuillez choisir un numéro de section valable\n");
			isValid = 0;
		}
	} else { // sinon avec le nom de la section #galère
			// Searching the name of the section
			ind_name = header.e_shstrndx;
			for (int k = 0; k < (int) tab[j].sh_name; k++) {
				while (fileBytes[ind_name] != '\0')
					ind_name++;
				ind_name++;
			}		


	}
	
	if (isValid == 1) {
		printf("Contenu de la section %d :", section.sh_name); // a completer avec String Table

		for(i=section.sh_offset;i<=section.sh_offset+section.sh_size;i++){

			printf("%x ", fileBytes[i]);
		} 
	}

}
