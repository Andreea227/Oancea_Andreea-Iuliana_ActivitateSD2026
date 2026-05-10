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

void afisareProdus(Produs produs) {

	printf("Id: %d\n", produs.id);
	printf("Stoc: %d\n", produs.stoc);
	printf("Pret: %.2f\n", produs.pret);
	printf("Denumire: %s\n", produs.denumire);
	printf("Producator: %s\n", produs.producator);
	printf("Categorie: %c\n\n", produs.categorie);
}

Heap initializareHeap(int lungime) {

	Heap heap;

	heap.lungime = lungime;
	heap.produse = malloc(sizeof(Produs) * lungime);
	heap.nrElemente = 0;

	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.produse[pozMin].pret > heap.produse[pozSt].pret) {

		pozMin = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.produse[pozMin].pret > heap.produse[pozDr].pret) {

		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {

		Produs aux = heap.produse[pozMin];
		heap.produse[pozMin] = heap.produse[pozitieNod];
		heap.produse[pozitieNod] = aux;

		if (pozMin < (heap.nrElemente - 2) / 2) {
			filtreazaHeap(heap, pozMin);
		}
	}
}

Heap citireHeapDinFisier(const char* numeFisier) {

	Heap heap = initializareHeap(10);

	FILE* f = fopen(numeFisier, "r");

	if (f) {

		while (!feof(f)) {
			heap.produse[heap.nrElemente++] =
				citireProdusDinFisier(f);
		}
	}

	fclose(f);

	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}

	return heap;
}

void afisareHeap(Heap heap) {

	for (int i = 0; i < heap.nrElemente; i++) {
		afisareProdus(heap.produse[i]);
	}
}

void afiseazaElementeAscunse(Heap heap) {

	for (int i = heap.nrElemente; i < heap.lungime; i++) {
		afisareProdus(heap.produse[i]);
	}
}

Produs extrageProdus(Heap* heap) {

	Produs produs;
	produs.id = -1;

	if (heap->nrElemente > 0) {

		produs = heap->produse[0];

		heap->produse[0] =
			heap->produse[heap->nrElemente - 1];

		heap->produse[heap->nrElemente - 1] = produs;

		heap->nrElemente--;

		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
	}

	return produs;
}

void dezalocareHeap(Heap* heap) {

	for (int i = 0; i < heap->lungime; i++) {

		free(heap->produse[i].denumire);
		free(heap->produse[i].producator);
	}

	free(heap->produse);

	heap->produse = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}

int main() {

	Heap heap = citireHeapDinFisier("produse.txt");

	afisareHeap(heap);

	printf("Extragere produse:\n");

	afisareProdus(extrageProdus(&heap));
	afisareProdus(extrageProdus(&heap));

	printf("Heap ramas:\n");
	afisareHeap(heap);

	dezalocareHeap(&heap);

	return 0;
}