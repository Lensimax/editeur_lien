#include "elfsection.h"
#include "elfheader.h"
#include "filereader.h"
#include "sectionfus.h"



int sectfusion( Elf32_Ehdr *header1, Elf32_Shdr * shtab1,const char *filePath1,   Elf32_Ehdr *header2, Elf32_Shdr * shtab2,const char *filePath2, sect_tab * tab){

	unsigned char * file1 = readFileBytes(filePath1);
	unsigned char * file2 = readFileBytes(filePath2);
	char * name1;
	char * name2;
	free(tab);	//mise a zero de la table
	tab = malloc(sizeof(sect_tab)); 
	int cpt = 0;
	int appartient;
	int j =0;

	for (int i = 0; i < header1->e_shnum; i++){
		if (shtab1[i].sh_type == SHT_PROGBITS){		//si c'est un progbits (on pourrait stoquer toutes les sections non... mais dans ce cas faut mettre type dans la structure
			appartient=0;
			name1 = nom_section(*header1, shtab1,i ,file1);
			for (j = 0; j < header2->e_shnum; j++){		//on pourrait mettre while pour raccourcir la boucle surtout que y'a qu'une section progbit avec le meme nom dans le 2
				if (shtab2[j].sh_type == SHT_PROGBITS){
					name2 = nom_section(*header2, shtab2, j ,file2);
					if (strcmp(name1,name2)==0){
						appartient=1;			//on a trouvé deux noms correspondants
						if (cpt != 0)
							tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
						strcpy(tab[cpt].name,name1);
						tab[cpt].num = i;
						tab[cpt].sect = malloc(sizeof(char)*(shtab1[i].sh_size+shtab2[j].sh_size));
						strncpy ((char*)tab[cpt].sect,(char*)(file1+shtab1[i].sh_offset), shtab1[i].sh_size);
						strncpy ((char*)(tab[cpt].sect+shtab1[i].sh_size),(char*)(file2+shtab2[j].sh_offset), shtab2[j].sh_size);
						tab[cpt].fichier=0;
						tab[cpt].numsection=i;
						cpt++;
					}
					free(name2);
				}
			}
			if (!appartient){			//si on a pas trouvé de nom correspondant
				if (cpt != 0)
					tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
				strcpy(tab[cpt].name,name1);
				tab[cpt].num = i;
				tab[cpt].sect = malloc(sizeof(char)*(shtab1[i].sh_size));
				strncpy ((char*)tab[cpt].sect,(char*)(file1+shtab1[i].sh_offset), shtab1[i].sh_size);
				tab[cpt].fichier=0;
				tab[cpt].numsection=i;
				cpt++;
			
			}
		}
		free(name1);
		

	}
	//copie des sections de type progbit du deuxieme fichier qui n'ont pas le meme nom que celles du premier
	int num = header1->e_shnum;
	for (int i=0; i<header2->e_shnum; i++) {
		appartient = 0;
		name1 = nom_section(*header2, shtab2, i ,file2); 
		if (shtab2[i].sh_type == SHT_PROGBITS) {
			j=0;
			while((j<cpt)&&(!appartient)){
				if (strcmp(name1, tab[j].name) == 0){
					appartient = 1;
				}
				j++;
			}
			if (!appartient) {
				if (cpt != 0)
					tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
				strcpy(tab[cpt].name,name1);
				tab[cpt].num = num;
				num++;
				tab[cpt].sect = malloc(sizeof(char)*(shtab2[i].sh_size));
				strncpy ((char*)tab[cpt].sect,(char*)(file2+shtab2[i].sh_offset), shtab2[i].sh_size);
				tab[cpt].fichier=1;
				tab[cpt].numsection=i;
				cpt++;
			}
		}
		free(name1);
	}
	return cpt;

}



