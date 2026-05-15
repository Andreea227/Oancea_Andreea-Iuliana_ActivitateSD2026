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

void afisareCont(ContBancar c) {
	printf("Id: %d\n", c.id);
	printf("Sold: %d\n", c.sold);
	printf("Dobanda: %.2f\n", c.dobanda);
	printf("Titular: %s\n", c.titular);
	printf("Banca: %s\n", c.banca);
	printf("Tip: %c\n\n", c.tip);
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.conturi = malloc(sizeof(ContBancar) * lungime);
	heap.nrElemente = 0;
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.conturi[pozMin].sold > heap.conturi[pozSt].sold) {
		pozMin = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.conturi[pozMin].sold > heap.conturi[pozDr].sold) {
		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {
		ContBancar aux = heap.conturi[pozMin];
		heap.conturi[pozMin] = heap.conturi[pozitieNod];
		heap.conturi[pozitieNod] = aux;

		if (pozMin < (heap.nrElemente - 2) / 2) {
			filtreazaHeap(heap, pozMin);
		}
	}
}