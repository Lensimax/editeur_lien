#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <getopt.h>
#include <sys/stat.h>
#include <string.h>
#include "elfheader.h"
#include "elfsectiontab.h"
#include "elfsection.h"
#include "util.h"
#include "elfsymbtab.h"
#include "elfreloc.h"
#include "fusion.h"
//#include "sectionfus.h"
#include "filereader.h"


int main(int argc, char * argv[]){

	ELF_STRUCT file1;
	ELF_STRUCT file2;
	ELF_STRUCT res;	
	

	strcpy(file1.file_name,"ARM.o");
	strcpy(file2.file_name,"example2.o");

	file1.fileBytes = readFileBytes("ARM.o");
	file2.fileBytes = readFileBytes("example2.o");

	strcpy(res.file_name,"ARM.o");
	res.fileBytes = readFileBytes("ARM.o");
	
	
	
		


	res.shtab = malloc(sizeof(Elf32_Shdr));
	sect_tab * tab = malloc(sizeof(sect_tab));

	file1.header = malloc(sizeof(Elf32_Ehdr));
	file2.header = malloc(sizeof(Elf32_Ehdr));	
	res.header = malloc(sizeof(Elf32_Ehdr));

	
	
	if(readHeader(file1)&&readHeader(file2)){

	

	file1.shtab = malloc(sizeof(Elf32_Shdr)*file1.header->e_shnum);
	readSectTab(file1);
	file2.shtab = malloc(sizeof(Elf32_Shdr)*file2.header->e_shnum);
	readSectTab(file2);



	int nbtab = sectfusion( file1, file2, res , tab);
	
	aff_header(file1);
	aff_header(file2);
	file1.header->e_shnum = nbtab;
	
		
	//fusion( file1.header, res.shtab, tab, nbtab, file1.file_name,  file2.file_name);
	
	res.file=file1.file;
	res.header->e_shnum=nbtab;
	//aff_Sheader(res);
	
	}


}
