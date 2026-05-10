#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct StructuraFilm {
	int id;
	int durata;
	float rating;
	char* titlu;
	char* regizor;
	unsigned char categorie;
};
typedef struct StructuraFilm Film;

struct Heap {
	int lungime;
	Film* filme;
	int nrElemente;
};
typedef struct Heap Heap;
