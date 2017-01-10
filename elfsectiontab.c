#include "elfsectiontab.h"

int readSectTab(ELF_STRUCT file){
 
	int j;
	FILE *f;

	//ouverture du fichier
	f = fopen(file.file_name, "r");
	
	//si l'ouverture a reussi
	if(f != NULL){
		//on se place en debut de table des sections
		fseek(f, file.header->e_shoff, SEEK_SET);
	
		//pour toutes les sections
		for (j=0; j<file.header->e_shnum; j++){
			//on rempli le shtab avec la section correpondante
			fread(&file.shtab[j], sizeof(Elf32_Shdr), 1, f);
		}	
		//fermeture du fichier	
	
		//inversion des octets si on a un problème de boutisme pour charque section
		if((file.header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((file.header->e_ident[EI_DATA] == 2) && !is_big_endian())) {


			for (j=0; j<file.header->e_shnum; j++){

				file.shtab[j].sh_name = reverse_4(file.shtab[j].sh_name);
				file.shtab[j].sh_type = reverse_4(file.shtab[j].sh_type);
				file.shtab[j].sh_flags = reverse_4(file.shtab[j].sh_flags);
				file.shtab[j].sh_addr = reverse_4(file.shtab[j].sh_addr);
				file.shtab[j].sh_offset = reverse_4(file.shtab[j].sh_offset);
				file.shtab[j].sh_size = reverse_4(file.shtab[j].sh_size);
				file.shtab[j].sh_link = reverse_4(file.shtab[j].sh_link);
				file.shtab[j].sh_info = reverse_4(file.shtab[j].sh_info);
				file.shtab[j].sh_addralign = reverse_4(file.shtab[j].sh_addralign);
				file.shtab[j].sh_entsize = reverse_4(file.shtab[j].sh_entsize);
			
			}

		
		}

	//si l'ouverture a echoue
	} else {
		fclose(f);
		//affichage message d'erreur
		printf("Probleme ouverture fichier(table section)\n");
		return 0;
	}

	fclose(f);
	return 1;
}



/////// NOM DES TYPES

char * nom_type(int i){

	//recherche du type et retour de son nom correspondant
	switch (i) {
		case SHT_NULL:		 	return "NULL";
		case SHT_PROGBITS:		return "PROGBITS";
		case SHT_SYMTAB:		return "SYMTAB";
		case SHT_STRTAB:		return "STRTAB";
		case SHT_RELA:			return "RELA";
		case SHT_HASH:			return "HASH";
		case SHT_DYNAMIC:		return "DYNAMIC";
		case SHT_NOTE:			return "NOTE";
		case SHT_NOBITS:		return "NOBITS";
		case SHT_REL:			return "REL";
		case SHT_SHLIB:			return "SHLIB";
		case SHT_DYNSYM:		return "DYNSYM";
		case SHT_INIT_ARRAY:	return "INIT_ARRAY";
		case SHT_FINI_ARRAY:	return "FINI_ARRAY";
		case SHT_PREINIT_ARRAY:	return "PREINIT_ARRAY";
		case SHT_GROUP:			return "GROUP";
		case SHT_SYMTAB_SHNDX:	return "SYMTAB SECTION INDICIES";
		case SHT_GNU_verdef:	return "VERDEF";
		case SHT_GNU_verneed:	return "VERNEED";
		case SHT_GNU_versym:	return "VERSYM";
		case 0x6ffffff0:		return "VERSYM";
		case 0x6ffffffc:		return "VERDEF";
		case 0x7ffffffd:		return "AUXILIARY";
		case 0x7fffffff:		return "FILTER";
		case 0x70000001:		return "ARM_EXITDX";
		case 0x70000002:		return "ARM_PREEMPTMAP";
		case 0x70000003:		return "ARM_ATTRIBUTES";
		case 0x70000004:		return "ARM_DEBUGOVERLAY";
		case 0x70000005:		return "ARM_OVERLAYSECTION";
		case SHT_GNU_LIBLIST: return "GNU_LIBLIST";
		
		default: return "";
		}
}

/////// NOM DES FLAGS

char* nom_flags(unsigned int flags) {

	//le nom d'un flag a une taille inferieure a 9 char
	char* val = malloc(sizeof(char)*9);

	//on met tous les char su string a zero (nb: on pourrait peut etre utiliser un calloc non..)
	int p;
	for(p=0;p<9;p++) {
			val[p]='\0';
	}
	//initialisation des compteurs
	int r;
	int i = 1;
	int b = 0;
	//tant qu'on a pas ecrit tout le flag
	while (flags != 0)
	{
		//on recupere le bit de poids faible et on ecrit le flag dans b
		r = flags%2;
		flags = flags/2;
		b = b+r*i;
		i = i*10;
	}



	//on rempli val (= le nom du flag) en fonction de la valeur de b 
	if (b & 00000001)
	{
		val[0]='W';
		if (b & 00000010)
		{
		val[1]='A';
			if (b & 00000100)
			{
			val[2]='X';
			}
		}
		else if (b & 00000100)
			{
			val[1]='X';
			}
	}

	else if (b & 00000010)
	{
		val[0]='A';
		if (b & 00000100)
		{
		val[1]='X';
		}
	}

	else if (b & 00000100) {
		val[0]='X';
		}

	if(b!=0 && val[0]=='\0') {
	val = "U";

	}

	return val;


}


///////AFFICHAGE

void aff_Sheader(ELF_STRUCT file){

//initialisation des compteurs
int i, k;
//initialisation du string qui contiendra le nom de section qu'on suppose inferieur a 50 char
char * name;
name = malloc(sizeof(char)*50);
int ind_name;
//initialisation du tableau de char avec le contenu de filePath (cf filereader.h)

printf("\nLecture des headers de sections : \n\n");
//affichage des entete de colonne du tableau 
printf("  [Nr] Nom\t\t        Type\t         Adr    \tDecala.\tTaille\tES\tFan\tLN\tInf\tAl\n");

//pour chaque section
for(i=0;i<file.header->e_shnum;i++){

	// recherche du nom d ela section
		//placement en debut de table des strings
		ind_name = file.shtab[file.header->e_shstrndx].sh_offset;
		k = 0;
		//placement en debut de nom de section
		ind_name =  ind_name + file.shtab[i].sh_name;
		
		//recuperation du nom de la section
		while(file.fileBytes[ind_name] != '\0'){
			name[k] = file.fileBytes[ind_name];
			k++;
			ind_name++;
		}
		//ajout de la marque de fin 
		name[k]='\0';

	//affichage des informations de chaque sections
	printf("  [%2d] %-25s%-17s%08d\t%06x\t%06x\t%02x\t%-1.04s\t%d\t%d\t%d\n",i,name,nom_type(file.shtab[i].sh_type),file.shtab[i].sh_addr,file.shtab[i].sh_offset,file.shtab[i].sh_size,file.shtab[i].sh_entsize,nom_flags(file.shtab[i].sh_flags),file.shtab[i].sh_link,file.shtab[i].sh_info,file.shtab[i].sh_addralign);

}

printf (("\nClé des fanions:\t W (écriture), A (allocation), X (exécution), U (Valeur Inconnue)\n\n"));
//liberation du nom
free(name);

}



