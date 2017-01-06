#include "elfreloc.h"

const char* Reloc_Type[] = 
	{ 
		"R_ARM_NONE", "R_ARM_PC24", "R_ARM_ABS32", "R_ARM_REL32", "R_ARM_LDR_PC_G0", 
		"R_ARM_ABS16", "R_ARM_ABS12", "R_ARM_THM_ABS5", "R_ARM_ABS8", "R_ARM_SBREL32", 
		"R_ARM_THM_CALL", "R_ARM_THM_PC8", "R_ARM_BREL_ADJ", "R_ARM_TLS_DESC", "R_ARM_THM_SWI8", 
		"R_ARM_XPC25", "R_ARM_THM_XPC22", "R_ARM_TLS_DTPMOD32", "R_ARM_TLS_DTPOFF32", "R_ARM_TLS_TPOFF32",
		"R_ARM_COPY", "R_ARM_GLOB_DAT", "R_ARM_JUMP_SLOT", "R_ARM_RELATIVE", "R_ARM_GOTOFF32", 
		"R_ARM_BASE_PREL", "R_ARM_GOT_BREL", "R_ARM_PLT32", "R_ARM_CALL", "R_ARM_JUMP24",
		"R_ARM_THM_JUMP24", "R_ARM_BASE_ABS", "R_ARM_ALU_PCREL_7_0", "R_ARM_ALU_PCREL_15_8", "R_ARM_ALU_PCREL_23_15", 
		"R_ARM_LDR_SBREL_11_0_NC", "R_ARM_ALU_SBREL_19_12_NC", "R_ARM_ALU_SBREL_27_20_CK", "R_ARM_TARGET1", "R_ARM_SBREL31", 
		"R_ARM_V4BX", "R_ARM_TARGET2", "R_ARM_PREL31", "R_ARM_MOVW_ABS_NC", "R_ARM_MOVT_ABS", 
		"R_ARM_MOVW_PREL_NC", "R_ARM_MOVT_PREL", "R_ARM_THM_MOVW_ABS_NC", "R_ARM_THM_MOVT_ABS", "R_ARM_THM_MOVW_PREL_NC",
		"R_ARM_THM_MOVT_PREL", "", "", "", "", "" 
	};
	
int getIndSectionReltab(Elf32_Ehdr * header,Elf32_Shdr* shtab) {
	int i;
	for(i=0;i<header->e_shnum;i++){
		if (shtab[i].sh_type == 9) {
			return i;
		}
	}
	return 0;
}

int getIndSectionRelatab(Elf32_Ehdr * header,Elf32_Shdr* shtab) {
	int i;
	for(i=0;i<header->e_shnum;i++){
		if (shtab[i].sh_type == 4) {
			return i;
		}
	}
	return 0;
}

int readReloc(Elf32_Rel * Reltab, Elf32_Rela * Relatab, Elf32_Ehdr * header, Elf32_Shdr * Shtab, Elf32_Sym * Symtab, char * filePath, int Indice_Reltab, int Indice_Relatab, int isVerbose) {
  
  
	unsigned char* fileBytes = readFileBytes(filePath);
	int ind_name;
	char name[256];
	//int compt = 0;
	int j, k;
	FILE *f;
  
	// PARTIE REL
	f = fopen(filePath, "r");
	if(f != NULL){
		fseek(f, Shtab[Indice_Reltab].sh_offset, SEEK_SET);
		
		for (j=0; j<Shtab[Indice_Reltab].sh_size/Shtab[Indice_Reltab].sh_entsize; j++){
			fread(&Reltab[j], sizeof(Elf32_Rel), 1, f);
		}		
		fclose(f);
		
		if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {
	
	
			for (j=0; j<Shtab[Indice_Reltab].sh_size/Shtab[Indice_Reltab].sh_entsize; j++){
				Reltab[j].r_offset = reverse_4(Reltab[j].r_offset);
				Reltab[j].r_info = reverse_4(Reltab[j].r_info);				
			}
		}
	} else {
		printf("Probleme ouverture fichier(table section)\n");
		return 0;
	}
	for (j=0; j<Shtab[Indice_Reltab].sh_size/Shtab[Indice_Reltab].sh_entsize; j++){				
		if(isVerbose){
			printf("[*] Offset : %x\n",Reltab[j].r_offset); // Sûrement faux
			printf("[*] Type : %s\n", Reloc_Type[ELF32_R_TYPE(Reltab[j].r_info)]);
			printf("[*] Symbol Index : %x\n", ELF32_R_SYM(Reltab[j].r_info));
		} 
	}
  
	// PARTIE RELA
	if ( (int) Shtab[Indice_Relatab].sh_entsize !=  0) {
		f = fopen(filePath, "r");
		if(f != NULL){
			fseek(f, Shtab[Indice_Relatab].sh_offset, SEEK_SET);
    
				for (j=0; j<Shtab[Indice_Relatab].sh_size/Shtab[Indice_Relatab].sh_entsize; j++){
					fread(&Relatab[j], sizeof(Elf32_Rela), 1, f);
				}		
				fclose(f);
  
				if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {
    
    
				for (j=0; j<Shtab[Indice_Relatab].sh_size/Shtab[Indice_Relatab].sh_entsize; j++){
					Relatab[j].r_offset = reverse_4(Relatab[j].r_offset);
					Relatab[j].r_info = reverse_4(Relatab[j].r_info);
					Relatab[j].r_addend = reverse_4(Relatab[j].r_addend);
				}
			}
		} else {
			printf("Probleme ouverture fichier(table section)\n");
			return 0;
		}
		for (j=0; j<Shtab[Indice_Relatab].sh_size/Shtab[Indice_Relatab].sh_entsize; j++){				
			if(isVerbose){
				printf("[*] Offset : %x\n",Reltab[j].r_offset); // Sûrement faux

				// Searching the name of the section
				ind_name = Shtab[header->e_shstrndx].sh_offset;
				int l = 0;
				ind_name =  ind_name + Reltab[j].r_info;
				while(fileBytes[ind_name] != '\0'){
					name[l] = fileBytes[ind_name];
					k++;
					ind_name++;
				}
				name[l]='\0';
				// Displaying the name
				printf("[*] Name of the section : %s\n", name);
				printf("[*] Addend : %d\n", Relatab[j].r_addend);
			} 
		}
	}
return 0;
}
