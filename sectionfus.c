#include "elfsection.h"
#include "elfheader.h"
#include "filereader.h"
#include "sectionfus.h"


int sectfusion( Elf32_Ehdr *header1, Elf32_Shdr * shtab1,const char *filePath1,   Elf32_Ehdr *header2, Elf32_Shdr * shtab2,const char *filePath2, Elf32_Shdr * shres, sect_tab * tab){

	unsigned char * file1 = readFileBytes(filePath1);
	unsigned char * file2 = readFileBytes(filePath2);
	char * name1;
	char * name2;
	free(tab);	//mise a zero de la table
	tab = malloc(sizeof(sect_tab)); 
	free(shres);
	shres = malloc(sizeof(Elf32_Shdr)); 
	int cpt = 0;
	int appartient;
	int j =0;
	int place=0;

	for (int i = 0; i < header1->e_shnum; i++){

		if(cpt==0){place = shtab1[i].sh_offset;}
		
		name1 = nom_section(*header1, shtab1, i ,file1);
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

						tab[cpt].offset1=shtab1[i].sh_offset;
						tab[cpt].size1=shtab1[i].sh_size;
						tab[cpt].offset2=shtab2[j].sh_offset;
						tab[cpt].size2=shtab2[j].sh_size;

						shres[cpt]=shtab1[i];	//on récupère les information du header du premier fichier puis on modifie
						shres[cpt].sh_offset=place;
						shres[cpt].sh_size=tab[cpt].size1+tab[cpt].size2;
						place=place+shres[cpt].sh_size;

						cpt++;
					}
					free(name2);
				}
			}
			if (!appartient){			//si on a pas trouvé de nom correspondant
				if (cpt != 0)
					tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
				tab[cpt].offset1=shtab1[i].sh_offset;
				tab[cpt].size1=shtab1[i].sh_size;
				tab[cpt].offset2=0;
				tab[cpt].size2=0;

				shres[cpt]=shtab1[i];	//on récupère les information du header du premier fichier puis on modifie
				shres[cpt].sh_offset=place;
				shres[cpt].sh_size=tab[cpt].size1;
				place=place+shres[cpt].sh_size;

				cpt++;
			
			}
		
		}else{
		tab[cpt].offset1=shtab1[i].sh_offset;
		tab[cpt].size1=shtab1[i].sh_size;
		tab[cpt].offset2=0;
		tab[cpt].size2=0;

		shres[cpt]=shtab1[i];	//on récupère les information du header du premier fichier puis on modifie
		shres[cpt].sh_offset=place;
		shres[cpt].sh_size=tab[cpt].size1;
		place=place+shres[cpt].sh_size;

		cpt++;
		}
		free(name1);
		tab[cpt].newnum = cpt;
		tab[cpt].numorigin = cpt;
		tab[cpt].type=shtab1[i].sh_type;
	}
	//copie des sections de type progbit du deuxieme fichier qui n'ont pas le meme nom que celles du premier
	for (int i=0; i<header2->e_shnum; i++) {

		if(cpt==0){place = shtab1[i].sh_offset;}

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
				tab[cpt].offset1=0;
				tab[cpt].size1=0;
				tab[cpt].offset2=shtab2[j].sh_offset;
				tab[cpt].size2=shtab2[j].sh_size;

				shres[cpt]=shtab2[i];	//on récupère les information du header du premier fichier puis on modifie
//////////////////////////////////////////////ATTENTION, il faut aussi modifier le nom en ajoutant la taillle de la table des strings de 1 à l'index (pour le momen ton a que l'index)
				shres[cpt].sh_offset=place;
				shres[cpt].sh_size=tab[cpt].size2;
				place=place+shres[cpt].sh_size;

				cpt++;
			}
			
		}else{
			tab[cpt].offset1=0;
			tab[cpt].size1=0;
			tab[cpt].offset2=shtab2[j].sh_offset;
			tab[cpt].size2=shtab2[j].sh_size;

			shres[cpt]=shtab2[i];	//on récupère les information du header du premier fichier puis on modifie
//////////////////////////////////////////////ATTENTION, il faut aussi modifier le nom en ajoutant la taillle de la table des strings de 1 à l'index (pour le momen ton a que l'index)
			shres[cpt].sh_offset=place;
			shres[cpt].sh_size=tab[cpt].size1;
			place=place+shres[cpt].sh_size;

			cpt++;
		}
		free(name1);
		tab[cpt].newnum = cpt;
		tab[cpt].numorigin = i;
		tab[cpt].type=shtab1[i].sh_type;
	}
	return cpt;

}


