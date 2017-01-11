#include "filewriter.h"



int Write_file(ELF_STRUCT file_struct, FILE *f){


	fseek(f, 0, SEEK_SET);

	fwrite(file_struct.header, file_struct.header->e_ehsize, 1, f);
	fwrite(file_struct.shtab, sizeof(Elf32_Shdr)*file_struct.header->e_shnum, 1, f);
	//fwrite(file_struct.symtab->, sizeof(Elf32_Sym)*->e_shnum, 1, f);

	for(int i=0; i<file_struct.header->e_shnum;i++){
		printf("Section %d\n", i);
	}

	// ecriture du header
	//fwrite(src,file2.header->e_ehsize,1,f);

	return 1;

}