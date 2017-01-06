#include "elfreloc.h"

int getIndSectionReltab(Elf32_Ehdr header,Elf32_Shdr* shtab) {
	int i;
	for(i=0;i<header.e_shnum;i++){
		if (shtab[i].sh_type == 4) {
			return i;
		}
	}
	return 0;
}

int getIndSectionRelatab(Elf32_Ehdr header,Elf32_Shdr* shtab) {
	int i;
	for(i=0;i<header.e_shnum;i++){
		if (shtab[i].sh_type == 4) {
			return i;
		}
	}
	return 0;
}

int readReloc(Elf32_Rel * Reltab, Elf32_Rela Relatab, Elf32_Ehdr header, Elf32_Shdr * Shtab, Elf32_Sym * Symtab, char * filePath, int isVerbose) {

	int Indice_Reltab = getIndSectionReltab(header, Shtab);
	int Indice_Relatab = getIndSectionRelatab(header, Shtab);
	unsigned char* fileBytes = readFileBytes(filePath);
	int ind_name;
	char name[256];
	//int compt = 0;
	int j;
	FILE *f;

	// PARTIE REL
	f = fopen(filePath, "r");

	if(f != NULL){
		fseek(f, shtab[indice_Reltab].sh_offset, SEEK_SET);
		
		for (j=0; j<shtab[indice_Reltab].sh_size/shtab[indice_Raltab].sh_entsize; j++){
			fread(&Reltab[j], sizeof(Elf32_Rel), 1, f);
		}		
		fclose(f);
		
		if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {
	
	
			for (j=0; j<shtab[indice_Reltab].sh_size/shtab[indice_Raltab].sh_entsize; j++){
	
				shtab[j].r_offset = reverse_4(Reltab[j].r_offset);
				shtab[j].r_info = reverse_4(Reltab[j].r_info);
				
			}
		}
	} else {
		printf("Probleme ouverture fichier(table section)\n");
		return 0;
	}
	for (j=0; j<shtab[indice_symtab].sh_size/shtab[indice_Raltab].sh_entsize; j++){				
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
	
	// PARTIE RELA
	f = fopen(filePath, "r");
	if(f != NULL){
		fseek(f, shtab[indice_Relatab].sh_offset, SEEK_SET);
		
		for (j=0; j<shtab[indice_Relatab].sh_size/shtab[indice_Ralatab].sh_entsize; j++){
			fread(&Relatab[j], sizeof(Elf32_Rela), 1, f);
		}		
		fclose(f);
		
		if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {
	
	
			for (j=0; j<shtab[indice_Relatab].sh_size/shtab[indice_Ralatab].sh_entsize; j++){
	
				Relatab[j].r_offset = reverse_4(Relatab[j].r_offset);
				Relatab[j].r_info = reverse_4(Relatab[j].r_info);
				Relatab[j].r_addend = reverse_4(Relatab[j].r_addend);
				
			}
		}
	} else {
		printf("Probleme ouverture fichier(table section)\n");
		return 0;
	}
	for (j=0; j<shtab[indice_symtab].sh_size/shtab[indice_Raltab].sh_entsize; j++){				
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
			printf("[*] Addend : %ld\n", Relatab[compt].r_append);
	} 
	}
	}else{ printf("[E] Echec malloc dans la table des symboles \n");return NULL;}
}
