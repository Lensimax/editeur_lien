#include "fill_struct.h"



#define DEBUG 1



int fill(ELF_STRUCT *file, char file_name[]){
	strcpy(file->file_name, file_name);
	file->fileBytes = readFileBytes(file->file_name);

	file->header = malloc(sizeof(Elf32_Ehdr));

	if(readHeader(*file)){
		if(DEBUG)
			printf("Lecture header done!\n"); // DEBUG

		file->shtab = malloc(sizeof(Elf32_Shdr)*file->header->e_shnum);

		if(readSectTab(*file)){
			if(DEBUG)
				printf("Lecture sections header done!\n"); // DEBUG

			file->indice_symtab = getIndSectionSymtab(file->header,file->shtab);
			file->symtab = malloc(sizeof(STRUCT_SYM)*(file->shtab[file->indice_symtab].sh_size/file->shtab[file->indice_symtab].sh_entsize));
			
			
			if(readSymbtab(*file)){
				if(DEBUG)
					printf("Lecture symbole tab done!\n"); // DEBUG

				file->tabrel = malloc(sizeof(STRUCT_REL)*(nbIndSectionReltab(*file)));

				if(readReloc(*file)){
					if(DEBUG){
						printf("Lecture reloc done!\n"); // DEBUG
						printf("Lecture fichier bonne\n");
					}

					return 1;

				} else {
					if(DEBUG)
						printf("[Error] Lecture Symbole tab\n"); // DEBUG
					return 0;
				}


			} else {
				if(DEBUG)
					printf("[Error] Lecture Symbole tab\n"); // DEBUG
				return 0;
			}

		} else {
			if(DEBUG)
				printf("[Error] Lecture SHTAB\n"); // DEBUG
			return 0;
		}

	} else {
		if(DEBUG)
			printf("[Error] Lecture HEADER\n"); // DEBUG
		return 0;
	}
}