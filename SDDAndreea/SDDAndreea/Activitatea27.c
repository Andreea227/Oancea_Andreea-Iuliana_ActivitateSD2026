#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraZbor {
	int id;
	int durata;
	float intarziere;
	char* destinatie;
	char* companie;
	unsigned char terminal;
};
typedef struct StructuraZbor Zbor;

struct Heap {
	int capacitate;
	Zbor* zboruri;
	int nrElemente;
};
typedef struct Heap Heap;
Zbor citireZborDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);

	char* aux;
	Zbor z;

	aux = strtok(buffer, sep);
	z.id = atoi(aux);

	z.durata = atoi(strtok(NULL, sep));

	z.intarziere = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	z.destinatie = malloc(strlen(aux) + 1);
	strcpy(z.destinatie, aux);

	aux = strtok(NULL, sep);
	z.companie = malloc(strlen(aux) + 1);
	strcpy(z.companie, aux);

	z.terminal = *strtok(NULL, sep);

	return z;
}
void afisareZbor(Zbor z) {
	printf("Id: %d\n", z.id);
	printf("Durata: %d\n", z.durata);
	printf("Intarziere: %.2f\n", z.intarziere);
	printf("Destinatie: %s\n", z.destinatie);
	printf("Companie: %s\n", z.companie);
	printf("Terminal: %c\n\n", z.terminal);
}