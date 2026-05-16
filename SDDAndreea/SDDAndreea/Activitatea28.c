#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraPrajitura {
	int id;
	int calorii;
	float pret;
	char* nume;
	char* cofetarie;
	unsigned char tip;
};
typedef struct StructuraPrajitura Prajitura;

struct Heap {
	int capacitate;
	Prajitura* prajituri;
	int nrElemente;
};
typedef struct Heap Heap;
Prajitura citirePrajituraDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);

	char* aux;
	Prajitura p;

	aux = strtok(buffer, sep);
	p.id = atoi(aux);

	p.calorii = atoi(strtok(NULL, sep));

	p.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	p.nume = malloc(strlen(aux) + 1);
	strcpy(p.nume, aux);

	aux = strtok(NULL, sep);
	p.cofetarie = malloc(strlen(aux) + 1);
	strcpy(p.cofetarie, aux);

	p.tip = *strtok(NULL, sep);

	return p;
}
void afisarePrajitura(Prajitura p) {
	printf("Id: %d\n", p.id);
	printf("Calorii: %d\n", p.calorii);
	printf("Pret: %.2f\n", p.pret);
	printf("Nume: %s\n", p.nume);
	printf("Cofetarie: %s\n", p.cofetarie);
	printf("Tip: %c\n\n", p.tip);
}
Heap initializareHeap(int capacitate) {
	Heap h;
	h.capacitate = capacitate;
	h.prajituri = malloc(sizeof(Prajitura) * capacitate);
	h.nrElemente = 0;
	return h;
}