#include "elfsection.h"
#include "elfheader.h"
#include "filereader.h"
#include "sectionfus.h"

void fnc_fus(ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT * fileres, sect_tab * tab, int indice_s1, int indice_s2, int indice_sfinal, int * place){

	tab[indice_sfinal].offset1 = file1.shtab[indice_s1].sh_offset;
	tab[indice_sfinal].size1 = file1.shtab[indice_s1].sh_size;
	tab[indice_sfinal].offset2 = file2.shtab[indice_s2].sh_offset;
	tab[indice_sfinal].size2 = file2.shtab[indice_s2].sh_size;
	tab[indice_sfinal].numorigin=indice_s2;
	tab[indice_sfinal].newnum=indice_sfinal;
	tab[indice_sfinal].offset= *place;
	tab[indice_sfinal].fusion=1;
	
	*place = *place+tab[indice_sfinal].size1+tab[indice_sfinal].size2;

	fileres->shtab[indice_sfinal].sh_name=file1.shtab[indice_s1].sh_name;
	fileres->shtab[indice_sfinal].sh_type=file1.shtab[indice_s1].sh_type;
	fileres->shtab[indice_sfinal].sh_flags=file1.shtab[indice_s1].sh_flags;
	fileres->shtab[indice_sfinal].sh_addr=file1.shtab[indice_s1].sh_addr;
	fileres->shtab[indice_sfinal].sh_offset=tab[indice_sfinal].offset;
	fileres->shtab[indice_sfinal].sh_size=tab[indice_sfinal].size1+tab[indice_sfinal].size2;
	fileres->shtab[indice_sfinal].sh_link=file1.shtab[indice_s1].sh_link;
	fileres->shtab[indice_sfinal].sh_info=file1.shtab[indice_s1].sh_info;
	fileres->shtab[indice_sfinal].sh_addralign=file1.shtab[indice_s1].sh_addralign;
	fileres->shtab[indice_sfinal].sh_entsize=file1.shtab[indice_s1].sh_entsize;

}

void fnc_non_fus(ELF_STRUCT file1, ELF_STRUCT * fileres, sect_tab * tab, int indice_s1, int indice_sfinal, int * place){

	tab[indice_sfinal].offset1 = file1.shtab[indice_s1].sh_offset;
	tab[indice_sfinal].size1 = file1.shtab[indice_s1].sh_size;
	tab[indice_sfinal].offset2 = 0;
	tab[indice_sfinal].size2 = 0;
	tab[indice_sfinal].numorigin=indice_sfinal;
	tab[indice_sfinal].newnum=indice_sfinal;
	tab[indice_sfinal].fusion=0;


	tab[indice_sfinal].offset= *place;	
	*place= *place+tab[indice_sfinal].size1;
	if(indice_sfinal == 0){
		tab[indice_sfinal].offset=0;
	}

	fileres->shtab[indice_sfinal].sh_name=file1.shtab[indice_s1].sh_name;
	fileres->shtab[indice_sfinal].sh_type=file1.shtab[indice_s1].sh_type;
	fileres->shtab[indice_sfinal].sh_flags=file1.shtab[indice_s1].sh_flags;
	fileres->shtab[indice_sfinal].sh_addr=file1.shtab[indice_s1].sh_addr;
	fileres->shtab[indice_sfinal].sh_offset=tab[indice_sfinal].offset;
	fileres->shtab[indice_sfinal].sh_size=file1.shtab[indice_s1].sh_size;
	fileres->shtab[indice_sfinal].sh_link=file1.shtab[indice_s1].sh_link;
	fileres->shtab[indice_sfinal].sh_info=file1.shtab[indice_s1].sh_info;
	fileres->shtab[indice_sfinal].sh_addralign=file1.shtab[indice_s1].sh_addralign;
	fileres->shtab[indice_sfinal].sh_entsize=file1.shtab[indice_s1].sh_entsize;

}

void fnc_fus_2(ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT * fileres, sect_tab * tab, int indice_s1, int indice_s2, int indice_sfinal, int * place){
	tab[indice_sfinal].offset1 = file1.shtab[indice_s1].sh_offset;
	tab[indice_sfinal].size1 = file1.shtab[indice_s1].sh_size;
	tab[indice_sfinal].offset2 = 0;
	tab[indice_sfinal].size2 = 0;
	tab[indice_sfinal].numorigin=indice_s2;
	tab[indice_sfinal].newnum=indice_sfinal;
	tab[indice_sfinal].offset=*place;
	tab[indice_sfinal].fusion=0;

	*place = *place+tab[indice_sfinal].size2;
	
	fileres->shtab[indice_sfinal].sh_name=file2.shtab[indice_s2].sh_name+file1.shtab[file1.header->e_shstrndx].sh_size;
	fileres->shtab[indice_sfinal].sh_type=file2.shtab[indice_s2].sh_type;
	fileres->shtab[indice_sfinal].sh_flags=file2.shtab[indice_s2].sh_flags;
	fileres->shtab[indice_sfinal].sh_addr=file2.shtab[indice_s2].sh_addr;
	fileres->shtab[indice_sfinal].sh_offset=tab[indice_sfinal].offset;
	fileres->shtab[indice_sfinal].sh_size=file2.shtab[indice_s2].sh_size;
	fileres->shtab[indice_sfinal].sh_link=file2.shtab[indice_s2].sh_link;
	fileres->shtab[indice_sfinal].sh_info=file2.shtab[indice_s2].sh_info;
	fileres->shtab[indice_sfinal].sh_addralign=file2.shtab[indice_s2].sh_addralign;
	fileres->shtab[indice_sfinal].sh_entsize=file2.shtab[indice_s2].sh_entsize;
}

int sectfusion( ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT * fileres, sect_tab * tab){

	char * name1;
	char * name2;
	int cpt  =  0;
	int fusion = 0;
	int indice_strndx = 0;
	int j  = 0;
	int place = file1.header->e_ehsize; // à déterminer, offset du premier, taille de header etc....?
	//int length1  = file1.header->e_shnum;
	//int length2  = file2.header->e_shnum;
	



	for (int i  =  0; i < file1.header->e_shnum; i++){

		name1 = nom_section(file1,i);		//récupération du nom
	

		///// REALLOC

		if (cpt !=  0){
			tab  =  realloc(tab,sizeof(sect_tab)*(cpt+1));
			fileres->shtab = realloc(fileres->shtab, sizeof(Elf32_Shdr)*(cpt+1));
		}

		strcpy(tab[cpt].name,name1); // stockage dans la structure sect_tab

		tab[cpt].type = file1.shtab[i].sh_type; // stockage du type

	
		if (file1.shtab[i].sh_type  ==  SHT_REL){
			j=0;
			while ((j < file2.header->e_shnum)&&(!fusion)){
				if (file2.shtab[j].sh_type  ==  SHT_REL){
					name2  =  nom_section(file2,j);
					if (strcmp(name1,name2) == 0){
						fnc_fus(file1,file2,fileres,tab,i,j,cpt,&place);
						cpt++;
						fusion = 1;
					}
				}
				j++;
			}
			if(!fusion){
				fnc_non_fus(file1,fileres,tab,i,cpt,&place);
				cpt++;
			}
			fusion = 0;
		}
		else if (file1.shtab[i].sh_type  ==  SHT_STRTAB && i == file1.header->e_shstrndx){
			j=0;
			while ((j < file2.header->e_shnum)&&(!fusion)){
				if (file2.shtab[j].sh_type  ==  SHT_STRTAB && j == file2.header->e_shstrndx){
						fnc_fus(file1,file2,fileres,tab,i,j,cpt,&place);
						cpt++;
				}
				j++;
			}
		}

		else if(file1.shtab[i].sh_type  == SHT_STRTAB && i != file1.header->e_shstrndx){
			j=0;
			while ((j < file2.header->e_shnum)&&(!fusion)){
				if (file2.shtab[j].sh_type  ==  SHT_STRTAB && j != file2.header->e_shstrndx){
						fnc_fus(file1,file2,fileres,tab,i,j,cpt,&place);
						cpt++;
				}
				j++;
			}
		}
		else if(file1.shtab[i].sh_type  == SHT_SYMTAB){
			j=0;
			while ((j < file2.header->e_shnum)&&(!fusion)){
				if (file2.shtab[j].sh_type  ==  SHT_SYMTAB){
						fnc_fus(file1,file2,fileres,tab,i,j,cpt,&place);
						cpt++;
				}
				j++;
			}
		}

		else if (file1.shtab[i].sh_type  ==  SHT_PROGBITS){		
				j=0;
				while ((j < file2.header->e_shnum)&&(!fusion)){
					if (file2.shtab[j].sh_type  ==  SHT_PROGBITS){
						name2  =  nom_section(file2,j);
						if (strcmp(name1,name2) == 0){
							fnc_fus(file1,file2,fileres,tab,i,j,cpt,&place);
							cpt++;
							fusion = 1;
						}
					}
					j++;
				}
				if(!fusion){
					fnc_non_fus(file1,fileres,tab,i,cpt,&place);
					cpt++;
				}
				fusion = 0;		
		}

		else {
			fnc_non_fus(file1,fileres,tab,i,cpt,&place);
			cpt++;			
		}
	}

	////////2EME FICHIER

	for (int i  =  0; i < file2.header->e_shnum; i++){
		
		name2  =  nom_section(file2,i);
	
		if(file2.shtab[i].sh_type != SHT_STRTAB && file2.shtab[i].sh_type != SHT_SYMTAB) {
			while (j < file1.header->e_shnum){
					name1  =  nom_section(file1,j);
					if(strcmp(name1,name2)!=0) {
						if (cpt !=  0){
							tab  =  realloc(tab,sizeof(sect_tab)*(cpt+1));
							fileres->shtab = realloc(fileres->shtab, sizeof(Elf32_Shdr)*(cpt+1));
						}
						strcpy(tab[cpt].name,name2);		
						tab[cpt].type = file2.shtab[cpt].sh_type;
						fnc_fus_2(file1,file2,fileres,tab,j,i,cpt,&place);
						cpt++;
					}
			}
		}	
	}

//////HEADER
fileres->header = file1.header;
fileres->header->e_shoff = file1.header->e_ehsize;
fileres->header->e_shnum = cpt;
fileres->header->e_shstrndx = indice_strndx;
//////

return cpt;
}
