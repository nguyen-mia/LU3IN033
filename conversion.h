#ifndef H_CONVERSION
#define H_CONVERSION

//Fonction permettant d'enlever une caratère indésrirable dans une chaine de caractère
void removeChar(char *str, char garbage);

//Fonction qui fait la conversion d'une chaine de caractere en hexadecimal vers un long int en decimal
long int hex_to_dec (char *hex);

//Fonction qui fait la conversion d'un int en decimal (= 15 max) vers un tableau de int en binaire (4 bits max)
int * decToBinary(int n);

#endif