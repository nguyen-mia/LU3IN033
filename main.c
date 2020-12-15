#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
	char *trame_traitee, *trame ;
	nbL = compter_lignes(nomFichierW);
	trame_traitee = lire_fichier(nomFichierW, &nbL);
	int cpt_trame = 1;
	while( (trame = strsep(&trame_traitee,"\r")) != NULL) {
        if(strlen(trame) >2) {
        	printf("\n--------------------------------- TRAME %d ---------------------------------", cpt_trame);
        	ethernet(trame);
        	cpt_trame++;
        }
    }
    free(res);
    free(trame_traitee);
	return 0;
}