#include "filereader.h"

unsigned char* readFileBytes(const char *name)
{
    FILE *fl = fopen(name, "r");	//ouverture du fichier
    fseek(fl, 0, SEEK_END);		
    long len = ftell(fl);		//calcul longueur du fichier
    unsigned char *ret = malloc(len);	//allocation de la taille du fichier dans le tableau de char
    fseek(fl, 0, SEEK_SET);
    fread(ret, 1, len, fl);		//remplissage du tableau de char
    fclose(fl);				//fermeture du fichier
    return ret;				//renvoi du tableau
}
