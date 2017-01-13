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

	FILE* file;
	Elf32_Ehdr *header; 
	Elf32_Shdr *shtab;
	STRUCT_SYM *symtab; 
	STRUCT_REL * tabrel; 
	

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
