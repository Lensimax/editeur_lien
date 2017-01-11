#include "elfsection.h"
#include "elfheader.h"
#include "filereader.h"
#include "sectionfus.h"


int sectfusion( ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT fileres, sect_tab * tab){

	char * name1;
	char * name2;
	int cpt  =  0;
	int fusion = 0;
	int j  = 0;
	int place = sizeof(Elf32_Ehdr *); // à déterminer, offset du premier, taille de header etc....?
	//int length1  = file1.header->e_shnum;
	//int length2  = file2.header->e_shnum;

	for (int i  =  0; i < file1.header->e_shnum; i++){

		//if(cpt == 0){place  =  file1.shtab[i].sh_offset;}
		if (file1.shtab[i].sh_type  ==  SHT_REL){
		}
		else if (file1.shtab[i].sh_type  ==  SHT_STRTAB){
		}
		else if(file1.shtab[i].sh_type  !=  SHT_SYMTAB){
		}
		else{

			name1 = nom_section(file1,i)		//récupération du nom
			if (cpt !=  0){
				tab  =  realloc(tab,sizeof(sect_tab)*(cpt+1));
				fileres.shtab = realloc(fileres.shtab, sizeof(Elf32_Shdr)*(cpt+1));
			}
			strcpy(tab[cpt].name,name1);		
			tab[cpt].type = file1.shtab[cpt].sh_type;

			if (file1.shtab[i].sh_type  ==  SHT_PROGBITS){
			
				j=0;
				while ((j < file2.header->e_shnum)&&(!fusion)){	
					if (file2.shtab[j].sh_type  ==  SHT_PROGBITS){
						name2  =  nom_section(file2,j);
						if (strcmp(name1,name2) == 0){
							tab[cpt].offset1 = file1.shtab[i].sh_offset;
							tab[cpt].size1 = file1.shtab[i].sh_size;
							tab[cpt].offset2 = file2.shtab[j].sh_offset;
							tab[cpt].size2 = file2.shtab[j].sh_size;
							tab[cpt].numorigin=j;
							tab[cpt].newnum=cpt;
							tab[cpt].offset= place+tab[cpt].size1+tab[cpt].size2;
							tab[cpt].fusion=1;
							
							place = place+tab[cpt].size1+tab[cpt].size2;
						
							fileres.shtab[cpt].sh_name=file1.shtab[cpt].sh_name=;;
							fileres.shtab[cpt].sh_type=file1.shtab[cpt].sh_type;
							fileres.shtab[cpt].sh_flags=file1.shtab[cpt].sh_flags;
							fileres.shtab[cpt].sh_addr=file1.shtab[cpt].sh_addr;
							fileres.shtab[cpt].sh_offset=tab[cpt].offset;
							fileres.shtab[cpt].sh_size=tab[cpt].size1+tab[cpt].size2;
							fileres.shtab[cpt].sh_link=file1.shtab[cpt].sh_link;
							fileres.shtab[cpt].sh_info=file1.shtab[cpt].sh_info;
							fileres.shtab[cpt].sh_addraglign=file1.shtab[cpt].addralign;
							fileres.shtab[cpt].sh_entsize=file1.shtab[cpt].sh_entsize;
						

							fusion = 1;
						}
					}
					j++;
				}
			}
			if(!fusion){
				tab[cpt].offset1 = file1.shtab[i].sh_offset;
				tab[cpt].size1 = file1.shtab[i].sh_size;
				tab[cpt].offset2 = 0;
				tab[cpt].size2 = 0;
				tab[cpt].numorigin=cpt;
				tab[cpt].newnum=cpt;
				tab[cpt].offset= place+tab[cpt].size1;
				tab[cpt].fusion=0;
				
				place=place+tab[cpt].size1;
			
				fileres.shtab[cpt].sh_name=file1.shtab[cpt].sh_name=;;
				fileres.shtab[cpt].sh_type=file1.shtab[cpt].sh_type;
				fileres.shtab[cpt].sh_flags=file1.shtab[cpt].sh_flags;
				fileres.shtab[cpt].sh_addr=file1.shtab[cpt].sh_addr;
				fileres.shtab[cpt].sh_offset=tab[cpt].offset;
				fileres.shtab[cpt].sh_size=file1.shtab[cpt].sh_size;
				fileres.shtab[cpt].sh_link=file1.shtab[cpt].sh_link;
				fileres.shtab[cpt].sh_info=file1.shtab[cpt].sh_info;
				fileres.shtab[cpt].sh_addraglign=file1.shtab[cpt].addralign;
				fileres.shtab[cpt].sh_entsize=file1.shtab[cpt].sh_entsize;
				
				fusion =0;
			}

		}
	}
	for (int i  =  0; i < file2.header->e_shnum; i++){
		
		//if(cpt == 0){place  =  file1.shtab[i].sh_offset;}
		
		
		
		
		
		if (file2.shtab[i].sh_type  ==  SHT_PROGBITS){
			
				j=0;
				while ((j < file1.header->e_shnum)&&(!fusion)){	
					if (file1.shtab[j].sh_type  ==  SHT_PROGBITS){
						name2  =  nom_section(file1,j);
						if (strcmp(name1,name2) == 0){
							
							fusion = 1;
						}
					}
					j++;
				}
		}
		if((!fusion)&&(file2.shtab[i].sh_type  !=  SHT_REL)&&(file2.shtab[i].sh_type  !=  SHT_STRTAB)&&(file2.shtab[i].sh_type  !=  SHT_SYMTAB)){
		
			name1 = nom_section(file2,i)		//récupération du nom
			if (cpt !=  0){
				tab  =  realloc(tab,sizeof(sect_tab)*(cpt+1));
				fileres.shtab = realloc(fileres.shtab, sizeof(Elf32_Shdr)*(cpt+1));
			}
			strcpy(tab[cpt].name,name1);		
			tab[cpt].type = file2.shtab[j].sh_type;
		
		
			tab[cpt].offset1 = file1.shtab[i].sh_offset;
			tab[cpt].size1 = file1.shtab[i].sh_size;
			tab[cpt].offset2 = 0;
			tab[cpt].size2 = 0;
			tab[cpt].numorigin=j;
			tab[cpt].newnum=cpt;
			tab[cpt].offset= place+tab[cpt].size2;
			tab[cpt].fusion=0;
		
			place =place+tab[cpt].size2;;
			
			fileres.shtab[cpt].sh_name=file2.shtab[cpt].sh_name;
			fileres.shtab[cpt].sh_type=file2.shtab[cpt].sh_type;
			fileres.shtab[cpt].sh_flags=file2.shtab[cpt].sh_flags;
			fileres.shtab[cpt].sh_addr=file2.shtab[cpt].sh_addr;
			fileres.shtab[cpt].sh_offset=tab[cpt].offset;
			fileres.shtab[cpt].sh_size=file2.shtab[cpt].sh_size;
			fileres.shtab[cpt].sh_link=file2.shtab[cpt].sh_link;
			fileres.shtab[cpt].sh_info=file2.shtab[cpt].sh_info;
			fileres.shtab[cpt].sh_addraglign=file2.shtab[cpt].addralign;
			fileres.shtab[cpt].sh_entsize=file2.shtab[cpt].sh_entsize;
			
			fusion =0;
		}
	
}
	
