
//////////////////////////////README//////////////////////////////

Lecteur de fichier ;

	filereader.c
	filereader.h

1.Affichage de l’en-tête ;
	
	elfheader.c
	elfheader.h
2.Affichage de la table des sections et des détails relatifs à chaque section ;

	elfsectiontab.c
	elfsectiontab.h

3.Affichage du contenu d’une section ;

	elfsection.c
	elfsection.h

4.Affichage de la table des symboles et des détails relatifs à chaque symbole ;

	elfsymtab.c //Verification à faire, pour le moment tous les symboles sont a zero ou inexistant sur les fichiers testés.
	elfsymtab.h

5.Affichage des tables de réimplantation et des détails relatifs à chaque entrée ;

	elfreloc.c  // Bon fonctionnement a verifier, affichage r_offset pas sûr du tout
	elfreloc.h

////////////////////////////////////////////////////////////////////
