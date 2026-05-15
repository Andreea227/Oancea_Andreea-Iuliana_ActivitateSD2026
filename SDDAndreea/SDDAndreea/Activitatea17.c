#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCont {
	int id;
	int sold;
	float dobanda;
	char* titular;
	char* banca;
	unsigned char tip;
};
typedef struct StructuraCont ContBancar;

struct Heap {
	int lungime;
	ContBancar* conturi;
	int nrElemente;
};
typedef struct Heap Heap;

ContBancar citireContDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);

	char* aux;
	ContBancar c;

	aux = strtok(buffer, sep);
	c.id = atoi(aux);

	c.sold = atoi(strtok(NULL, sep));

	c.dobanda = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	c.titular = malloc(strlen(aux) + 1);
	strcpy_s(c.titular, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	c.banca = malloc(strlen(aux) + 1);
	strcpy_s(c.banca, strlen(aux) + 1, aux);

	c.tip = *strtok(NULL, sep);

	return c;
}