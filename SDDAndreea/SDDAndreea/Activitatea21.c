#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraTara {
	int id;
	int populatie;
	float pib;
	char* numeTara;
	char* capitala;
	unsigned char continent;
};
typedef struct StructuraTara Tara;

struct Nod {
	Tara info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

Tara citireTaraDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);

	char* aux;
	Tara t1;

	aux = strtok(buffer, sep);
	t1.id = atoi(aux);

	t1.populatie = atoi(strtok(NULL, sep));

	t1.pib = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	t1.numeTara = malloc(strlen(aux) + 1);
	strcpy_s(t1.numeTara, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	t1.capitala = malloc(strlen(aux) + 1);
	strcpy_s(t1.capitala, strlen(aux) + 1, aux);

	t1.continent = *strtok(NULL, sep);

	return t1;
}