#include "symbolfus.h"

// FONCTIONS AUXILLIAIRES !!!!!!

void change_num_after_fusion(sect_tab * sect_fus, STRUCT_SYM * symbol, int nb_sect_after_fusion){

	for(int i = 0; i<nb_sect_after_fusion;i++) {
		if(sect_fus[i].numorigin == symbol->symbole.st_shndx) {
			if(sect_fus[i].numorigin != sect_fus[i].newnum) {
				symbol->symbole.st_shndx=sect_fus[i].newnum;
				if(sect_fus[i].fusion == 1) {
				symbol->symbole.st_value+=sect_fus[i].size1;
				}
			}
		}
	}
}

void ajout_symbole_symtable_finale(int * compteur_symtab, STRUCT_SYM * symtab_final, Elf32_Sym symbol) {

	if (*compteur_symtab != 0){
		symtab_final = realloc(symtab_final,sizeof(*symtab_final)+sizeof(Elf32_Sym)+4*(sizeof(int)));
	}
	symtab_final[*compteur_symtab].symbole=symbol;

}





//CORPS

int symbolfus(ELF_STRUCT file_1, ELF_STRUCT file_2, ELF_STRUCT * file_final, sect_tab * sect_fus, int nb_sect_after_fusion){ /////// malloc du symtab_final à faire dans le main (malloc de 1)


	int compteur_symtab_final = 0;
	int addrStrName_1_stable;
	int addrStrName_2_stable;
	char* nameString_1;
	char* nameString_2;
	int addrStrName_1_var;
	int addrStrName_2_var;
	int indice_string_table_1 = 0;
	int j, compteur_locaux_fichier = 0;
	int boolean, indice_symtab_1, indice_symtab_2;
	int p1=0; int p2=0;
	

	for(int i=0;i<file_1.header->e_shnum;i++){
		if(i != file_1.header->e_shstrndx && file_1.shtab[i].sh_type == 3){
			addrStrName_1_stable = file_1.shtab[i].sh_offset;
			indice_string_table_1 = i;				
		}
	}

	for(int i=0;i<file_2.header->e_shnum;i++){
		if(i != file_2.header->e_shstrndx && file_2.shtab[i].sh_type == 3){
			addrStrName_2_stable = file_2.shtab[i].sh_offset;					
		}
	}


	indice_symtab_1 = getIndSectionSymtab(file_1.header,file_1.shtab);
	indice_symtab_2 = getIndSectionSymtab(file_2.header,file_2.shtab);

///////////////////////////////////PARCOURS DE LA 1ERE TABLE DE SYMBOLES
	while(!ELF32_ST_BIND(file_1.symtab[p1].symbole.st_info) && p1 < (file_1.shtab[indice_symtab_1].sh_size/file_1.shtab[indice_symtab_1].sh_entsize)) {

		ajout_symbole_symtable_finale(&compteur_symtab_final, file_final->symtab, file_1.symtab[p1].symbole);
		file_final->symtab[compteur_symtab_final].old_num = p1;
		file_final->symtab[compteur_symtab_final].new_num = compteur_symtab_final;
		p1++;
		compteur_locaux_fichier++;
		compteur_symtab_final++;
		
	}

	while(!ELF32_ST_BIND(file_2.symtab[p2].symbole.st_info) && p2 < (file_2.shtab[indice_symtab_2].sh_size/file_2.shtab[indice_symtab_2].sh_entsize)) {

		ajout_symbole_symtable_finale(&compteur_symtab_final, file_final->symtab, file_2.symtab[p2].symbole);
		
		change_num_after_fusion(sect_fus, &file_final->symtab[compteur_symtab_final], nb_sect_after_fusion);
		file_final->symtab[compteur_symtab_final].old_num = p2;
		file_final->symtab[compteur_symtab_final].new_num = compteur_symtab_final;
		file_final->symtab[compteur_symtab_final].symbole.st_name += 	file_1.shtab[indice_string_table_1].sh_size;
		p2++;
		compteur_locaux_fichier++;
		compteur_symtab_final++;

	}

	for (int k=p1;k<file_1.shtab[indice_symtab_1].sh_size/file_1.shtab[indice_symtab_1].sh_entsize;k++) {
		boolean = 0;
			
			nameString_1 = malloc(sizeof(char)*75);
			//position en debut de nom du symbole
			addrStrName_1_var = addrStrName_1_stable+file_1.symtab[k].symbole.st_name;
			j = 0;
				//recuperation du symbole
				while(file_1.fileBytes[addrStrName_1_var] != '\0'){
				nameString_1[j] = file_1.fileBytes[addrStrName_1_var];
				addrStrName_1_var++;
				j++;
				}
			//ajout de la marque de fin
			nameString_1[j] = 0;
			
			for (int l=0;l<file_2.shtab[indice_symtab_2].sh_size/file_2.shtab[indice_symtab_2].sh_entsize;l++) {

				if(ELF32_ST_BIND(file_2.symtab[l].symbole.st_info) != 0) {

				nameString_2 = malloc(sizeof(char)*75);
				//position en debut de nom du symbole
				addrStrName_2_var = addrStrName_2_stable+file_2.symtab[l].symbole.st_name;
				j = 0;
					//recuperation du symbole
					while(file_2.fileBytes[addrStrName_2_var] != '\0'){
					nameString_2[j] = file_2.fileBytes[addrStrName_2_var];
					addrStrName_2_var++;
					j++;
					}
				//ajout de la marque de fin
				nameString_2[j] = 0;
				
				if(strcmp(nameString_1,nameString_2) == 0) {
					boolean = 1;
					if(file_2.symtab[l].symbole.st_shndx != SHN_UNDEF && file_1.symtab[k].symbole.st_shndx != SHN_UNDEF) {
						printf("ERREUR 2 SYMBOLES DEFINIS DE MEME NOMS");
						return -1;

					} else if((file_2.symtab[l].symbole.st_shndx == SHN_UNDEF && file_1.symtab[k].symbole.st_shndx != SHN_UNDEF) || (file_1.symtab[k].symbole.st_shndx == SHN_UNDEF && file_2.symtab[l].symbole.st_shndx == SHN_UNDEF)) {
						ajout_symbole_symtable_finale(&compteur_symtab_final, file_final->symtab, file_1.symtab[k].symbole);
						file_final->symtab[compteur_symtab_final].old_num = 0;
						file_final->symtab[compteur_symtab_final].fusion_num_f1 = k;
						file_final->symtab[compteur_symtab_final].fusion_num_f2 = l;
						file_final->symtab[compteur_symtab_final].new_num = compteur_symtab_final;
						compteur_symtab_final++;
					}
				}
				free(nameString_2);
			}
			}
			if(!boolean){																							//////SI LES 2 SYMBOLES N'ONT PAS LE MÊME NOM
				ajout_symbole_symtable_finale(&compteur_symtab_final, file_final->symtab, file_1.symtab[k].symbole);
				file_final->symtab[compteur_symtab_final].old_num = k;
				file_final->symtab[compteur_symtab_final].new_num = compteur_symtab_final;
				compteur_symtab_final++;
			}

		free(nameString_1);
		
	
	}

///////////////////////////////////PARCOURS DE LA 2EME TABLE DE SYMBOLES

	for (int k=p2;k<file_2.shtab[indice_symtab_2].sh_size/file_2.shtab[indice_symtab_2].sh_entsize;k++) {
		boolean = 0;
		

			nameString_2 = malloc(sizeof(char)*75);
			//position en debut de nom du symbole
			addrStrName_2_var = addrStrName_2_stable+file_2.symtab[k].symbole.st_name;
			j = 0;
				//recuperation du symbole
				while(file_2.fileBytes[addrStrName_2_var] != '\0'){
				nameString_2[j] = file_2.fileBytes[addrStrName_2_var];
				addrStrName_2_var++;
				j++;
				}
			//ajout de la marque de fin
			nameString_2[j] = 0;
			
			for (int l=0;l<file_1.shtab[indice_symtab_1].sh_size/file_1.shtab[indice_symtab_1].sh_entsize;l++) {

				if(ELF32_ST_BIND(file_1.symtab[l].symbole.st_info) != 0) {

				nameString_1 = malloc(sizeof(char)*75);
				//position en debut de nom du symbole
				addrStrName_1_var = addrStrName_1_stable+file_1.symtab[l].symbole.st_name;
				j = 0;
					//recuperation du symbole
					while(file_1.fileBytes[addrStrName_1_var] != '\0'){
					nameString_1[j] = file_1.fileBytes[addrStrName_1_var];
					addrStrName_1_var++;
					j++;
					}
				//ajout de la marque de fin
				nameString_1[j] = 0;
				
				if(strcmp(nameString_2,nameString_1) == 0) {
					boolean = 1;
					if(file_1.symtab[l].symbole.st_shndx != SHN_UNDEF && file_2.symtab[k].symbole.st_shndx != SHN_UNDEF) {
						printf("ERREUR 2 SYMBOLES DEFINIS DE MEME NOMS");
						return -1;
					} else if(file_1.symtab[l].symbole.st_shndx == SHN_UNDEF && file_2.symtab[k].symbole.st_shndx != SHN_UNDEF) { // *var_1.st_shndx == SHN_UNDEF && *var_2.st_shndx != SHN_UNDEF

						ajout_symbole_symtable_finale(&compteur_symtab_final, file_final->symtab, file_2.symtab[k].symbole);
						file_final->symtab[compteur_symtab_final].old_num = 0;
						file_final->symtab[compteur_symtab_final].fusion_num_f1 = l;
						file_final->symtab[compteur_symtab_final].fusion_num_f2 = k;
						file_final->symtab[compteur_symtab_final].new_num = compteur_symtab_final;
						change_num_after_fusion(sect_fus, &file_final->symtab[compteur_symtab_final], nb_sect_after_fusion);
						file_final->symtab[compteur_symtab_final].symbole.st_name += 	file_1.shtab[indice_string_table_1].sh_size;
						compteur_symtab_final++;
						
					}
				}
				free(nameString_1);
			}
			}
		
			if(!boolean){																					//////SI LES 2 SYMBOLES N'ONT PAS LE MÊME NOM

				ajout_symbole_symtable_finale(&compteur_symtab_final, file_final->symtab, file_2.symtab[k].symbole);
				file_final->symtab[compteur_symtab_final].new_num = compteur_symtab_final;
				file_final->symtab[compteur_symtab_final].old_num = k;
				change_num_after_fusion(sect_fus, &file_final->symtab[compteur_symtab_final], nb_sect_after_fusion);
				file_final->symtab[compteur_symtab_final].symbole.st_name += 	file_1.shtab[indice_string_table_1].sh_size;
				compteur_symtab_final++;

			}

		free(nameString_2);
		
	
	}


	file_final->shtab[getIndSectionSymtab(file_final->header,file_final->shtab)].sh_size = compteur_symtab_final*file_final->shtab[getIndSectionSymtab(file_final->header,file_final->shtab)].sh_entsize;
	for(int i = getIndSectionSymtab(file_final->header,file_final->shtab); i<file_final->header->e_shnum;i++){
		file_final->shtab[i].sh_offset -= ((file_1.shtab[getIndSectionSymtab(file_1.header,file_1.shtab)].sh_size + file_2.shtab[getIndSectionSymtab(file_2.header,file_2.shtab)].sh_size) - compteur_symtab_final);
	}


//return compteur_locaux_fichier;
return 1;


}

