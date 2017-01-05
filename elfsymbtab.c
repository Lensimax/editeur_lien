#include "elfsymbtab.h"





int getIndSectionSymtab(Elf32_Ehdr header,Elf32_Shdr* shtab) {
	int i;
	for(i=0;i<header.e_shnum;i++){
		if (shtab[i].sh_type == 2) {
			return i;
		}
	}
	return 0;
}


int readSymbtab(Elf32_Ehdr header, Elf32_Shdr * shtab, Elf32_Sym * symtab ,char * filePath, int indice_symtab){

int j;
FILE *f;


f = fopen(filePath, "r");

if(f != NULL){
	
	fseek(f, shtab[indice_symtab].sh_offset, SEEK_SET);
	
	for (j=0; j<shtab[indice_symtab].sh_size/shtab[indice_symtab].sh_entsize; j++){

		fread(&symtab[j], shtab[indice_symtab].sh_entsize, 1, f);

	}

	fclose(f);
	
	if((header.e_ident[EI_DATA] == 1 && is_big_endian()) || ((header.e_ident[EI_DATA] == 2) && !is_big_endian())) {


		for (j=0; j<shtab[indice_symtab].sh_size/shtab[indice_symtab].sh_entsize; j++){

			symtab[j].st_name = reverse_4(symtab[j].st_name);
			symtab[j].st_value = reverse_4(symtab[j].st_value);
			symtab[j].st_size = reverse_4(symtab[j].st_size);
			symtab[j].st_shndx = reverse_2(symtab[j].st_shndx);
						
			
		}

		
	}

} else {
	printf("Probleme ouverture fichier(table symbole)\n");
	return 0;
}


	return 1;
}



void aff_Symtable(Elf32_Shdr * shtab, Elf32_Ehdr header, char * filePath, Elf32_Sym * symtab, int indice_symtab){

unsigned char* fileBytes = readFileBytes(filePath);
char * nameString;
int j, bind, type, i,addrStrName;
int numSymb = 0;
printf("\n");
printf("  Num:    Valeur Tail   Type     Lien   Ndx Nom\n");

for (j=0; j<shtab[indice_symtab].sh_size/shtab[indice_symtab].sh_entsize; j++){

printf("   %2d:",numSymb);
numSymb++;

printf("  %08x",symtab[j].st_value);

printf("   %2d",symtab[j].st_size);

printf("   ");

bind = ELF32_ST_BIND(symtab[j].st_info);
type = ELF32_ST_TYPE(symtab[j].st_info);

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


for(i=0;i<header.e_shnum;i++){
	if(i != header.e_shstrndx && shtab[i].sh_type == 3){
		addrStrName = shtab[i].sh_offset;
	}
}


nameString = malloc(sizeof(char)*75);
addrStrName = addrStrName+symtab[j].st_name;
i = 0;
    while(fileBytes[addrStrName] != '\0'){
        nameString[i] = fileBytes[addrStrName];
        addrStrName++;
        i++;
    }

nameString[i] = 0;

printf(" %s",nameString);

printf("\n");

}

printf("\n");
}


