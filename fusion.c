#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "elfheader.h"
#include "elfsectiontab.h"
#include "elfsection.h"
#include "elfsymbtab.h"
#include "elfreloc.h"
#include "fusion.h"




//affichage de la fusion
void fusion(ELF_STRUCT file1, ELF_STRUCT file2 ,ELF_STRUCT * res, sect_tab * tab, int nbtab){
	
	FILE* fileres= fopen(res->file_name,"w");


	////////affichage du header////////
	fwrite(res->header,1,sizeof(Elf32_Ehdr),fileres);
	

	///////affichage des section headers///////
	//for (int i=0; i<nbtab;i++){
		fwrite(&res->shtab,1,sizeof(Elf32_Shdr)*nbtab,fileres);
	//}

	///////affichage des sections///////
	for (int i=0; i<nbtab;i++){

		if(tab[i].size1!=0){
			//printf("(tab[i].offset1) %d %d \n",(tab[i].offset1), i);
			fwrite(file1.fileBytes+(tab[i].offset1),1,tab[i].size1,fileres);
		}
		if(tab[i].size2!=0){
			fwrite(file2.fileBytes+(tab[i].offset2),1,tab[i].size2,fileres);
		}
	}
	
	res->file=fileres;
	fclose(fileres);
}
