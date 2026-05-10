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

Film citireFilmDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;
	Film f;

	aux = strtok(buffer, sep);
	f.id = atoi(aux);

	f.durata = atoi(strtok(NULL, sep));

	f.rating = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	f.titlu = malloc(strlen(aux) + 1);
	strcpy_s(f.titlu, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	f.regizor = malloc(strlen(aux) + 1);
	strcpy_s(f.regizor, strlen(aux) + 1, aux);

	f.categorie = *strtok(NULL, sep);

	return f;
}