



int sectfusion( Elf32_Ehdr *header1,  Elf32_Ehdr *header2, Elf32_Shdr * shtab1, Elf32_Shdr * shtab2){
t=taille totale des sections 1

pour chaque section de 1 on cherche celles de type PROGBITS
	pour chacune de celles-ci on cherche si on en a pa sune dan s2 qui a le meme nom
			la taille de toutes les section de 1 prend + la taille de la section 2 qu'on vient de trouver
			la taille de la section pren +sh_size de la deuxieme


for(int i = 0; i < nb de section de 2, i++){
	si shtab2[i].type == PROGBITS
		on cherche si le nom 



}










}
