#include "elfreloc.h"

int readReloc(Elf32_Rel * Reltab, Elf32_Ehdr header, Elf32_Shdr * Shtab, Elf32_Sym * Symtab, char * filePath, int isVerbose) {

	unsigned char* fileBytes = readFileBytes(filePath);
	int ind_name;
	char name[256];
	Elf32_Reloc Reloc;
	Elf32_Rel * Reltab = malloc(sizeof(Elf32_Rel));
	Els32_Rela * Relatab = malloc(sizeof(Elf32_Rela));
	//int compt = 0;
	int j;
	FILE *f;


	f = fopen(filePath, "r");

	if(f != NULL){
		fseek(f, header->e_shoff, SEEK_SET);
		
		for (j=0; j<header->e_shentsize; j++){
			fread(&Reltab[j], sizeof(Elf32_Shdr), 1, f);
		}		
		fclose(f);
		
		if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {
	
	
			for (j=0; j<header->e_shnum; j++){
	
				shtab[j].sh_name = reverse_4(Reltab[j].r_offset);
				shtab[j].sh_type = reverse_4(Reltab[j].r_info);
				
			}
		}
	} else {
		printf("Probleme ouverture fichier(table section)\n");
		return 0;
	}
	for (j = 0; j<header->e_shentsize; j++) {				
		if(isVerbose){
			printf("[*] Offset : %x\n",Reltab[compt].r_offset); // Sûrement faux
	
			// Searching the name of the section
			ind_name = Shtab[header.e_shstrndx].r_offset;
			int l = 0;
			ind_name =  ind_name + Reltab[compt].r_info;
			while(fileBytes[ind_name] != '\0'){
				name[l] = fileBytes[ind_name];
				k++;
				ind_name++;
			}
			name[l]='\0';
			// Displaying the name
			printf("[*] Name of the section : %s\n", name);
			//printf("[*] Addend : %ld\n", Relatab[compt].r_append);
	} 
	}
	}else{ printf("[E] Echec malloc dans la table des symboles \n");return NULL;}
}
