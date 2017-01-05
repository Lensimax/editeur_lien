#include "elfsectiontab.h"

int readSectTab(Elf32_Shdr ** shtab, Elf32_Ehdr * header, char * filePath){
 
Elf32_Half j;
FILE *f;

f = fopen(filePath, "r");

if(f != NULL){
	for (j=0; j<header->e_shnum; j++){
		fread(shtab[j], sizeof(Elf32_Shdr), 1, f);
	}		
	fclose(f);

} else {
	printf("Probleme ouverture fichier(table section)\n");
	return 0;
}








	return 1;
}



/////// AFFICHAGE


void aff_Sheader(Elf32_Shdr ** shtab, Elf32_Ehdr * header, char * filePath){

int i, j, k;
char * name;
int ind_name;
unsigned char* fileBytes = readFileBytes(filePath);


printf("Lecture des headers de sections\n");

printf("  [Nr]  Nom\t\t        Type\t         Adr    \tDécala.\tTaille\tES\tFan\tLN\tInf\tAl\n");

for(i=0;i<header->e_shnum;i++){

// Searching the name of the section
		ind_name = shtab[header->e_shstrndx].sh_offset;
		k = 0;
		
		ind_name =  ind_name + shtab[j]->sh_name;
		
		while(fileBytes[ind_name] != '\0'){
			name[k] = fileBytes[ind_name];
			k++;
			ind_name++;
		}
		name[k]='\0';


	printf("  [%2d] %-25s%-17s%08d\t%06x\t%06x\t%02x\t%-1.04s\t%d\t%d\t%d\n",i,name,nom_type(shtab[i]->sh_type),shtab[i]->sh_addr,shtab[i]->sh_offset,shtab[i]->sh_size,shtab[i]->sh_entsize,nom_flags(shtab[i]->sh_flags),shtab[i]->sh_link,shtab[i]->sh_info,shtab[i]->sh_addralign);
}


}

char * nom_type(int i){
switch (Shtab[j].sh_type) {
			case 0: printf("[E] Type : SHT_NULL\n"); break;
			case 1:printf("[*] Type : SHT_PROGBITS\n"); break;
			case 2:printf("[*] Type : SHT_SYMTAB\n"); break;
			case 3:printf("[*] Type : SHT_STRTAB\n"); break;
			case 4:printf("[*] Type : SHT_RELA\n"); break;
			case 5:printf("[*] Type : SHT_HASH\n"); break;
			case 6:printf("[*] Type : SHT_DYNAMIC\n"); break;
			case 7:printf("[*] Type : SHT_NOTE\n"); break;
			case 8:printf("[*] Type : SHT_NOBITS\n"); break;
			case 9:printf("[*] Type : SHT_REL\n"); break;
			case 10:printf("[*] Type : SHT_SHLIB\n"); break;
			case 11:printf("[*] Type : SHT_DYNSYM\n"); break;
			case 0x70000000:printf("[*] Type : SHT_LOPROC\n"); break;
			case 0x7fffffff:printf("[*] Type : SHT_HIPROC\n"); break;
			case 0x80000000:printf("[*] Type : SHT_LOUSER\n"); break;
			case 0xffffffff:printf("[*] Type : SHT_HIUSER\n"); break;
		}
}




/*for (j=0; j<header.e_shnum; j++){
	





	Shtab[j].sh_name = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];	//name index
	i = i+4;			
	
	Shtab[j].sh_type = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3]; //type
	i = i+4;

	
	Shtab[j].sh_flags = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
	i = i+4;

	Shtab[j].sh_addr = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
	i = i+4;

	Shtab[j].sh_offset = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
	i = i+4;

	Shtab[j].sh_size = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
	i = i+4;

	Shtab[j].sh_link = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
	i = i+4;
	
	Shtab[j].sh_info = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
	i = i+4;

	Shtab[j].sh_addralign = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
	i = i+4;

	Shtab[j].sh_entsize = (fileBytes[i]<<24) + (fileBytes[i+1]<<16) + (fileBytes[i+2]<<8) + fileBytes[i+3];
	i = i+4;

}


for (j=0; j<header.e_shnum; j++){
	if (isVerbose ) {

		printf("[*] Name indice : %d\n",Shtab[j].sh_name);
		
		// Searching the name of the section
		ind_name = Shtab[header.e_shstrndx].sh_offset;
		k = 0;
		
		ind_name =  ind_name + Shtab[j].sh_name;
		
		while(fileBytes[ind_name] != '\0'){
		name[k] = fileBytes[ind_name];
		k++;
		ind_name++;
		}
		name[k]='\0';
		// Displaying the name
		printf("[*] Name of the section : %s\n", name);

		switch (Shtab[j].sh_type) {
			case 0: printf("[E] Type : SHT_NULL\n"); break;
			case 1:printf("[*] Type : SHT_PROGBITS\n"); break;
			case 2:printf("[*] Type : SHT_SYMTAB\n"); break;
			case 3:printf("[*] Type : SHT_STRTAB\n"); break;
			case 4:printf("[*] Type : SHT_RELA\n"); break;
			case 5:printf("[*] Type : SHT_HASH\n"); break;
			case 6:printf("[*] Type : SHT_DYNAMIC\n"); break;
			case 7:printf("[*] Type : SHT_NOTE\n"); break;
			case 8:printf("[*] Type : SHT_NOBITS\n"); break;
			case 9:printf("[*] Type : SHT_REL\n"); break;
			case 10:printf("[*] Type : SHT_SHLIB\n"); break;
			case 11:printf("[*] Type : SHT_DYNSYM\n"); break;
			case 0x70000000:printf("[*] Type : SHT_LOPROC\n"); break;
			case 0x7fffffff:printf("[*] Type : SHT_HIPROC\n"); break;
			case 0x80000000:printf("[*] Type : SHT_LOUSER\n"); break;
			case 0xffffffff:printf("[*] Type : SHT_HIUSER\n"); break;
		}

		switch (Shtab[j].sh_flags) {
			case 0: printf("[E] Flag : SHF_NULL\n"); break;
			case 0x1:printf("[*] Flag : SHF_WRITE\n"); break;
			case 0x2:printf("[*] Flag : SHF_ALLOC\n"); break;
			case 0x4:printf("[*] Flag : SHF_EXECINSTR\n"); break;
			case 0xf0000000:printf("[*] Flag : SHF_MASKPROC\n"); break;
		}
		
		printf("[*] Adrress : %x\n", Shtab[j].sh_addr);

		printf("[*] Offset : %d\n", Shtab[j].sh_offset);

		printf("[*] Size : %x\n", Shtab[j].sh_size);

		printf("[*] Link : %x\n", Shtab[j].sh_link);

		switch (Shtab[j].sh_type) {
			case 2: case 11: printf("[*] Info : index %x of the relocation\n",Shtab[j].sh_info); break;
			case 4: case 9: printf("[*] Info : index %x of last local symbol+1\n",Shtab[j].sh_info); break;
			default :printf("[*] Info : No Data\n"); break;
		
		}

		printf("[*] Addralign : %x\n", Shtab[j].sh_addralign);

		printf("[*] Entsize : %x\n", Shtab[j].sh_entsize);
		

	}






}*/




