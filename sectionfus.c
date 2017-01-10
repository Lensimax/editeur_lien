#include "elfsection.h"
#include "elfheader.h"
#include "filereader.h"
#include "sectionfus.h"


int sectfusion( ELF_STRUCT file1, ELF_STRUCT file2, ELF_STRUCT fileres, sect_tab * tab){

	/*file1.fileBytes  =  readFileBytes(file1.file_name);
	file2.fileBytes  =  readFileBytes(file2.file_name);*/
	char * name1;
	char * name2;
	int cpt  =  0;
	int appartient;
	int j  = 0;
	int place = 0;
	int length1  = file1.header->e_shnum;
	int length2  = file2.header->e_shnum;
	
	
	for (int i  =  0; i < length1; i++){

		if(cpt == 0){place  =  file1.shtab[i].sh_offset;}
		
		name1  =  nom_section(file1,i);
		strcpy(tab[cpt].name,name1);
		if (file1.shtab[i].sh_type  ==  SHT_PROGBITS){		//si c'est un progbits (on pourrait stoquer toutes les sections non... mais dans ce cas faut mettre type dans la structure
			appartient = 0;
			for (j  =  0; j < length2; j++){		//on pourrait mettre while pour raccourcir la boucle surtout que y'a qu'une section progbit avec le meme nom dans le 2
				if (file2.shtab[j].sh_type  ==  SHT_PROGBITS){
					name2  =  nom_section(file2,j);
					if (strcmp(name1,name2) == 0){
						appartient = 1;			//on a trouvé deux noms correspondants
						if (cpt !=  0){
							tab  =  realloc(tab,sizeof(sect_tab)*cpt);
						}
						tab[cpt].offset1 = file1.shtab[i].sh_offset;
						tab[cpt].size1 = file1.shtab[i].sh_size;
						tab[cpt].offset2 = file2.shtab[j].sh_offset;
						tab[cpt].size2 = file2.shtab[j].sh_size;

						fileres.shtab[cpt] = file1.shtab[i];	//on récupère les information du header du premier fichier puis on modifie
						fileres.shtab[cpt].sh_offset = place;
						fileres.shtab[cpt].sh_size = tab[cpt].size1+tab[cpt].size2;
						place = place+fileres.shtab[cpt].sh_size;

						cpt++;
						//printf("cpt %d fusion \n",cpt);
					}
						
				}
			}
			if (!appartient){			//si on a pas trouvé de nom correspondant
				if (cpt !=  0){
					tab  =  realloc(tab,sizeof(sect_tab)*cpt);
				}
				tab[cpt].offset1 = file1.shtab[i].sh_offset;
				tab[cpt].size1 = file1.shtab[i].sh_size;
				tab[cpt].offset2 = 0;
				tab[cpt].size2 = 0;

				fileres.shtab[cpt] = file1.shtab[i];	//on récupère les information du header du premier fichier puis on modifie
				fileres.shtab[cpt].sh_offset = place;
				fileres.shtab[cpt].sh_size = tab[cpt].size1;
				place = place+fileres.shtab[cpt].sh_size;

				cpt++;
				//printf("cpt %d pas fusion1 \n",cpt);
			
			}
		
		}else{
		if (cpt !=  0){
			tab  =  realloc(tab,sizeof(sect_tab)*cpt);
		}
		tab[cpt].offset1 = file1.shtab[i].sh_offset;
		tab[cpt].size1 = file1.shtab[i].sh_size;
		tab[cpt].offset2 = 0;
		tab[cpt].size2 = 0;

		fileres.shtab[cpt] = file1.shtab[i];	//on récupère les information du header du premier fichier puis on modifie
		fileres.shtab[cpt].sh_offset = place;
		fileres.shtab[cpt].sh_size = tab[cpt].size1;
		place = place+fileres.shtab[cpt].sh_size;

		cpt++;
		//printf("cpt %d file1 \n",cpt);
		
		}
		
		tab[cpt].newnum  =  cpt;
		tab[cpt].numorigin  =  cpt;
		tab[cpt].type = file1.shtab[i].sh_type;
	}free(name1);	free(name2);
	//copie des sections de type progbit du deuxieme fichier qui n'ont pas le meme nom que celles du premier
	for (int i = 0; i<length2; i++) {

		if(cpt == 0){place  =  file1.shtab[i].sh_offset;}
		
		char *name3  =  nom_section(file2,i); 
		strcpy(tab[cpt].name,name3);
		if (file2.shtab[i].sh_type  ==  SHT_PROGBITS) {
			j = 0;
			while((j<cpt)&&(!appartient)){
				if (strcmp(name1, tab[j].name)  ==  0){
					appartient  =  1;
				}
				j++;
			}
			if (!appartient) {
				if (cpt !=  0){
					tab  =  realloc(tab,sizeof(sect_tab)*cpt);
				}
				tab[cpt].offset1 = 0;
				tab[cpt].size1 = 0;
				tab[cpt].offset2 = file2.shtab[j].sh_offset;
				tab[cpt].size2 = file2.shtab[j].sh_size;

				fileres.shtab[cpt] = file2.shtab[i];	//on récupère les information du header du premier fichier puis on modifie
				fileres.shtab[cpt].sh_name =  file1.shtab[file1.header->e_shstrndx].sh_size+fileres.shtab[cpt].sh_name;
				fileres.shtab[cpt].sh_offset = place;
				fileres.shtab[cpt].sh_size = tab[cpt].size2;
				place = place+fileres.shtab[cpt].sh_size;

				cpt++;
				//printf("cpt %d fusion2 \n",cpt);
				
			}
			
		}else{
			if (cpt !=  0){
			tab  =  realloc(tab,sizeof(sect_tab)*cpt);
			}

			tab[cpt].offset1 = 0;
			tab[cpt].size1 = 0;
			tab[cpt].offset2 = file2.shtab[j].sh_offset;
			tab[cpt].size2 = file2.shtab[j].sh_size;

			fileres.shtab[cpt] = file2.shtab[i];	//on récupère les information du header du premier fichier puis on modifie
			fileres.shtab[cpt].sh_name =  file1.shtab[file1.header->e_shstrndx].sh_size+fileres.shtab[cpt].sh_name;
			fileres.shtab[cpt].sh_offset = place;
			fileres.shtab[cpt].sh_size = tab[cpt].size1;
			place = place+fileres.shtab[cpt].sh_size;

			cpt++;
			//printf("cpt %d file2 \n",cpt);

		}	
		free(name3);		
		tab[cpt].newnum  =  cpt;
		tab[cpt].numorigin  =  i;
		tab[cpt].type = file1.shtab[i].sh_type;
			
	}

	/*file1.header->e_shnum = length1;
	file2.header->e_shnum = length2;*/
	return cpt;

}

