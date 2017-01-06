#ifndef __FILE_READER__
#define __FILE_READER__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*renvoi un tableau de char qui contient le contenu du fichier de nom *name */
unsigned char* readFileBytes(const char *name);

#endif

