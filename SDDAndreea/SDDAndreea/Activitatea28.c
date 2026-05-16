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
void filtreazaHeap(Heap heap, int poz) {
	int st = 2 * poz + 1;
	int dr = 2 * poz + 2;
	int min = poz;

	if (st < heap.nrElemente && heap.prajituri[st].pret < heap.prajituri[min].pret)
		min = st;

	if (dr < heap.nrElemente && heap.prajituri[dr].pret < heap.prajituri[min].pret)
		min = dr;

	if (min != poz) {
		Prajitura aux = heap.prajituri[min];
		heap.prajituri[min] = heap.prajituri[poz];
		heap.prajituri[poz] = aux;

		if (min < (heap.nrElemente - 2) / 2)
			filtreazaHeap(heap, min);
	}
}
Heap citireHeapPrajituriDinFisier(const char* numeFisier) {
	Heap h = initializareHeap(10);
	FILE* f = fopen(numeFisier, "r");

	if (f) {
		while (!feof(f)) {
			h.prajituri[h.nrElemente++] = citirePrajituraDinFisier(f);
		}
	}
	fclose(f);

	for (int i = (h.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(h, i);
	}

	return h;
}
void afisareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		afisarePrajitura(h.prajituri[i]);
	}
}
void afisareHeapAscuns(Heap h) {
	for (int i = h.nrElemente; i < h.capacitate; i++) {
		afisarePrajitura(h.prajituri[i]);
	}
}
Prajitura extragePrajitura(Heap* h) {
	Prajitura p;
	p.id = -1;

	if (h->nrElemente > 0) {
		p = h->prajituri[0];

		h->prajituri[0] = h->prajituri[h->nrElemente - 1];
		h->prajituri[h->nrElemente - 1] = p;
		h->nrElemente--;

		for (int i = (h->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*h, i);
		}
	}
	return p;
}
