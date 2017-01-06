#include "elfsection.h"


void read_section(char * filePath, Elf32_Ehdr header, Elf32_Shdr *Shtab, char *section_name, int section_index){

	//initialisation des indices
	int i,ind_name, k, j;	
	//creation du tableau de char correspondant au fichier filePath(cf filereader.h)
	unsigned char* fileBytes = readFileBytes(filePath);	
	Elf32_Shdr section;
	//initialisation bit de validite du header
	int isValid = 1;
	//initialisation string pour les noms de sections
	char name[256];

	//chaine vide faire avec l'index
	if(section_name[0] == '\0'){ 
		//si numero de section valide
		if(!(section_index > header.e_shnum)){
			//on rempli section avec la section correspondante
			section = Shtab[section_index-1];
		//si numero de section invalide
		}else {
			//message d'erreur
			printf("Veuillez choisir un numéro de section valable\n");
			//isValid prend donc la valeur false
			isValid = 0;
		}
	// sinon avec le nom de la section
	} else { 
		// recherche du nom de la section
		j = 0;
		isValid = 1;
		//tant qu'on ne depasse pas ne nombre de section et qu'on a pas le nom (strcmp == 0)
		while (j < header.e_shnum && isValid != 0) {
			//placement en debut de table de chaine de char
			ind_name = Shtab[header.e_shstrndx].sh_offset;
			k = 0;
			//placement au debut d'un nom de section
			ind_name =  ind_name + Shtab[j].sh_name;
			//tant qu'on a pas trouve le nom en entier
			while(fileBytes[ind_name] != '\0'){
				//remplissage du nom
				name[k] = fileBytes[ind_name];
				k++;
				ind_name++;
			}
			//ajout marque de fin
			name[k]='\0';
			//on verifie si c'est le bon nom
			isValid = strcmp (name, section_name);
			j++;
		}
		//si on trouve le nom dans aucune table
		if (isValid!=0) {
			//affichage du message d'erreur
			printf("Veuillez donner un nom correct\n");
			isValid = 0;
		//si on a trouve le nom
		} else 
			isValid = 1;
		//on rempli section avec la section correspondante
		section = Shtab[j-1];

	}
	//si on a trouve une reponse valide
	if (isValid == 1) {
		//placement en debut de table de chaine de char
		ind_name = Shtab[header.e_shstrndx].sh_offset;
		k = 0;
		//placement au debut du nom de la section
		ind_name =  ind_name + section.sh_name;
		//tant qu'on est pa sa la fin du nom
		while(fileBytes[ind_name] != '\0'){
			//on remplit le nom
			name[k] = fileBytes[ind_name];
			k++;
			ind_name++;
		}
		//ajout de la marque de fin
		name[k]='\0';
		//affichage du nom de la section
		printf("Contenu de la section %s :", name); // a completer avec String Table
		j = 0;
		//affichage de son contenu
		for(i=section.sh_offset;i<=section.sh_offset+section.sh_size;i++){
		
			printf("%x ", fileBytes[i]);
			j++;
		} 
	}
	printf("\n");

}
