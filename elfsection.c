#include "elfsection.h"

Elf32_Shdr * readSectTab(Elf32_Ehdr header, char * filePath, int isVerbose){
  
  Elf32_Addr i = header.e_entry + header.e_shoff ;//adresse de depart(0 par defaut) + décalage 
  unsigned char* fileBytes = readFileBytes(filePath);
  Elf32_Shdr * Shtab = malloc(sizeof(Elf32_Shdr)*header.e_shnum);
  ELF32_Half j;
  
  for (j=0, j<header.e_shnum, j++){
    
    Shtab[j].sh_name = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];	//name index
    i = i+4;			
    
    Shtab[j].sh_type = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3]; //type
    i = i+4;
    
    Shtab[j].sh_flags = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
    i = i+4;
    
    Shtab[j].sh_addr = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
    i = i+4;

    Shtab[j].sh_offset = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
    i = i+4;
    
    Shtab[j].sh_size = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
    i = i+4;
    
    Shtab[j].sh_link = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
    i = i+4;
    
    Shtab[j].sh_info = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
    i = i+4;
    
    Shtab[j].sh_addralign = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
    i = i+4;
    
    Shtab[j].sh_entsize = fileBytes[i]<<24 + fileBytes[i+1]<<16 + fileBytes[i+2]<<8 + fileBytes[i+3];
    i = i+4;
    
    if (isVerbose ) {
      
      printf("[*] Name indice : %ld\n",Shtab[j].sh_name);
      
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
      
      printf("[*] Adrress : %lx\n", Shtab[j].sh_addr);
      
      printf("[*] Offset : %ld\n", Shtab[j].sh_offset);
      
      printf("[*] Size : %lx\n", Shtab[j].sh_size);
      
      printf("[*] Link : %lx\n", Shtab[j].sh_link);
      
      printf("[*] Offset : %ld\n", Shtab[j].sh_offset);
      
      switch (Shtab[j].sh_type) {
      case 2: case 11: printf("[*] Info : index %lx of the relocation\n",Shtab[j].sh_info); break;
      case 4: case 9: printf("[*] Info : index %lx of last local symbol+1\n"); break;
      default :printf("[*] Info : No Data\n"); break;
	
      }
      
      printf("[*] Addralign : %lx\n", Shtab[j].sh_addralign);
      
      printf("[*] Entsize : %lx\n", Shtab[j].sh_entsize);
        
    }
       
  }
  
}
