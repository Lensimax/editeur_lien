#include "elfsection.h"


void read_section(char * filePath, Elf32_Ehdr header, Elf32_Shdr *Shtab, char *section_name, int section_index){

	int i,ind_name, k, j;
	unsigned char* fileBytes = readFileBytes(filePath);
	Elf32_Shdr section;
	int isValid = 1;
	char name[256];

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
		j = 0;
		isValid = 1;
		while (j < header.e_shnum && isValid != 0) {
			ind_name = Shtab[header.e_shstrndx].sh_offset;
			k = 0;
			ind_name =  ind_name + Shtab[j].sh_name;
			while(fileBytes[ind_name] != '\0'){
				name[k] = fileBytes[ind_name];
				k++;
				ind_name++;
			}
			name[k]='\0';
			isValid = strcmp (name, section_name);
			j++;
		}
		if (isValid!=0) {
			printf("Veuillez donner un nom correct\n");
			isValid = 0;
		} else 
			isValid = 1;
		section = Shtab[j-1];

	}
	
	if (isValid == 1) {
		ind_name = Shtab[header.e_shstrndx].sh_offset;
		k = 0;
		ind_name =  ind_name + section.sh_name;
		while(fileBytes[ind_name] != '\0'){
			name[k] = fileBytes[ind_name];
			k++;
			ind_name++;
		}
		name[k]='\0';
		printf("Contenu de la section %s :", name); // a completer avec String Table
		j = 0;
		for(i=section.sh_offset;i<=section.sh_offset+section.sh_size;i++){
		
			printf("%x ", fileBytes[i]);
			j++;
		} 
	}
	printf("\n");

}
