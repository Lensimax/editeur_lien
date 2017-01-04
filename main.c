#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <getopt.h>
#include <sys/stat.h>

#include "elfheader.h"
#include "elfsection.h"

int main(int argc, char * argv[]){

	readHeader("vecteur.o",1);

return 0;
}
