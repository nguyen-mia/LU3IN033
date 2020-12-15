#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "conversion.h"

void removeChar(char *str, char garbage){

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

long int hex_to_dec (char *hex){
    long int decimal, val;
    int i = 0, len;

    decimal = 0;

    /* Find the length of total number of hex digit */
    len = strlen(hex);
    len--;

    // Iterate over each hex digit
    int pw =0; 
    for(i=len; i >= 0; i--)
    {
        
        /* Find the decimal representation of hex[i] */
        if(hex[i]>='0' && hex[i]<='9')
        {
            val = hex[i] - 48;
        }
        else if(hex[i]>='a' && hex[i]<='f')
        {
            val = hex[i] - 97 + 10;
        }
        else if(hex[i]>='A' && hex[i]<='F')
        {
            val = hex[i] - 65 + 10;
        }
        decimal += val * pow(16, pw);
        pw++;
    }
    return decimal;
}

int * decToBinary(int n) { 
    if (n > 15){
        return NULL;
    }
    // array to store binary number 
    int * binaryNum = (int *)malloc(sizeof(int)*4); 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = (n % 2); 
        n = n / 2; 
        i++; 
    } 
    return binaryNum;
}