#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fichier.h"


#define BUFFER 1000
#define TAILLE_MAX 6000

#define LIGNE_MAX 6000

int compter_lignes(char *nomFichier){
	FILE *pFi;
	int nbL=0;
	char c;
	
	pFi=fopen(nomFichier, "r");
	if(pFi==NULL){
		fprintf(stderr, "compter_lignes:: Ne peut ouvrir %s\nEXITING\n", nomFichier);
		exit(1);
	}
	while((c=fgetc( pFi))!=EOF)
		if(c=='\n')
			nbL++;
	fclose(pFi);
	return nbL + 1;
}

char * lire_fichier(char *nomFichier, int * p_nbL){
  char ligne_lue[BUFFER];
  FILE * pt_f= NULL;  
  pt_f = fopen (nomFichier, "r") ;
  if (pt_f == NULL) {
    fprintf (stderr, "Impossible d'ouvrir %s \n", nomFichier);
   	return 0;
  } 
  *p_nbL = compter_lignes(nomFichier); 
  char * res = NULL;
  res = (char *) malloc(sizeof(char) * TAILLE_MAX);

  while ((fgets(ligne_lue, BUFFER, pt_f))) {
  	strcat(res, ligne_lue);
  }	
  strcat(res, "\n");
  fclose(pt_f);
  return res;
}


void ecrire_fichier(char *nomFichier, char * texte){
	FILE *pt_fichier = NULL;
	pt_fichier = fopen(nomFichier, "a");
	if (pt_fichier == NULL) {
    	fprintf (stderr, "Impossible d'ouvrir %s \n", nomFichier);
   		return;
  	}
  	fprintf(pt_fichier, "%s \n",texte);
  	fclose(pt_fichier);
	return;
}

void ecrire_fichier_octet(char *nomFichier, char * texte){
	FILE *pt_fichier = NULL;
	pt_fichier = fopen(nomFichier, "a");
	if (pt_fichier == NULL) {
    	fprintf (stderr, "Impossible d'ouvrir %s \n", nomFichier);
   		return;
  	}
  	fprintf(pt_fichier, "%s ",texte);
  	fclose(pt_fichier);
	return;
}

void clean_fichier(char *nomFichier){
	FILE *pt_fichier = NULL;
	pt_fichier = fopen(nomFichier, "w");
	if (pt_fichier == NULL) {
    	fprintf (stderr, "Impossible d'ouvrir %s \n", nomFichier);
   		return;
  	}
  	fprintf(pt_fichier, "%s","");
  	fclose(pt_fichier);
	return;
}