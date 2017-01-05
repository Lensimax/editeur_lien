#include "elfreloc.h"

Elf32_Reloc * readReloc(Elf32_Ehdr header, Elf32_Shdr * Shtab, char * filePath, int isVerbose) {

	unsigned char* fileBytes = readFileBytes(filePath);
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
						printf("[*] Offset : %x\n",Reltab[compt].st_offset); // Surement faux 
						/*printf("[*] Info : %x\n",Reltab[compt].st_offset);
						switch(ELF32_ST_TYPE(Symtab[compt].st_info)){
							case 2: case 1: printf("[*] Value: Adress : %x\n", Symtab[compt].st_value );break; 
							default: printf("[*] Value: Alignment/Offset : %d\n", Symtab[compt].st_value );break;
						}
						
						
						printf("[*] Size : %x\n", Symtab[compt].st_size);
						
						printf("[*] Info code : %x\n", Symtab[compt].st_info);
						
						switch (ELF32_ST_BIND(Symtab[compt].st_info)) {
							case 0: printf("[*] Info bind : STB_LOCAL \n"); break;
							case 1:printf("[*] Info bind : STB_GLOBAL\n"); break;
							case 2:printf("[*] Info bind : STB_WEAK\n"); break;
							case 13:printf("[*] Info bind : STB_LOPROC\n"); break;
							case 15:printf("[*] Info bind : STB_HIPROC\n"); break;
							default:printf("[*] Info bind :unknown \n"); break;
						}
							
						switch (ELF32_ST_TYPE(Symtab[compt].st_info)) {
							case 0: printf("[*] Info type : STT_NOTYPE \n"); break;
							case 1:printf("[*] Info type : STT_OBJECT \n"); break;
							case 2:printf("[*] Info type : STT_FUNC \n"); break;
							case 3:printf("[*] Info type : STT_SECTION \n"); break;
							case 4:printf("[*] Info type : STT_FILE \n"); break;
							case 13:printf("[*] Info type : STT_LOPROC \n"); break;
							case 15:printf("[*] Info type : STT_HIPROC \n"); break;
							default:printf("[*] Info type :unknown \n"); break;
						}
						
						printf("[*] Other : %d\n", Symtab[compt].st_other);
						
						printf("[*] Section index : %d\n", Symtab[compt].st_shndx);*/
					
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
					
					/*if(isVerbose){
						printf("[*] Name indice : %d\n",Symtab[compt].st_name);
		
						// Searching the name of the section
						ind_name = Shtab[header.e_shstrndx].sh_offset;
						int l = 0;
		
						ind_name =  ind_name + Symtab[compt].st_name;
		
						while(fileBytes[ind_name] != '\0'){
						name[l] = fileBytes[ind_name];
						k++;
						ind_name++;
						}
						name[l]='\0';
						// Displaying the name
						printf("[*] Name of the section : %s\n", name);
						
						
						switch(ELF32_ST_TYPE(Symtab[compt].st_info)){
							case 2: case 1: printf("[*] Value: Adress : %x\n", Symtab[compt].st_value );break; 
							default: printf("[*] Value: Alignment/Offset : %d\n", Symtab[compt].st_value );break;
						}
						
						
						printf("[*] Size : %x\n", Symtab[compt].st_size);
						
						printf("[*] Info code : %x\n", Symtab[compt].st_info);
						
						switch (ELF32_ST_BIND(Symtab[compt].st_info)) {
							case 0: printf("[*] Info bind : STB_LOCAL \n"); break;
							case 1:printf("[*] Info bind : STB_GLOBAL\n"); break; 						A COMPLETER
							case 2:printf("[*] Info bind : STB_WEAK\n"); break;
							case 13:printf("[*] Info bind : STB_LOPROC\n"); break;
							case 15:printf("[*] Info bind : STB_HIPROC\n"); break;
							default:printf("[*] Info bind :unknown \n"); break;
						}
							
						switch (ELF32_ST_TYPE(Symtab[compt].st_info)) {
							case 0: printf("[*] Info type : STT_NOTYPE \n"); break;
							case 1:printf("[*] Info type : STT_OBJECT \n"); break;
							case 2:printf("[*] Info type : STT_FUNC \n"); break;
							case 3:printf("[*] Info type : STT_SECTION \n"); break;
							case 4:printf("[*] Info type : STT_FILE \n"); break;
							case 13:printf("[*] Info type : STT_LOPROC \n"); break;
							case 15:printf("[*] Info type : STT_HIPROC \n"); break;
							default:printf("[*] Info type :unknown \n"); break;
						}
						
						printf("[*] Other : %d\n", Symtab[compt].st_other);
						
						printf("[*] Section index : %d\n", Symtab[compt].st_shndx);
					
					} */
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
