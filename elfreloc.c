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
	
int IsIndSectionReltab(Elf32_Ehdr * header,Elf32_Shdr* shtab, int i) {
	return shtab[i].sh_type == SHT_REL;
}

int IsIndSectionRelatab(Elf32_Ehdr * header,Elf32_Shdr* shtab, int i) {
	return shtab[i].sh_type == SHT_RELA;
}

int nbIndSectionReltab(Elf32_Ehdr * header, Elf32_Shdr * Shtab) {
	int sum = 0;
	for(int i=0;i<header->e_shnum;i++){
		if (Shtab[i].sh_type == SHT_REL) {
			sum++;
		}
	}
	return sum;
}

int nbIndSectionRelatab(Elf32_Ehdr * header, Elf32_Shdr * Shtab) {
	int sum = 0;
	for(int i=0;i<header->e_shnum;i++){
		if (Shtab[i].sh_type == SHT_RELA) {
			sum++;
		}
	}
	return sum;
}

int readReloc(Elf32_Rel ** Reltab, Elf32_Ehdr * header, Elf32_Shdr * Shtab, Elf32_Sym * Symtab, char * filePath) {
  
  

	int j, n;
	FILE *f;
  
	// PARTIE REL

	/* c'est un peu porc */


	///// A CHANGER /////

	n = 0;
	for (int i=0; i<header->e_shnum; i++) {
          if (IsIndSectionReltab(header, Shtab, i)) {
			f = fopen(filePath, "r");
			if(f != NULL){
				fseek(f, Shtab[i].sh_offset, SEEK_SET);
				Reltab[n] = malloc(sizeof(Elf32_Rel)*(Shtab[i].sh_size/Shtab[i].sh_entsize));
				for (j=0; j<Shtab[i].sh_size/Shtab[i].sh_entsize; j++){
					fread(&Reltab[n][j], sizeof(Elf32_Rel), 1, f);
				}		
				fclose(f);
				
				if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {
			
			
					for (j=0; j<Shtab[i].sh_size/Shtab[i].sh_entsize; j++){
						Reltab[n][j].r_offset = reverse_4(Reltab[n][j].r_offset);
						Reltab[n][j].r_info = reverse_4(Reltab[n][j].r_info);				
					}
				}
			} else {
				printf("Probleme ouverture fichier(table reloc)\n");
				return 0;
			}			

			n++;
		}
	}
  
	
	return 1;
}

void aff_Reloc(ELF_STRUCT file){
	char *name;

	for (int i=0; i<file.header->e_shnum; i++) {

		name = nom_section(*file.header, file.shtab, i, file.file_name);

		printf("Section de réadressage %d : %s\n",i, name);
		
		printf("[*] Offset : %x\n",file.Reltab[i].r_offset); // Sûrement faux
		printf("[*] Type : %s\n", Reloc_Type[ELF32_R_TYPE(file.Reltab[i].r_info)]);
		printf("[*] Symbol Index : %x\n", ELF32_R_SYM(file.Reltab[i].r_info));
	}
}
