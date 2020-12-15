#ifndef H_FICHIER
#define H_FICHIER

//Compter le nombre de lignes dans un fichier .txt
int compter_lignes(char *nomFichier); 

//Lire un fichier .txt
char * lire_fichier(char *nomFichier, int * p_nbL);

//Ecrire dans un fichier .txt
void ecrire_fichier(char *nomFichier, char * texte);

//Ecrire un octet dans un fichier .txt
void ecrire_fichier_octet(char *nomFichier, char * texte);

//Tout effacer un fichier .txt
void clean_fichier(char *nomFichier);

#endif