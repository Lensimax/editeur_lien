#include "elfsection.h"
#include "elfheader.h"
#include "filereader.h"
#include "sectionfus2.h"



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
		name1 = nom_section(*header1, shtab1,i ,file1);
		strcpy(tab[cpt].name,name1);
		if (shtab1[i].sh_type == SHT_PROGBITS){		//si c'est un progbits (on pourrait stoquer toutes les sections non... mais dans ce cas faut mettre type dans la structure
			appartient=0;
			for (j = 0; j < header2->e_shnum; j++){		//on pourrait mettre while pour raccourcir la boucle surtout que y'a qu'une section progbit avec le meme nom dans le 2
				if (shtab2[j].sh_type == SHT_PROGBITS){
					name2 = nom_section(*header2, shtab2, j ,file2);
					if (strcmp(name1,name2)==0){
						appartient=1;			//on a trouvé deux noms correspondants
						if (cpt != 0)
							tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
						tab[cpt].offs1=shtab1[i].sh_offset;
						tab[cpt].size1=shtab1[i].sh_size;
						tab[cpt].offs2=shtab2[j].sh_offset;
						tab[cpt].size2=shtab2[j].sh_size;
						cpt++;
					}
					free(name2);
				}
			}
			if (!appartient){			//si on a pas trouvé de nom correspondant
				if (cpt != 0)
					tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
				tab[cpt].offs1=shtab1[i].sh_offset;
				tab[cpt].size1=shtab1[i].sh_size;
				tab[cpt].offs2=0;
				tab[cpt].size2=0;
				cpt++;
			
			}
		
		}else{
		tab[cpt].offs1=shtab1[i].sh_offset;
		tab[cpt].size1=shtab1[i].sh_size;
		tab[cpt].offs2=0;
		tab[cpt].size2=0;
		cpt++;
		}
		free(name1);
		tab[cpt].type=shtab1[i].sh_type;
	}
	//copie des sections de type progbit du deuxieme fichier qui n'ont pas le meme nom que celles du premier
	for (int i=0; i<header2->e_shnum; i++) {
		name1 = nom_section(*header2, shtab2, i ,file2); 
		strcpy(tab[cpt].name,name1);
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
				tab[cpt].offs1=0;
				tab[cpt].size1=0;
				tab[cpt].offs2=shtab2[j].sh_offset;
				tab[cpt].size2=shtab2[j].sh_size;
				cpt++;
			}
			
		}else{
			tab[cpt].offs1=0;
			tab[cpt].size1=0;
			tab[cpt].offs2=shtab2[j].sh_offset;
			tab[cpt].size2=shtab2[j].sh_size;
			cpt++;
		}
		free(name1);
		tab[cpt].newnum = cpt;
		tab[cpt].numorign = i;
		tab[cpt].type=shtab1[i].sh_type;
	}
	return cpt;

}


