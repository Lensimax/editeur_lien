#include "fusrel.h"



void correction_num_symb_reloc(ELF_STRUCT * file_final, Elf32_Rel * rel){
	printf("%d",ELF32_R_SYM(rel->r_info));
	/*if(file_final->symtab[ELF32_R_SYM(rel.r_info)].old_num != file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num) {
		rel.r_info = ELF32_R_INFO(file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num, ELF32_R_TYPE(rel.r_info));
	}*/
}

/*void ajout_rel(ELF_STRUCT file_1, ELF_STRUCT * file_final, int compteur_section_rel_final, int * compteur_rel_par_section, int x, int n) {

printf(" %d \n",compteur_section_rel_final);
	
	file_final->tabrel[compteur_section_rel_final].reltab = realloc(&file_final->tabrel[compteur_section_rel_final].reltab, sizeof(Elf32_Rel)*(*compteur_rel_par_section+1));

	//file_final->tabrel[compteur_section_rel_final].reltab[*compteur_rel_par_section] = file_1.tabrel[x].reltab[n]; 
	//correction_num_symb_reloc(file_final,&file_final->tabrel[compteur_section_rel_final].reltab[*compteur_rel_par_section]);
	*compteur_rel_par_section = *compteur_rel_par_section + 1;

}*/

int relfus(ELF_STRUCT file_1, ELF_STRUCT file_2, ELF_STRUCT * file_final){

	int compteur_section_rel_final = 0;
	int compteur_rel_par_section = 0;
	int a_trouve_rel_meme_nom;
	Elf32_Rel rel;
	/////PARCOURS 1ERE TABLE DE RELOC

	for (int i=0; i<file_1.header->e_shnum; i++) {
	
		if (IsIndSectionReltab(file_1, i)) {
			a_trouve_rel_meme_nom = 0;
			file_final->tabrel = realloc(file_final->tabrel, sizeof(STRUCT_REL)*(compteur_section_rel_final+1));

			////// RECHERCHE D UNE SECTION DE MEME NOM ///
			for(int j=0; j<file_2.header->e_shnum; j++) {
				if (IsIndSectionReltab(file_2, j)) {


					//// ON A TROUVE LE MEME NOM DANS LE FICHIER 2
					if(!strcmp(nom_section(file_1,i),nom_section(file_2,j))) { /////FUSION A FAIRE


						//// RECHERCHE DANS LA TABLE DE RELOC
						for(int x=0;x<nbIndSectionReltab(file_1);x++){
							if(file_1.tabrel[x].indice_section == i) {

								for(int n=0; n<file_1.shtab[i].sh_size/file_1.shtab[i].sh_entsize; n++) { 
					
									file_final->tabrel[compteur_section_rel_final].reltab = realloc(&file_final->tabrel[compteur_section_rel_final].reltab, sizeof(Elf32_Rel)*(compteur_rel_par_section+1));
									file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section] = file_1.tabrel[x].reltab[n]; 
									rel = file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section];

									if(file_final->symtab[ELF32_R_SYM(rel.r_info)].old_num != file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num) {
										file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section].r_info = ELF32_R_INFO(file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num, ELF32_R_TYPE(rel.r_info));
									}

									//correction_num_symb_reloc(file_final,file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section]);


									compteur_rel_par_section = compteur_rel_par_section + 1;	
								}
							}
						}

						for(int x=0;x<nbIndSectionReltab(file_2);x++){
							if(file_2.tabrel[x].indice_section == j) {

								for(int n=0; n<file_2.shtab[j].sh_size/file_2.shtab[j].sh_entsize; n++) {

									file_final->tabrel[compteur_section_rel_final].reltab = realloc(&file_final->tabrel[compteur_section_rel_final].reltab, sizeof(Elf32_Rel)*(compteur_rel_par_section+1));
									file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section] = file_2.tabrel[x].reltab[n]; 
								
									rel = file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section];
									if(file_final->symtab[ELF32_R_SYM(rel.r_info)].old_num != file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num) {
										file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section].r_info = ELF32_R_INFO(file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num, ELF32_R_TYPE(rel.r_info));
									}

									//correction_num_symb_reloc(file_final,file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section]);

									compteur_rel_par_section = compteur_rel_par_section + 1;		
									file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section-1].r_offset+=file_1.shtab[i].sh_size;
								}
							}
						}
					a_trouve_rel_meme_nom = 1;
					compteur_rel_par_section = 0;
					compteur_section_rel_final++;
					//file_final->tabrel = realloc(file_final->tabrel, sizeof(STRUCT_REL)*(compteur_section_rel_final));
					} // ici
				}
			}






			
			if(!a_trouve_rel_meme_nom) {		/////PAS DE FUSION A FAIRE
				for(int x=0;x<nbIndSectionReltab(file_1);x++){
					if(file_1.tabrel[x].indice_section == i) {
						for(int n=0; n<file_1.shtab[i].sh_size/file_1.shtab[i].sh_entsize; n++) {


							
							file_final->tabrel[compteur_section_rel_final].reltab = realloc(&file_final->tabrel[compteur_section_rel_final].reltab, sizeof(Elf32_Rel)*(compteur_rel_par_section+1));

							file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section] = file_1.tabrel[x].reltab[n]; 
					
							rel = file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section];

							if(file_final->symtab[ELF32_R_SYM(rel.r_info)].old_num != file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num) {
									file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section].r_info = ELF32_R_INFO(file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num, ELF32_R_TYPE(rel.r_info));
							}

							//correction_num_symb_reloc(file_final,file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section]);
							compteur_rel_par_section = compteur_rel_par_section + 1;			
						}
					}
				}


				compteur_rel_par_section = 0;
				compteur_section_rel_final++;
				//file_final->tabrel = realloc(file_final->tabrel, sizeof(STRUCT_REL)*(compteur_section_rel_final));

			}

		}
	}

	/////PARCOURS 2EME TABLE DE RELOC

	/*for (int i=0; i<file_2.header->e_shnum; i++) {
		if (IsIndSectionReltab(file_2, i)) {
			a_trouve_rel_meme_nom = 0;
			file_final->tabrel = realloc(file_final->tabrel, sizeof(STRUCT_REL)*(compteur_section_rel_final+1));

			for(int j=0; j<file_1.header->e_shnum; j++) {
				if (IsIndSectionReltab(file_1, j)) {
					
					if(!strcmp(nom_section(file_2,i),nom_section(file_1,j))) {
						a_trouve_rel_meme_nom = 1;
					}
				}
			}
			
			if(!a_trouve_rel_meme_nom) {	/////PAS DE FUSION A FAIRE
				for(int x=0;x<nbIndSectionReltab(file_2);x++){
					if(file_2.tabrel[x].indice_section == i) {
						for(int n=0; n<file_2.shtab[i].sh_size/file_2.shtab[i].sh_entsize; n++) {
							file_final->tabrel[compteur_section_rel_final].reltab = realloc(&file_final->tabrel[compteur_section_rel_final].reltab, sizeof(Elf32_Rel)*(compteur_rel_par_section+1));
							file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section] = file_2.tabrel[x].reltab[n]; 


							rel = file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section];
							if(file_final->symtab[ELF32_R_SYM(rel.r_info)].old_num != file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num) {
									file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section].r_info = ELF32_R_INFO(file_final->symtab[ELF32_R_SYM(rel.r_info)].new_num, ELF32_R_TYPE(rel.r_info));
							}

							//correction_num_symb_reloc(file_final,file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section]);
							compteur_rel_par_section = compteur_rel_par_section + 1;		
						}
					}
				}
				compteur_section_rel_final++;
				compteur_rel_par_section = 0;
				//file_final->tabrel = realloc(file_final->tabrel, sizeof(STRUCT_REL)*(compteur_section_rel_final));
			}
		}
	}*/

	
return 0;
}
