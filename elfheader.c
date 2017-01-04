#include "elfheader.h"

Elf32_Ehdr readHeader(char * filePath, int isVerbose){


	Elf32_Ehdr header;
	int isValid = 1;
	unsigned int first;
    unsigned int second;
	unsigned int sum;
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
            printf("[E] Le fichier fourni n'est pas un fichier ELF\n");
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
				printf("[E] Classe : Invalide\n");
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

	i++;

	if(isValid == 1) {
		
		if(fileBytes[i]== 0){
			if(isVerbose == 1)
				printf("[*] ABI : UNIX SYSTEM V\n");
		}
		else if (fileBytes[i] == 3) {
			if(isVerbose == 1)
				printf("[*] ABI : LINUX\n");
		}
		else if (fileBytes[i] == 7) {
			if(isVerbose == 1)
				printf("[*] ABI : IBM AIX\n");
		}
		else if (fileBytes[i] == 64) {
			if(isVerbose == 1)
				printf("[*] ABI : ARM EABI\n");
		}
		else if (fileBytes[i] == 97) {
			if(isVerbose == 1)
				printf("[*] ABI : ARM\n");
		}
		else {
			if(isVerbose == 1)
				printf("[W] ABI : INCONNU\n");
		}
		
		header.e_ident[EI_VERSION] = fileBytes[i];
	}

	i=16; 

	if(isValid == 1) {
		first = fileBytes[i];
		second = fileBytes[i+1];
		sum = first * 16 * 16 + second;
		if(sum == 0){
			if(isVerbose == 1)
				printf("[*] Pas de type de fichiers\n");
		}
		else if (sum ==1){
			if(isVerbose == 1)
				printf("[*] Type du fichier : Relocatable file\n");
		}
		else if (sum ==2){
			if(isVerbose == 1)
				printf("[*] Type du fichier : Fichier executable\n");
		}
		else if (sum==3){
			if(isVerbose == 1)
				printf("[*] Type du fichier : Fichier partagé\n");
		}
		else if (sum ==4){
			if(isVerbose == 1)
				printf("[*] Type du fichier : Core file\n");
		}
		else {
			if(isVerbose == 1)
				printf("[W] Type du fichier : Inconnu\n");
		}
		header.e_type = sum;
	}
	
	i+=2; ////////////////////////////////////////////////
	
	if(isValid == 1){
		first = fileBytes[i];
		second = fileBytes[i+1];
		sum = first * 16 * 16 + second;
        if(isVerbose == 1){
            if(sum == 0){
                printf("[*] Aucune machine cible\n");
            }
            else if(sum == 2){
                printf("[*] Machine cible : SPARC\n");
            }
            else if(sum == 3){
                printf("[*] Machine cible : Intel 80386\n");
            }
            else if(sum == 4){
                printf("[*] Machine cible : Motorola 68000\n");
            }
            else if(sum == 7){
                printf("[*] Machine cible : Intel i860\n");
            }
            else if(sum == 8){
                printf("[*] Machine cible : MIPS I\n");
            }
            else if(sum == 19){
                printf("[*] Machine cible : Intel i960\n");
            }
            else if(sum == 20){
                printf("[*] Machine cible : PowerPC\n");
            }
            else if(sum == 40){
                printf("[*] Machine cible : ARM\n");
            }
            else if(sum == 50){
                printf("[*] Machine cible : Intel IA64\n");
            }
            else if(sum == 62){
                printf("[*] Machine cible : x64\n");
            }
            else{
                printf("[W] Machine cible non reconnue\n");
			}
		}
	header.e_machine = sum;
	}

	i+=2; ////////////////////////////////////////////////

	if(isValid == 1){
		sum = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
		if(sum == 0){
        	if(isVerbose == 1)
				printf("[E] Version invalide\n");

		}
		else if(sum == 1){
			if(isVerbose == 1)
				printf("[*] Version : 0x%x\n",sum);
	
		}
		else {
			printf("[W] Version inconnue\n");
		}
		header.e_version = sum;

	}

	i+=4; ///////////////////////////////////////////

	if(isValid == 1){
		sum = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];

		if(isVerbose == 1)
				printf("[*] Point d'entrée : 0x%x\n",sum);

		header.e_entry = sum;
	
		}

	i+=4;

	if(isValid == 1){
		sum = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];

		if(isVerbose == 1)
				printf("[*] Début des en-têtes de header : %d\n",sum);

		header.e_phoff = sum;
	
		}

	i+=4;

	if(isValid == 1){
		sum = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
		
		if(isVerbose == 1)
				printf("[*] Début des en-têtes de sections : %d\n",sum);

		header.e_shoff = sum;
	
		}

	i+=4;

	if(isValid == 1){
		sum = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];

		if(isVerbose == 1)
				printf("[*] Flags : 0x%x\n",sum);

		header.e_flags = sum;
	
		}

	i+=4;

	if(isValid == 1){
		first = fileBytes[i];
		second = fileBytes[i+1];
		sum = first * 16 * 16 + second;
        if(isVerbose == 1)
			printf("[*] Taille du header : %d\n",sum);
	header.e_ehsize = sum;
	}
	i+=2;

	if(isValid == 1){
		first = fileBytes[i];
		second = fileBytes[i+1];
		sum = first * 16 * 16 + second;
        if(isVerbose == 1)
			printf("[*] Taille d'une entrée dans la table contenant l'entête de programme : %d\n",sum);
	header.e_phentsize = sum;
	}
	i+=2;

	if(isValid == 1){
		first = fileBytes[i];
		second = fileBytes[i+1];
		sum = first * 16 * 16 + second;
        if(isVerbose == 1)
			printf("[*] Nombre d'entrées dans la table contenant l'entête de programme : %d\n",sum);
	header.e_phnum = sum;
	}
	i+=2;

	if(isValid == 1){
		first = fileBytes[i];
		second = fileBytes[i+1];
		sum = first * 16 * 16 + second;
        if(isVerbose == 1)
			printf("[*] Taille d'une entrée dans la table des entêtes de sections  : %d\n",sum);
	header.e_shentsize = sum;
	}
	i+=2;

	if(isValid == 1){
		first = fileBytes[i];
		second = fileBytes[i+1];
		sum = first * 16 * 16 + second;
        if(isVerbose == 1)
			printf("[*] Nombre d'entrées dans la table des entêtes de sections : %d\n",sum);
	header.e_shnum = sum;
	}
	i+=2;

	if(isValid == 1){
		first = fileBytes[i];
		second = fileBytes[i+1];
		sum = first * 16 * 16 + second;
        if(isVerbose == 1)
			printf("[*] Indice des noms de sections : %d\n",sum);
	header.e_shstrndx = sum;
	}
	
	return header;

}
	








