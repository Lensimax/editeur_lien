



void sectfusion( Elf32_Ehdr *header1, Elf32_Shdr * shtab1, char *filePath1,   Elf32_Ehdr *header2, Elf32_Shdr * shtab2, char *filePath2, sect_tab * tab){

tab = malloc(sizeof(sect_tab)); 
int cpt = 0;
int appartient;

for (int i = 0; i < header1->e_shnum; i++){
	if (shtab1[i].sh_type == SHT_PROGBITS){
		name1 = nom_section(header1, shtab1,i ,filePath1);
		for (int j = 0; j < header2->e_shnum, j++){
			if (shtab2[j].sh_type == SHT_PROGBITS){
				name2 = nom_section(header2, shtab2, j ,filePath2);
				if (strcmp(name1,name2)==0){
					if (cpt != 0)
						tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
					strcpy(tab[cpt].name,name1);
					tab[cpt].num = i;
					tab[cpt].sect = malloc(sizeof(char)*(shtab1[i].sh_size+shtab2[j].sh_size));
					strncpy (tab[cpt].sect, file1+shtab1[i].sh_offset], shtab1[i].sh_size);
					strncpy (tab[cpt].sect+shtab1[i].sh_size, file2+shtab2[j].sh_offset, shtab2[j].sh_size);
					cpt++;
				}
			}
		}
	}

}
for (int i=0; i<header1->e_shnum; i++) {
	appartient = 0;
	if (shtab1[i].sh_type == SHT_PROGBITS) {
		for (int j = 0; j<cpt; j++)
			name1 = nom_section(header1, shtab1,i ,filePath1); 
			if (strcmp(name1, tab[j].name) == 0)
				appartient = 1;
		if (!appartient) {
			if (cpt != 0)
				tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
			strcpy(tab[cpt].name,name1);
			tab[cpt].num = i;
			tab[cpt].sect = malloc(sizeof(char)*(shtab1[i].sh_size));
			strncpy (tab[cpt].sect, file1+shtab1[i].sh_offset, shtab1[i].sh_size);
			cpt++;
		}
	}
}
for (int i=0; i<header2->e_shnum; i++) {
	appartient = 0;
	if (shtab2[i].sh_type == SHT_PROGBITS) {
		for (int j = 0; j<cpt; j++)
			name1 = nom_section(header2, shtab2,i ,filePath2); 
			if (strcmp(name1, tab[j].name) == 0)
				appartient = 1;
		if (!appartient) {
			if (cpt != 0)
				tab = realloc(tab, sizeof(tab)+sizeof(sect_tab));
			strcpy(tab[cpt].name,name1);
			tab[cpt].num = header1->e_shnum;
			header1->e_shnum++;
			tab[cpt].sect = malloc(sizeof(char)*(shtab2[i].sh_size));
			strncpy (tab[cpt].sect, file2+shtab2[i].sh_offset, shtab2[i].sh_size);
			cpt++;
		}
	}
}

}



