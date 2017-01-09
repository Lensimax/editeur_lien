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

void affichebin1(unsigned char n)
{
	unsigned char bit = 0 ;
	unsigned char mask = 1 ;
	for (int i = 0 ; i < 8 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
}

void affichebin2(Elf32_Word n)
{
	Elf32_Word bit = 0 ;
	Elf32_Word mask = 1 ;
	for (int i = 0 ; i < 16 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
}

void affichebin4(Elf32_Half n)
{
	Elf32_Half bit = 0 ;
	Elf32_Half mask = 1 ;
	for (int i = 0 ; i < 32 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
}




void fuuuuusion(Elf32_Ehdr * header, sect_tab * tab, int nbtab,char *filePath1, char *filePath2){

FILE *file1=fopen(filePath1, "r");
FILE *file2=fopen(filePath2, "r");		
char *text1;
char *text2;

affichebin1(header->e_ident[EI_MAG0]);
affichebin1(header->e_ident[EI_MAG1]);
affichebin1(header->e_ident[EI_MAG2]);
affichebin1(header->e_ident[EI_MAG3]);
affichebin1(header->e_ident[EI_CLASS]);
affichebin1(header->e_ident[EI_DATA]);
affichebin1(header->e_ident[EI_VERSION]);
affichebin1(header->e_ident[EI_PAD]);
affichebin1(header->e_ident[EI_NIDENT]);
affichebin2(header->e_type);
affichebin2(header->e_machine);
affichebin4(header->e_version);
affichebin4(header->e_entry);
affichebin4(header->e_phoff);
affichebin4(header->e_shoff);
affichebin4(header->e_flags);
affichebin2(header->e_ehsize);
affichebin2(header->e_phentsize);
affichebin2(header->e_phnum);
affichebin2(header->e_shentsize);
affichebin2(header->e_shnum);
affichebin2(header->e_shstrndx);
for (int i=0; i<nbtab;i++){

	realloc(text1, (sect_tab[i].size1)*sizeof(char))
	fseek(file1,sect_tab[i].offset1,SEEK_SET)
	fread(text1, 1, sect_tab[i].size1 , file1);	

	realloc(text2, (sect_tab[i].size2)*sizeof(char))
	fseek(file2,sect_tab[i].offset2,SEEK_SET)
	fread(text2, 1, sect_tab[i].size2 , file2);

	for (int i=0; i<sect_tab[i].size1; i++){
		affichebin1(text1[i]);
	}
	for (int i=0; i<sect_tab[i].size2; i++){
		affichebin1(text2[i]);
	}

}


}
