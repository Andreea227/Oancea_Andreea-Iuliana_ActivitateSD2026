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

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.telefoane = malloc(sizeof(Telefon) * lungime);
	heap.nrElemente = 0;
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.telefoane[pozMin].pret > heap.telefoane[pozSt].pret) {
		pozMin = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.telefoane[pozMin].pret > heap.telefoane[pozDr].pret) {
		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {
		Telefon aux = heap.telefoane[pozMin];
		heap.telefoane[pozMin] = heap.telefoane[pozitieNod];
		heap.telefoane[pozitieNod] = aux;

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
			heap.telefoane[heap.nrElemente++] =
				citireTelefonDinFisier(f);
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
		afisareTelefon(heap.telefoane[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {

	for (int i = heap.nrElemente; i < heap.lungime; i++) {
		afisareTelefon(heap.telefoane[i]);
	}
}

Telefon extrageTelefon(Heap* heap) {

	Telefon t;
	t.id = -1;

	if (heap->nrElemente > 0) {

		t = heap->telefoane[0];

		heap->telefoane[0] =
			heap->telefoane[heap->nrElemente - 1];

		heap->telefoane[heap->nrElemente - 1] = t;

		heap->nrElemente--;

		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
	}

	return t;
}
void dezalocareHeap(Heap* heap) {

	for (int i = 0; i < heap->lungime; i++) {
		free(heap->telefoane[i].brand);
		free(heap->telefoane[i].model);
	}

	free(heap->telefoane);

	heap->telefoane = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}

int main() {

	Heap heap = citireHeapDinFisier("telefoane.txt");

	afisareHeap(heap);

	printf("Extrageri:\n");

	afisareTelefon(extrageTelefon(&heap));
	afisareTelefon(extrageTelefon(&heap));

	printf("Heap ramas:\n");
	afisareHeap(heap);

	printf("Elemente ascunse:\n");
	afiseazaHeapAscuns(heap);

	dezalocareHeap(&heap);

	return 0;
}