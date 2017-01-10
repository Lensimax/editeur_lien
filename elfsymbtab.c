#include "elfsymbtab.h"

///////RECHERCHE de la section correspondant a la table des symboles SHT_SYMTAB
int getIndSectionSymtab(Elf32_Ehdr * header,Elf32_Shdr* shtab) {

	int i;
	for(i=0;i<header->e_shnum;i++){
		if (shtab[i].sh_type == 2) {
			return i;
		}
	}
	return 0;
}

///////RECHERCHE de la section correspondant a la table des symboles SHT_DYNSYM
int getIndSectionDynsym(Elf32_Ehdr * header,Elf32_Shdr* shtab) {
	int i;
	for(i=0;i<header->e_shnum;i++){
		if (shtab[i].sh_type == 11) {
			return i;
		}
	}
	return 0;
}

///////LECTURE de la table des symboles////////////////////////////////////////////////////////////////////////////
int readSymbtab(ELF_STRUCT file){
	//initialisation compteur
	int j;
	FILE *f;

	//ouverture du fichier filePath
	//printf("dans section tab %s\n", file.file_name);
	f = fopen(file.file_name, "r");

	//si l'ouverture a reussi
	if(f != NULL){
	
		//on se place en debut de table des strings
		fseek(f, file.shtab[file.indice_symtab].sh_offset, SEEK_SET);
	
		//on cherche le nombre de symboles (taille de la section/taille d'un symbole)
		for (j=0; j<file.shtab[file.indice_symtab].sh_size/file.shtab[file.indice_symtab].sh_entsize; j++){

			fread(&file.symtab[j], file.shtab[file.indice_symtab].sh_entsize, 1, f);

		}
		//fermeture du fichier
		fclose(f);
	
		//inversion des octets si on a un problème de boutisme	
		if((file.header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((file.header->e_ident[EI_DATA] == 2) && !is_big_endian())) {


			for (j=0; j<file.shtab[file.indice_symtab].sh_size/file.shtab[file.indice_symtab].sh_entsize; j++){

				file.symtab[j].st_name = reverse_4(file.symtab[j].st_name);
				file.symtab[j].st_value = reverse_4(file.symtab[j].st_value);
				file.symtab[j].st_size = reverse_4(file.symtab[j].st_size);
				file.symtab[j].st_shndx = reverse_2(file.symtab[j].st_shndx);
						
			
			}

		
		}
	//si l'ouverture a echoue
	} else {
		//affichage du message d'erreur
		printf("Probleme ouverture fichier(table symbole)\n");
		return 0;
	}


		return 1;
}



////////AFFICHAGE
void aff_Symtable(ELF_STRUCT file){

	//remplissage du tableau de char avec le contenu du fichier filePath (cf readfile.h)
	char * nameString;
	//initialisation des variables
	int j, bind, type, i,addrStrName;
	int numSymb = 0;

	//affichage des entete de colonne du tableau 
	printf("  Num:   |    Valeur  |   Tail   |   Type   |   Lien  |  Ndx  | Nom\n");

	//pour chaque symbole
	for (j=0; j<file.shtab[file.indice_symtab].sh_size/file.shtab[file.indice_symtab].sh_entsize; j++){

		//on affiche les information du symbole
		printf("   %4d:",numSymb);
		numSymb++;

		printf(" |  %08x",file.symtab[j].st_value);

		printf("  |   %4d",file.symtab[j].st_size);

		printf("   | ");

		//recuperation du bind et du type contenu dans st_info
		bind = ELF32_ST_BIND(file.symtab[j].st_info);
		type = ELF32_ST_TYPE(file.symtab[j].st_info);

		//affichage du type
		switch(type){
			      case 0:
				printf("NOTYPE "); break;
			      case 1:
				printf("OBJECT "); break;
			      case 2:
				printf("FUNC   "); break;
			      case 3:
				printf("SECTION"); break;
			      case 4:
				printf("FILE   "); break;
			      case 13:
				printf("LOPROC "); break;
			      case 15:
				printf("HIPROC "); break;
			      default:
				printf("UNKNOWN"); break;
		}
		printf("  |");
		//affichage du bind
		switch(bind){
			      case 0:
				printf("%8s", "LOCAL"); break;
			      case 1:
				printf("%8s", "GLOBAL"); break;
			      case 2:
				printf("%8s", "WEAK"); break;
			      case 13:
				printf("%8s", "LOPROC"); break;
			      case 15:
				printf("%8s", "HIPROC"); break;
			      default:
				printf("%8s", "UKN"); break;
			    }
		printf(" |\t");

		//affichage de l'index
		switch(file.symtab[j].st_shndx){
			      case SHN_UNDEF:
				printf("UND");
				break;
			      case SHN_ABS:
				printf("ABS");
				break;
			      default:
				printf("%3d",file.symtab[j].st_shndx);
				break;
		}

		printf(" | ");

		for(i=0;i<file.header->e_shnum;i++){
			if(i != file.header->e_shstrndx && file.shtab[i].sh_type == 3){
				addrStrName = file.shtab[i].sh_offset;					
			}
		}
		

		//on suppose le nom d'un symbole inferieur a 75 char
		nameString = malloc(sizeof(char)*75);
		//position en debut de nom du symbole
		addrStrName = addrStrName+file.symtab[j].st_name;
		i = 0;
			//recuperation du symbole
		    while(file.fileBytes[addrStrName] != '\0'){
			nameString[i] = file.fileBytes[addrStrName];
			addrStrName++;
			i++;
		    }
		//ajout de la marque de fin
		nameString[i] = 0;

		//affichage du nom du symbole
		printf(" %s",nameString);

		printf("\n");

	}
	printf("\n");
}


