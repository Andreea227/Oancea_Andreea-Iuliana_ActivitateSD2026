#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraTelefon {
	int id;
	int stoc;
	float pret;
	char* brand;
	char* model;
	unsigned char memorie;
};
typedef struct StructuraTelefon Telefon;

struct Heap {
	int lungime;
	Telefon* telefoane;
	int nrElemente;
};
typedef struct Heap Heap;

Telefon citireTelefonDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);

	char* aux;
	Telefon t;

	aux = strtok(buffer, sep);
	t.id = atoi(aux);

	t.stoc = atoi(strtok(NULL, sep));

	t.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	t.brand = malloc(strlen(aux) + 1);
	strcpy_s(t.brand, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	t.model = malloc(strlen(aux) + 1);
	strcpy_s(t.model, strlen(aux) + 1, aux);

	t.memorie = *strtok(NULL, sep);

	return t;
}

void afisareTelefon(Telefon t) {
	printf("Id: %d\n", t.id);
	printf("Stoc: %d\n", t.stoc);
	printf("Pret: %.2f\n", t.pret);
	printf("Brand: %s\n", t.brand);
	printf("Model: %s\n", t.model);
	printf("Memorie: %c\n\n", t.memorie);
}