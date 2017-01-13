
#include "fusion.h"




//affichage de la fusion
void fusion(ELF_STRUCT file1, ELF_STRUCT file2 ,ELF_STRUCT * res, sect_tab * tab, int nbtab){
	
	FILE* fileres= fopen(res->file_name,"w");


	////////affichage du header////////
	fwrite(res->header,1,sizeof(Elf32_Ehdr),fileres);
	

	///////affichage des section headers///////
	fwrite(&res->shtab,1,sizeof(Elf32_Shdr)*nbtab,fileres);
	

	///////affichage des sections///////
	for (int i=0; i<nbtab;i++){

		if (/*(res->shtab[i].sh_type!=SHT_REL)&&*/(res->shtab[i].sh_type!=SHT_SYMTAB)){
			if(tab[i].size1!=0){
				fwrite(file1.fileBytes+(tab[i].offset1),1,tab[i].size1,fileres);
			}
			if(tab[i].size2!=0){							///// EN COMMENTAIRE AU CAS OU LA FUSION DES TABLES DE REIMPLANTATION FONCTIONNENT /////
				fwrite(file2.fileBytes+(tab[i].offset2),1,tab[i].size2,fileres);
			}
		}/*else if(res->shtab[i].sh_type==SHT_REL){

			fwrite(res->tabrel,1,res->shtab[i].sh_size,fileres);

		}*/
		else if(tab[i].type==SHT_SYMTAB){

			fwrite(res->symtab,1,res->shtab[i].sh_size,fileres);
			
		}
	}
	
	res->file=fileres;
	fclose(fileres);
}
