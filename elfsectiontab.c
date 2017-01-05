#include "elfsectiontab.h"

int readSectTab(Elf32_Shdr * shtab, Elf32_Ehdr * header, char * filePath){
 
int j;
FILE *f;


f = fopen(filePath, "r");

if(f != NULL){
	fseek(f, header->e_shoff, SEEK_SET);
	
	for (j=0; j<header->e_shnum; j++){
		fread(&shtab[j], sizeof(Elf32_Shdr), 1, f);
	}		
	fclose(f);
	
	if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {


		for (j=0; j<header->e_shnum; j++){

			shtab[j].sh_name = reverse_4(shtab[j].sh_name);
			shtab[j].sh_type = reverse_4(shtab[j].sh_type);
			shtab[j].sh_flags = reverse_4(shtab[j].sh_flags);
			shtab[j].sh_addr = reverse_4(shtab[j].sh_addr);
			shtab[j].sh_offset = reverse_4(shtab[j].sh_offset);
			shtab[j].sh_size = reverse_4(shtab[j].sh_size);
			shtab[j].sh_link = reverse_4(shtab[j].sh_link);
			shtab[j].sh_info = reverse_4(shtab[j].sh_info);
			shtab[j].sh_addralign = reverse_4(shtab[j].sh_addralign);
			shtab[j].sh_entsize = reverse_4(shtab[j].sh_entsize);
			
		}

		
	}


} else {
	printf("Probleme ouverture fichier(table section)\n");
	return 0;
}


	return 1;
}



/////// NOM DES TYPES

char * nom_type(int i){
	char* nom;
	nom = malloc(sizeof(char)*30);

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
	return nom;
}

/////// NOM DES FLAGS

char* nom_flags(unsigned int flags) {

	char* val = malloc(sizeof(char)*9);

	int p;
	for(p=0;p<9;p++) {
			val[p]='\0';
	}
	int r;
	int i = 1;
	int b = 0;
	while (flags != 0)
	{
		r = flags%2;
        flags = flags/2;
        b = b+r*i;
        i = i*10;
	}



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

void aff_Sheader(Elf32_Shdr * shtab, Elf32_Ehdr * header, char * filePath){

int i, k;
char * name;
int ind_name;
unsigned char* fileBytes = readFileBytes(filePath);
name = malloc(sizeof(char)*50);

printf("\nLecture des headers de sections : \n\n");

printf("  [Nr]  Nom\t\t        Type\t         Adr    \tDecala.\tTaille\tES\tFan\tLN\tInf\tAl\n");

for(i=0;i<header->e_shnum;i++){

// Searching the name of the section
		ind_name = shtab[header->e_shstrndx].sh_offset;
		k = 0;
		
		ind_name =  ind_name + shtab[i].sh_name;
		
		while(fileBytes[ind_name] != '\0'){
			name[k] = fileBytes[ind_name];
			k++;
			ind_name++;
		}
		name[k]='\0';


	printf("  [%2d] %-25s%-17s%08d\t%06x\t%06x\t%02x\t%-1.04s\t%d\t%d\t%d\n",i,name,nom_type(shtab[i].sh_type),shtab[i].sh_addr,shtab[i].sh_offset,shtab[i].sh_size,shtab[i].sh_entsize,nom_flags(shtab[i].sh_flags),shtab[i].sh_link,shtab[i].sh_info,shtab[i].sh_addralign);

}

printf (("\nClé des fanions:\t W (écriture), A (allocation), X (exécution), U (Valeur Inconnue)\n\n"));
free(name);

}



