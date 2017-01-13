#ifndef __ELF_STRUCT_H__
#define __ELF_STRUCT_H__

#include <elf.h>
#include <stdio.h>

typedef struct STRUCT_REL {

	Elf32_Rel *reltab;
	int indice_section;

} STRUCT_REL;

typedef struct STRUCT_SYM {

	Elf32_Sym symbole;
	int old_num;
	int fusion_num_f1;
	int fusion_num_f2;
	int new_num;

} STRUCT_SYM;

typedef struct ELF_STRUCT {

	FILE* file; // Nom du fichier, init en 1er
	Elf32_Ehdr *header; //Elf header, init en 2e
	Elf32_Shdr *shtab; // 4e
	STRUCT_SYM *symtab; // 7e
	STRUCT_REL * tabrel; // 8e
	

	int indice_symtab;

	
	char file_name[256];
	unsigned char* fileBytes;

} ELF_STRUCT;

typedef struct {
	char name[256];
	int offset1, size1, offset2, size2;
	int newnum, numorigin;
	int type, fusion, offset;
} sect_tab;


#endif 
