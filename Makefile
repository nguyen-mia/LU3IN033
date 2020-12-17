EXEC=main

all : $(EXEC)

main : main.o fichier.o texte.o trame.o conversion.o
	gcc -ggdb3 -Wall -o main main.o fichier.o texte.o trame.o conversion.o -lm

main.o: main.c
	gcc -ggdb3 -Wall -o main.o -c main.c 

conversion.o: conversion.c conversion.h
	gcc -ggdb3 -Wall -o conversion.o -c conversion.c -lm

trame.o: trame.c trame.h conversion.h
	gcc -ggdb3 -Wall -o trame.o trame.c -c -lm

texte.o : texte.c texte.h conversion.h
	gcc -ggdb3 -Wall -o texte.o -c texte.c

fichier.o: fichier.c fichier.h
	gcc -ggdb3 -Wall -o fichier.o -c fichier.c 


clean:
	rm -rf *.o main
