#include <stdlib.h>
#include <stdio.h>
#include "texte.h"
#include "fichier.h"
#include "trame.h"
#include "conversion.h"

int main(int argc, char *argv[])
{
	char * res; 
	char * nomFichierR = "Entree.txt";
	char * nomFichierW = "Sortie.txt";
	//Lecture de la trame
	int nbL = compter_lignes(nomFichierR);
	res = lire_fichier(nomFichierR, &nbL);
	//Traitement de la trame 
	clean_fichier(nomFichierW); 
	verification_trame(res,nbL);
	//Décodage de la trame
	char * trame_traitee ;
	nbL = compter_lignes(nomFichierW);
	trame_traitee = lire_fichier(nomFichierW, &nbL);
	ethernet(trame_traitee);
    return 0;
}