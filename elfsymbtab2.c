#include "elfsymbtab.h"


int readSymbtab(Elf32_Ehdr *header, Elf32_Shdr * Shtab,Elf32_Sym * Symtab ,char * filePath, int isVerbose){
 
int j;
unsigned char* fileBytes = readFileBytes(filePath);
FILE *f;

f = fopen(filePath, "r");
int ind_name;
char name[256];
int compt = 0;

if(f != NULL){
	fseek(f, header->e_shoff, SEEK_SET);
	
	for (j=0; j<header->e_shnum; j++){
		if (( Shtab[j].sh_type == 2 ) || ( Shtab[j].sh_type == 6 )){
			int k =0;
			while (k < header->e_shentsize){			
				if (compt != 0){		//
						Symtab = (Elf32_Sym * ) realloc(Symtab, sizeof(Symtab)+sizeof(Elf32_Sym));
						if (Symtab == NULL){printf("[E] Echec realloc dans la table des symboles \n");return 0;}
						}
				fread(&Symtab[compt], sizeof(Elf32_Sym), 1, f);
				k=k+16;
			}
		}
	}		
	fclose(f);
	
	for (j=0; j<compt; j++){


		if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {

			Symtab[j].st_name =reverse_4(Symtab[j].st_name);
			Symtab[j].st_value =reverse_4(Symtab[j].st_value);
			Symtab[j].st_size =reverse_4(Symtab[j].st_size);
			Symtab[j].st_info =reverse_4(Symtab[j].st_info );
			Symtab[j].st_other =reverse_4(Symtab[j].st_other);
			Symtab[j].st_shndx =reverse_4(Symtab[j].st_shndx);
			
		}
		
		if(isVerbose){
						printf("[*] Name indice : %d\n",Symtab[j].st_name);
		
						// Searching the name of the section
						ind_name = Shtab[header->e_shstrndx].sh_offset;
						int l = 0;
		
						ind_name =  ind_name + Symtab[j].st_name;
		
						while(fileBytes[ind_name] != '\0'){
						name[l] = fileBytes[ind_name];
						l++;
						ind_name++;
						}
						name[l]='\0';
						// Displaying the name
						printf("[*] Name of the section : %s\n", name);
						
						
						switch(header->e_type){
							case 1: printf("[*] Value: Alignment/Offset : %d\n", Symtab[j].st_value );break;
							case 2: case 3: printf("[*] Value: Adress : %x\n", Symtab[j].st_value );break; 
							default: printf("[*] Value: %x\n", Symtab[j].st_value );break; 
						}
						
						
						printf("[*] Size : %x\n", Symtab[j].st_size);
						
						printf("[*] Info code : %x\n", Symtab[j].st_info);
						
						switch (ELF32_ST_BIND(Symtab[j].st_info)) {
							case 0: printf("[*] Info bind : STB_LOCAL \n"); break;
							case 1:printf("[*] Info bind : STB_GLOBAL\n"); break;
							case 2:printf("[*] Info bind : STB_WEAK\n"); break;
							case 13:printf("[*] Info bind : STB_LOPROC\n"); break;
							case 15:printf("[*] Info bind : STB_HIPROC\n"); break;
							default:printf("[*] Info bind :unknown \n"); break;
						}
							
						switch (ELF32_ST_TYPE(Symtab[j].st_info)) {
							case 0: printf("[*] Info type : STT_NOTYPE \n"); break;
							case 1:printf("[*] Info type : STT_OBJECT \n"); break;
							case 2:printf("[*] Info type : STT_FUNC \n"); break;
							case 3:printf("[*] Info type : STT_SECTION \n"); break;
							case 4:printf("[*] Info type : STT_FILE \n"); break;
							case 13:printf("[*] Info type : STT_LOPROC \n"); break;
							case 15:printf("[*] Info type : STT_HIPROC \n"); break;
							default:printf("[*] Info type :unknown \n"); break;
						}
						
						printf("[*] Other : %d\n", Symtab[j].st_other);
						
						printf("[*] Section index : %d\n", Symtab[j].st_shndx);
					
			}

	
	}


} else {
	printf("Probleme ouverture fichier(table section)\n");
	return 0;
}


	return 1;
}

