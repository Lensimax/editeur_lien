#include "elfheader.h"

///// REMPLISSAGE DE LA STRUCTURE

int readHeader(char *filePath, Elf32_Ehdr *header){

	FILE *f;

	//ouverture du fichier filePath
	f = fopen(filePath, "r");		
	
	//si l'ouverture reussit
	if(f != NULL){				
		//on rempli le header
		fread(header, sizeof(Elf32_Ehdr), 1, f);	
		//fermeture du fichier
		fclose(f);	
	//si l'ouverture echoue		
	} else {				
		//message d'erreur
		printf("Probleme ouverture fichier (header)\n");
		return 0;
	}

	//si on a le chiffre magique suivit de ELF(=fichier ELF)
	if(header->e_ident[EI_MAG0] == 127 && header->e_ident[EI_MAG1] == 69 && header->e_ident[EI_MAG2] == 76 && header->e_ident[EI_MAG3] == 70){

		//inversion des octets si on a un problème de boutisme	
		if((header->e_ident[EI_DATA] == 1 && is_big_endian()) || ((header->e_ident[EI_DATA] == 2) && !is_big_endian())) {
		header->e_type = reverse_2(header->e_type);
		header->e_machine = reverse_2(header->e_machine);
		header->e_version = reverse_4(header->e_version);
		header->e_entry = reverse_4(header->e_entry);
		header->e_phoff = reverse_4(header->e_phoff);
		header->e_shoff = reverse_4(header->e_shoff);
		header->e_flags = reverse_4(header->e_flags);
		header->e_ehsize = reverse_2(header->e_ehsize);
		header->e_phentsize = reverse_2(header->e_phentsize);
		header->e_phnum = reverse_2(header->e_phnum);
		header->e_shentsize = reverse_2(header->e_shentsize);
		header->e_shnum = reverse_2(header->e_shnum);
		header->e_shstrndx = reverse_2(header->e_shstrndx);
		}
		return 1;
	//si on est pas dans un fichier ELF
	} else {	
		return 0;
	}

	

}



 /////// AFFICHAGE


void aff_header(Elf32_Ehdr *header){

	//affichage fichier ELF valide
	if(header->e_ident[EI_MAG0] == 127 && header->e_ident[EI_MAG1] == 69 && header->e_ident[EI_MAG2] == 76 && header->e_ident[EI_MAG3] == 70){
		printf("[*] Fichier ELF Reconnu\n");
	}else{	printf("[E] Le fichier fourni n'est pas un fichier ELF\n");
	}
	
	//affichage classe du fichier
	if (header->e_ident[EI_CLASS] == 1){
		printf("[*] Classe : 32 Bits ELFCLASS32\n");
	}else{	printf("[E] Classe : Invalide\n");}
	
	//affichage boutisme fichier
	switch(header->e_ident[EI_DATA]) {
		case 1: printf("[*] EI_DATA : LSB Little endian\n"); break;
		case 2: printf("[*] EI_DATA : MSB Big endian\n"); break;
		default: printf("[E] Erreur de lecture de l'encodage EI_DATA\n"); break;
	}
	
	//affichage version du header
	switch(header->e_ident[EI_VERSION]) {
		case 0: printf("[E] Version du header invalide\n"); break;
		default: printf("[*] Version du header : %d\n",header->e_ident[EI_VERSION]); break;
	}
	
	//affichage PAD du fichier
	switch(header->e_ident[EI_PAD]) {
		case 0: printf("[*] ABI : UNIX SYSTEM V\n"); break;
		case 3: printf("[*] ABI : LINUX\n"); break;
		case 7: printf("[*] ABI : IBM AIX\n"); break;
		case 64: printf("[*] ABI : ARM EABI\n"); break;
		case 97: printf("[*] ABI : ARM\n"); break;
		default: printf("[W] ABI : INCONNU\n"); break;
	}
	
	//affichage type du fichier
	switch(header->e_type) {
		case 0: printf("[*] Pas de type de fichiers\n"); break;
		case 1: printf("[*] Type du fichier : Relocatable file\n"); break;
		case 2: printf("[*] Type du fichier : Fichier executable\n"); break;
		case 3: printf("[*] Type du fichier : Fichier partagé\n"); break;
		case 4: printf("[*] Type du fichier : Core file\n"); break;
		default: printf("[W] Type du fichier : Inconnu\n"); break;
	}
	
	//affichage machine
	switch(header->e_machine) {
		case 0:printf("[*] Aucune machine cible\n"); break;
		case 2:printf("[*] Machine cible : SPARC\n"); break;
		case 3:printf("[*] Machine cible : Intel 80386\n"); break;
		case 4:printf("[*] Machine cible : Motorola 68000\n"); break;
		case 7:printf("[*] Machine cible : Intel i860\n"); break;
		case 8:printf("[*] Machine cible : MIPS I\n"); break;
		case 19:printf("[*] Machine cible : Intel i960\n"); break;
		case 20:printf("[*] Machine cible : PowerPC\n"); break;
		case 40:printf("[*] Machine cible : ARM\n"); break;
		case 50:printf("[*] Machine cible : Intel IA64\n"); break;
		case 62:printf("[*] Machine cible : x64\n"); break;
		default:printf("[W] Machine cible non reconnue\n"); break;
	}

	//affichage version du fichier
	switch(header->e_version) {
		case 0: printf("[E] Version invalide\n"); break;
		case 1: printf("[*] Version : originale\n"); break;
		default: printf("[*] Version : 0x%x\n",header->e_version); break;
	}

	//affichage point d'entree
	printf("[*] Point d'entrée : 0x%x\n",header->e_entry);

	//affichage offset du debut des entetes de header
	printf("[*] Début des entêtes de header : %d\n",header->e_phoff);

	//affichage offset du debut des entetes de s
	printf("[*] Début des entêtes de section : %d\n",header->e_shoff);

	//affichage flags
	printf("[*] Flags : 0x%x\n",header->e_flags);

	//affichage taille du header
	printf("[*] Taille du header : %d\n",header->e_ehsize);

	//affichage taille d'une entree dans la table d'entete de programme
	printf("[*] Taille d'une entrée dans la table contenant l'entête de programme : %d\n",header->e_phentsize);

	//affichage nombre d'entrees dans la table
	printf("[*] Nombre d'entrées dans la table contenant l'entête de programme : %d\n",header->e_phnum );

	//affichage taille d'une entree dans la table des entetes
	printf("[*] Taille d'une entrée dans la table des entêtes de section : %d\n",header->e_shentsize);

	//affichage nombre d'entrees dans la table des entetes
	printf("[*] Nombre d'entrées dans la table des entêtes de section : %d\n",header->e_shnum);

	//affichage indice du nom des s
	printf("[*] Indice des noms de section : %d\n",header->e_shstrndx);




}

