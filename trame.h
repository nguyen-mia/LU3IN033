#ifndef H_TRAME
#define H_TRAME


//Fonction permettant d'afficher une adresse IP ou MAC selon la longueur len_addr
void affiche_addr(char * addr_hex, int len_addr);

//Fonction permettant de lire et décoder la couche (7) pour le protocol HTTP 
void HTTP(char * trame);

//Fonction permettant de lire et décoder la couche (4) pour le protocol TCP 
void TCP(char * trame);

//Fonction permettant de lire et décoder la couche (3) pour le protocol IPv4 
void IPv4(char * trame);

//Fonction permettant de lire et décoder la couche (3) - Ethernet
void ethernet(char * trame);

#endif