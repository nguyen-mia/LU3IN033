#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fichier.h"
#include "texte.h"
#include "conversion.h"

#define TAILLE_MAX 5000


int verification_octet(char ** octet){
    int i = 0, len;
    char * octet2 = *octet;
    len = strlen(*octet);
    int res = 1;
    if(len < 2){
        return -1;
    }
    if (len == 2){ //pas de `\n' dans l'octet
    	len--;
	    for(i=len; i >= 0; i--){
	        if((octet2[i]>='0' && octet2[i]<='9') || (octet2[i]>='a' && octet2[i]<='f') || (octet2[i]>='A' && octet2[i]<='F')) {
	        	res = 1;
	        }else{
                return 0;
            }
	    }
    }if (len == 3){ //l'octet de fin de ligne
        if((octet2[2]>='0' && octet2[2]<='9') || (octet2[2]>='a' && octet2[2]<='f') || (octet2[2]>='A' && octet2[2]<='F')) {
           return 0;
        }
        if((octet2[2] == '\n') || (octet2[2] == '\r')){
           octet2[2] = '\0';
        }
	    for(i=1; i >= 0; i--){
	        if((octet2[i]>='0' && octet2[i]<='9') || (octet2[i]>='a' && octet2[i]<='f') || (octet2[i]>='A' && octet2[i]<='F')) {
	        	res = 1;
	        }else{
                return 0;
            }
	    }
    }if(len > 3){
        return 0;
    }
    return res;
}

int verification_offset(char * offset, int nb_mot_lprec){
	if(strlen(offset) < 2){
        return -1;
    }
    int offset_dec = hex_to_dec(offset);
    if(offset_dec == 0){
        return 1;
    }
	return (offset_dec == nb_mot_lprec);	
}

int verification_ligne(char * ligne, int * pcpt_mot, int cpt_ligne){
	char * nomFichierW = "TrameBrute.txt";
	char *del,*trame_tmp,*mot;
	int cpt_mot = *(pcpt_mot); //cpt de mots total dans la trame
	int nb_mot_lprec;
	int v_off; 
    int v_oct;
    int cpt_mot_vide = 0; //espaces séparant l'offset et les octets ainsi que les octets et les valeurs textuelles

	del = trame_tmp = strdup(ligne);

	while( (mot = strsep(&trame_tmp," ")) != NULL ){
        nb_mot_lprec = cpt_mot;
        //on verifie l'offset d'abord
        if(cpt_mot_vide > 2){ //début des valeurs textuelles à la fin de ligne
            break;
        }
        if (cpt_mot == *(pcpt_mot)){
        	v_off = verification_offset(mot, nb_mot_lprec); 
        	if (!v_off){ //si l'offset est faux par rapport aux lignes précédentes
                return 0; //on sort de la boucle et retourne 0
        	}else{
                if((v_off != -1) && (hex_to_dec(mot) == 0)){
                    cpt_mot = 0;
                    *(pcpt_mot) = 0;
                    ecrire_fichier(nomFichierW, "\r");
                }
        		cpt_mot++;  
        	}
        }
        else{ //ensuite on verifie chaque octet
        	v_oct = verification_octet(&mot);
        	if (v_oct != -1){
                if(v_oct == 1){ //octet bien formaté
                    ecrire_fichier_octet(nomFichierW, mot);
                    cpt_mot++; 
                }else{ // octet mal formaté
                    removeChar(mot, '\n');
                    removeChar(mot, '\r');
                    printf("Erreur d'octet à la ligne %d, %s ignoré \n", cpt_ligne, mot);
                }
            }else{ //mots vides (lorsqu'on a plusieurs espaces d'affilés)
                cpt_mot_vide++;
            }
        }      
    }
    *(pcpt_mot) = cpt_mot - 1;
    free(del);
    return 1;
}
//fonction permet de verifier que la trame donnee est bien formatee et ecrit dans le fichier TrameBrute.txt la trame brute (sans offset)
void verification_trame(char * trame_init, int nbL){
	int cpt_mot = 0;
    int cpt_ligne = 1;
	//parcourt de notre trame 
	char *del,*trame_tmp,*ligne;
    del = trame_tmp = strdup(trame_init);
    int cpt_err = 0;
    //identification d'une ligne
    printf("\n----------------------------- WARNING / ERROR -----------------------------\n");
    while( (ligne = strsep(&trame_tmp,"\n")) != NULL) {
        int res = verification_ligne(ligne, &cpt_mot, cpt_ligne);
        if(!res && cpt_ligne < nbL){
            removeChar(ligne, '\n');
            removeChar(ligne, '\r');
            printf("Erreur d'offset, ligne %d ignorée \n", cpt_ligne);
            cpt_err++;
        }
        cpt_ligne++;
    }
    if(cpt_err){
        printf("Veuillez vérifier les trames données en entrée\n");
    }
    free(del);
	return; 
}

