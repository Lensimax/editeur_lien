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
		if (shtab[i].sh_type == 6) {
			return i;
		}
	}
	return 0;
}

///////LECTURE de la table des symboles
int readSymbtab(Elf32_Ehdr header, Elf32_Shdr * shtab, Elf32_Sym * symtab ,char * filePath, int indice_symtab){
	//initialisation compteur
	int j;
	FILE *f;

	//ouverture du fichier filePath
	f = fopen(filePath, "r");

	//si l'ouverture a reussi
	if(f != NULL){
	
		//on se place en debut de table des strings
		fseek(f, shtab[indice_symtab].sh_offset, SEEK_SET);
	
		//on cherche le nombre de symboles (taille de la section/taille d'un symbole)
		for (j=0; j<shtab[indice_symtab].sh_size/shtab[indice_symtab].sh_entsize; j++){

			fread(&symtab[j], shtab[indice_symtab].sh_entsize, 1, f);

		}
		//fermeture du fichier
		fclose(f);
	
		//inversion des octets si on a un problème de boutisme	
		if((header.e_ident[EI_DATA] == 1 && is_big_endian()) || ((header.e_ident[EI_DATA] == 2) && !is_big_endian())) {


			for (j=0; j<shtab[indice_symtab].sh_size/shtab[indice_symtab].sh_entsize; j++){

				symtab[j].st_name = reverse_4(symtab[j].st_name);
				symtab[j].st_value = reverse_4(symtab[j].st_value);
				symtab[j].st_size = reverse_4(symtab[j].st_size);
				symtab[j].st_shndx = reverse_2(symtab[j].st_shndx);
						
			
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
void aff_Symtable(Elf32_Shdr * shtab, Elf32_Ehdr header, char * filePath, Elf32_Sym * symtab, int indice_symtab){

	//remplissage du tableau de char avec le contenu du fichier filePath (cf readfile.h)
	unsigned char* fileBytes = readFileBytes(filePath);
	char * nameString;
	//initialisation des variables
	int j, bind, type, i,addrStrName;
	int numSymb = 0;
	printf("\n");
	//affichage des entete de colonne du tableau 
	printf("  Num:    Valeur Tail   Type     Lien   Ndx Nom\n");

	//pour chaque symbole
	for (j=0; j<shtab[indice_symtab].sh_size/shtab[indice_symtab].sh_entsize; j++){

		//on affiche les information du symbole
		printf("   %2d:",numSymb);
		numSymb++;

		printf("  %08x",symtab[j].st_value);

		printf("   %2d",symtab[j].st_size);

		printf("   ");

		//recuperation du bind et du type contenu dans st_info
		bind = ELF32_ST_BIND(symtab[j].st_info);
		type = ELF32_ST_TYPE(symtab[j].st_info);

		//affichage du type
		switch(type){
			      case 0:
				printf("NOTYPE ");
				break;
			      case 1:
				printf("OBJECT ");
				break;
			      case 2:
				printf("FUNC   ");
				break;
			      case 3:
				printf("SECTION");
				break;
			      case 4:
				printf("FILE   ");
				break;
			      case 13:
				printf("LOPROC ");
				break;
			      case 15:
				printf("HIPROC ");
				break;
			      default:
				printf("UNKNOWN");
		}
		printf("  ");
		//affichage du bind
		switch(bind){
			      case 0:
				printf("LOCAL ");
				break;
			      case 1:
				printf("GLOBAL");
				break;
			      case 2:
				printf("WEAK  ");
				break;
			      case 13:
				printf("LOPROC");
				break;
			      case 15:
				printf("HIPROC");
				break;
			      default:
				printf("UKN   ");
				break;
			    }
		printf("\t");

		//affichage de l'index
		switch(symtab[j].st_shndx){
			      case SHN_UNDEF:
				printf("UND");
				break;
			      case SHN_ABS:
				printf("ABS");
				break;
			      default:
				printf("%3d",symtab[j].st_shndx);
				break;
		}

		//on cherche la section de table des noms de symboles (celle de type 3)
		for(i=0;i<header.e_shnum;i++){
			if(i != header.e_shstrndx && shtab[i].sh_type == 3){
				addrStrName = shtab[i].sh_offset;
			}
		}

		//on suppose le nom d'un symbole inferieur a 75 char
		nameString = malloc(sizeof(char)*75);
		//position en debut de nom du symbole
		addrStrName = addrStrName+symtab[j].st_name;
		i = 0;
			//recuperation du symbole
		    while(fileBytes[addrStrName] != '\0'){
			nameString[i] = fileBytes[addrStrName];
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


