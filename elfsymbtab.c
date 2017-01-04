#include "elfsymbtab.h"


Elf32_Sym * readSymbtab(Elf32_Ehdr header, Elf32_Shdr * Shtab,char * filePath, int isVerbose){
	
	unsigned char* fileBytes = readFileBytes(filePath);
	
	// OU EST LE NOMBRE DE SYMBOLES ? //
	for (j=0; j<header.e_shnum; j++){
		if (( Shtab[j].sh_type == 2 ) || ( Shtab[j].sh_type == 6 )){
			

		i = Shtab[j].sh_offset; // debut de la table de symboles
		
		/*remplissage du Elf32_Sym */

		
		}
	}

int printSymbtab( Elf32_Sym * Symtab){

	return 0;
}
