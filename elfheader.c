#include "elfheader.h"

Elf32_Ehdr readHeader(char * filePath, int isVerbose){

	Elf32_Ehdr header;
	int isValid = 1;
    int isBigEndian = 0;
	unsigned char* fileBytes = readFileBytes(filePath);


	if(fileBytes[0] == 127 && fileBytes[1] == 69 && fileBytes[2] == 76 && fileBytes[3] == 70){
        if(isVerbose == 1)
            printf("[*] Fichier ELF Reconnu\n");
        header.e_ident[EI_MAG0] = fileBytes[0];
        header.e_ident[EI_MAG1] = fileBytes[1];
        header.e_ident[EI_MAG2] = fileBytes[2];
        header.e_ident[EI_MAG3] = fileBytes[3];
	}
	else{
        if(isVerbose == 1)
            printf("[E] Le fichier founi n'est pas un fichier ELF\n");
        isValid = 0;
	}
	
	int i = 4;

	if(isValid == 1) {
		if(fileBytes[i]==1){
			if(isVerbose == 1)
				printf("[*] Classe : 32 Bits ELFCLASS32\n");
		}
		else {
			if(isVerbose == 1)
				printf("[E] Classe invalide\n");
			isValid = 0;
		}
		header.e_ident[EI_CLASS] = fileBytes[i];
	}
	
	i++;
	if(isValid == 1) {
		if(fileBytes[i]==1){
			if(isVerbose == 1)
				printf("[*] EI_DATA : LSB Little endian\n");
		}
		else if(fileBytes[i]==2){
			if(isVerbose == 1)
				printf("[*] EI_DATA : MSB Big endian\n");
			isBigEndian=1;
		}
		else {
			if(isVerbose == 1)
				printf("[E] Erreur de lecture de l'encodage EI_DATA\n");
		isValid = 0;
		}
		header.e_ident[EI_DATA] = fileBytes[i];
	}
	
	i++;
	if(isValid == 1) {
		if(fileBytes[i]!=0){
			if(isVerbose == 1)
				printf("[*] Version du header : %d\n",fileBytes[i]);
		}
		else {
			if(isVerbose == 1)
				printf("[E] Version du header invalide");
			isValid = 0;
		}
		header.e_ident[EI_VERSION] = fileBytes[i];
	}

	if(isBigEndian == 1)
        i=17;
    if(isBigEndian == 0)
		i=16;

	if(isValid == 1) {
		if(fileBytes[i]==0){
			if(isVerbose == 1)
				printf("[*] Pas de type de fichiers");
		else if (fileBytes[i]==1){
			if(isVerbose == 1)
				printf("[*] Type du fichier : ");






}
