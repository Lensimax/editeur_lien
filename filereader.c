#include "filereader.h"

unsigned char* readFileBytes(const char *name)
{
	//ouverture du fichier
	FILE *fl = fopen(name, "r");	
	fseek(fl, 0, SEEK_END);		
	//calcul longueur du fichier
	long len = ftell(fl);		
	//allocation de la taille du fichier dans le tableau de char
	unsigned char *ret = malloc(len);	
	fseek(fl, 0, SEEK_SET);
	//remplissage du tableau de char
	fread(ret, 1, len, fl);		
	//fermeture du fichier
	fclose(fl);			
	//renvoi du tableau	
	return ret;				
}
