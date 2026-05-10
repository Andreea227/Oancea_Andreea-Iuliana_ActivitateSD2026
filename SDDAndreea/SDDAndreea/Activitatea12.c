#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct StructuraProdus {
	int id;
	int stoc;
	float pret;
	char* denumire;
	char* producator;
	unsigned char categorie;
};
typedef struct StructuraProdus Produs;

struct Heap {
	int lungime;
	Produs* produse;
	int nrElemente;
};
typedef struct Heap Heap;

Produs citireProdusDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;
	Produs p;

	aux = strtok(buffer, sep);
	p.id = atoi(aux);

	p.stoc = atoi(strtok(NULL, sep));

	p.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	p.denumire = malloc(strlen(aux) + 1);
	strcpy_s(p.denumire, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	p.producator = malloc(strlen(aux) + 1);
	strcpy_s(p.producator, strlen(aux) + 1, aux);

	p.categorie = *strtok(NULL, sep);

	return p;
}