#include "fusrel.h"

void correction_num_symb_reloc(Elf32_Rel * rel){
	if(file_final.symtab[ELF32_R_SYM(rel->r_info)].old_num != file_final.symtab[ELF32_R_SYM(rel->r_info)].new_num) {
		rel->r_info = ELF32_R_INFO(file_final.symtab[ELF32_R_SYM(rel->r_info)].new_num, ELF32_R_TYPE(rel->r_info));
	}
}

int relfus(ELF_STRUCT file_1, ELF_STRUCT file_2, ELF_STRUCT * file_final){

	int compteur_section_rel_final = 0;
	int compteur_rel_par_section = 0;
	int a_trouve_rel_meme_nom;

	/////PARCOURS 1ERE TABLE DE RELOC

	for (int i=0; i<file_1.header->e_shnum; i++) {
		if (IsIndSectionReltab(file_1.header, file_1.shtab, i)) {
			a_trouve_rel_meme_nom = 0;

			for(int j=0; j<file_2.header->e_shnum; j++) {
				if (IsIndSectionReltab(file_2.header, file_2.shtab, j)) {
					
					if(!strcmp(nom_section(file_1.file,i),nom_section(file_2.file,j))) {
						
						for(int x=0;x<nbIndSectionRelTab(file_1);x++){
							if(file_1.tabrel[x].indice_section == i) {

								for(int n=0; n<file_1.shtab[i].sh_size/file_1.shtab[i].sh_entsize; n++) {
									file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section] = file_1.tabrel[x].reltab[n];
									correction_num_symb_reloc(&file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section]);
									compteur_rel_par_section++;
								}
							}
						}

						for(int x=0;x<nbIndSectionRelTab(file_2);x++){
							if(file_2.tabrel[x].indice_section == j) {

								for(int n=0; n<file_2.shtab[j].sh_size/file_2.shtab[j].sh_entsize; n++) {
									file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section] = file_2.tabrel[x].reltab[n];
									correction_num_symb_reloc(&file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section]);
									compteur_rel_par_section++;
								}
							}
						}
					a_trouve_rel_meme_nom = 1;
					compteur_rel_par_section = 0;
					////////////////////////////// TROUVER UN MOYEN DE REMPLIR INDICE_SECTION DANS TABREL_FINAL
					compteur_section_rel_final++;
					}
				}
			}
			
			if(!a_trouve_rel_meme_nom) {
				for(int x=0;x<nbIndSectionRelTab(file_1);x++){
					if(file_1.tabrel[x].indice_section == i) {
						for(int n=0; n<file_1.shtab[i].sh_size/file_1.shtab[i].sh_entsize; n++) {
							file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section] = file_1.tabrel[x].reltab[n];
							correction_num_symb_reloc(&file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section]);
							compteur_rel_par_section++;
						}
					}
				}
				compteur_section_rel_final++;
			}

		}
	}

	/////PARCOURS 2EME TABLE DE RELOC

	for (int i=0; i<file_2.header->e_shnum; i++) {
		if (IsIndSectionReltab(file_2.header, file_2.shtab, i)) {
			a_trouve_rel_meme_nom = 0;

			for(int j=0; j<file_1.header->e_shnum; j++) {
				if (IsIndSectionReltab(file_1.header, file_1.shtab, j)) {
					
					if(!strcmp(nom_section(file_2.file,i),nom_section(file_1.file,j))) {
						a_trouve_rel_meme_nom = 1;
					}
				}
			}
			
			if(!a_trouve_rel_meme_nom) {
				for(int x=0;x<nbIndSectionRelTab(file_2);x++){
					if(file_2.tabrel[x].indice_section == i) {
						for(int n=0; n<file_2.shtab[i].sh_size/file_2.shtab[i].sh_entsize; n++) {
							file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section] = file_2.tabrel[x].reltab[n];
							correction_num_symb_reloc(&file_final->tabrel[compteur_section_rel_final].reltab[compteur_rel_par_section]);
							compteur_rel_par_section++;
						}
					}
				}
				compteur_section_rel_final++;
			}
		}
	}

	

}
