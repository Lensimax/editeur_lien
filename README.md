
//////////////////////////////README//////////////////////////////

/////PHASE 1////// 


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

	elfsymtab.c 
	elfsymtab.h

5.Affichage des tables de réimplantation et des détails relatifs à chaque entrée ;

	elfreloc.c
	elfreloc.h


//////////////////////////////////////////////////////////////////////

/////PHASE 2/////


6.Fusion et renumérotation des sections;

	sectionfus.c
	sectionfus.h

7.Fusion, renumérotation et correction des symboles;

	symbolfus.c
	symbolfus.h

8.Fusion et correction des tables de réimplantations;

	fusrel.c
	fusrel.h

9.Production d’un fichier résultat au format ELF;

	fusion.c
	fusion.h


//////////////////////////////////////////////////////////////////////

/////OUTILS ET MAIN/////
Lecteur de fichier ;

	filereader.c
	filereader.h

Verificatio big/little endian ;

	util.c
	util.h

Création du fichier de fusion ;

	testfus.c
	testfus.h

Remplissage des structures

	fill_struct.c
	fill_struct.h

Affichage optionnel après remplissage;

	main.c
	main.h


//////////////////////////////README//////////////////////////////
