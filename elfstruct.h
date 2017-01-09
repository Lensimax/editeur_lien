#ifndef __ELF_STRUCT_H__
#define __ELF_STRUCT_H__

#include <elf.h>
#include <stdio.h>

typedef struct ELF_STRUCT {

	FILE* file; // Nom du fichier, init en 1er
	Elf32_Ehdr *header; //Elf header, init en 2e
	Elf32_Shdr *shtab; // 4e
	Elf32_Sym *symtab; // 7e
	Elf32_Rela *Relatab; // 8e
	Elf32_Rel *Reltab; // 8e
	unsigned char **sections_content; // malloc( sizeof(char *) * elf_struct->elf_header->e_shnum ), 5e
	char *section_names;
	int nb_sections; // elf_struct->elf_header->e_shnum;, init en 3e
	int str_table_idx; // 6e
	int symb_table_idx; // 6e

	int indice_symtab;

	
	char file_name[256];
	unsigned char* fileBytes;

} ELF_STRUCT;

#endif 
