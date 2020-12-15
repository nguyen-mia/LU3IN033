#ifndef H_TEXTE
#define H_TEXTE


//Verification d'un octet extrait de la trame, ecrit dans une chaine de caractere 
//Retourne 1 si l'octet est bien formate, 0 sinon
int verification_octet(char ** octet, int cpt_mot_ligne);

//Verification du offset passe en pararametre
//Retourne 1 si l'offset correspond bien au decalage, 0 sinon
int verification_offset(char * offset, int nb_mot_lprec);

//Verification d'une ligne de trame ecrit dans une chaine de caractere 
int verification_ligne(char * ligne, int * pcpt_mot, int cpt_ligne);

//Verification d'une trame 
void verification_trame(char * trame_init, int nbL);


#endif