#include "elfreloc.h"

Elf32_Reloc * readReloc(Elf32_Ehdr header, Elf32_Shdr * Shtab, Elf32_Sym * Symtab, char * filePath, int isVerbose) {

	unsigned char* fileBytes = readFileBytes(filePath);
	int ind_name;
	char name[256];
	Elf32_Reloc Reloc;
	Elf32_Rel * Reltab = malloc(sizeof(Elf32_Rel));
	Els32_Rela * Relatab = malloc(sizeof(Elf32_Rela));
	//int compt = 0;
	if (Reltab != NULL){	//Si l'allocation reussi
	
		for (int j=0; j<header.e_shnum; j++){ // for each section
		
			if (( Shtab[j].sh_type == 9 )){	//if Rel tab
			
				int i = Shtab[j].sh_offset;		 // debut de la table de symboles
				int k = 0; 
				
				while (k < header.e_shentsize){	// while not end of section
					if (compt != 0){		//
						Reltab = (Elf32_Rel * ) realloc(Reltab, sizeof(Reltab)+sizeof(Elf32_Rel));
						if (Reltab == NULL){printf("[E] Echec realloc dans la table des realocations \n");return NULL;}
					}
					Reltab[compt].r_offset = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
					i=i+4;
					Reltab[compt].r_info = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
					i=i+4;
					k=k+8;
					
					if(isVerbose){
						printf("[*] Offset : %x\n",Reltab[compt].st_offset); // Sûrement faux
						
						// Searching the name of the section
						ind_name = Shtab[header.e_shstrndx].sh_offset;
						int l = 0;
						ind_name =  ind_name + Reltab[compt].r_info;
						while(fileBytes[ind_name] != '\0'){
						name[l] = fileBytes[ind_name];
						k++;
						ind_name++;
						}
						name[l]='\0';
						// Displaying the name
						printf("[*] Name of the section : %s\n", name);
					
					} 
					compt++; 
				}	
			}
		}
	}else{ printf("[E] Echec malloc dans la table des symboles \n");return NULL;}
	
	if (Relatab != NULL){	//Si l'allocation reussi
	
		for (int j=0; j<header.e_shnum; j++){ // for each section
		
			if (( Shtab[j].sh_type == 4 )){	//if Rela tab
			
				int i = Shtab[j].sh_offset;		 // debut de la table de symboles
				int k = 0; 
				
				while (k < header.e_shentsize){	// while not end of section
					if (compt != 0){		//
						Relatab = (Elf32_Rela * ) realloc(Relatab, sizeof(Relatab)+sizeof(Elf32_Rela));
						if (Reltab == NULL){printf("[E] Echec realloc dans la table des realocations \n");return NULL;}
					}
					Relatab[compt].r_offset = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
					i=i+4;
					Relatab[compt].r_info = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
					i=i+4;
					Relatab[compt].r_addend = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
					i=i+4;
					k=k+12;
					
					if(isVerbose){
					
						printf("[*] Offset : %x\n",Relatab[compt].st_offset); // Sûrement faux
						
						// Searching the name of the section
						ind_name = Shtab[header.e_shstrndx].sh_offset;
						int l = 0;
						ind_name =  ind_name + Relatab[compt].r_info;
						while(fileBytes[ind_name] != '\0'){
						name[l] = fileBytes[ind_name];
						k++;
						ind_name++;
						}
						name[l]='\0';
						// Displaying the name
						printf("[*] Name of the section : %s\n", name);
						
						printf("[*] Addend : %ld\n", Relatab[compt].r_append);
					
					} 
					compt++; 
				}	
			}
		}
	}else{ printf("[E] Echec malloc dans la table des symboles \n");return NULL;}
	
	if(isVerbose){ printf("[*] Nombre symboles : %d\n",compt);}
	Reloc.Reltab = Reltab;
	Reloc.Relatab = Relatab;
	return Reloc;
}
