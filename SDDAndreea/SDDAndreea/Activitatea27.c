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

Heap initializareHeap(int capacitate) {
	Heap h;
	h.capacitate = capacitate;
	h.zboruri = malloc(sizeof(Zbor) * capacitate);
	h.nrElemente = 0;
	return h;
}
void filtreazaHeap(Heap heap, int poz) {
	int st = 2 * poz + 1;
	int dr = 2 * poz + 2;
	int min = poz;

	if (st < heap.nrElemente && heap.zboruri[st].intarziere < heap.zboruri[min].intarziere)
		min = st;

	if (dr < heap.nrElemente && heap.zboruri[dr].intarziere < heap.zboruri[min].intarziere)
		min = dr;

	if (min != poz) {
		Zbor aux = heap.zboruri[min];
		heap.zboruri[min] = heap.zboruri[poz];
		heap.zboruri[poz] = aux;

		if (min < (heap.nrElemente - 2) / 2)
			filtreazaHeap(heap, min);
	}
}
Heap citireHeapZboruriDinFisier(const char* numeFisier) {
	Heap h = initializareHeap(10);
	FILE* f = fopen(numeFisier, "r");

	if (f) {
		while (!feof(f)) {
			h.zboruri[h.nrElemente++] = citireZborDinFisier(f);
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
		afisareZbor(h.zboruri[i]);
	}
}
void afisareHeapAscuns(Heap h) {
	for (int i = h.nrElemente; i < h.capacitate; i++) {
		afisareZbor(h.zboruri[i]);
	}
}
Zbor extrageZbor(Heap* h) {
	Zbor z;
	z.id = -1;

	if (h->nrElemente > 0) {
		z = h->zboruri[0];

		h->zboruri[0] = h->zboruri[h->nrElemente - 1];
		h->zboruri[h->nrElemente - 1] = z;
		h->nrElemente--;

		for (int i = (h->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*h, i);
		}
	}
	return z;
}
void dezalocareHeap(Heap* h) {
	for (int i = 0; i < h->capacitate; i++) {
		free(h->zboruri[i].destinatie);
		free(h->zboruri[i].companie);
	}
	free(h->zboruri);

	h->zboruri = NULL;
	h->capacitate = 0;
	h->nrElemente = 0;
}
char* getNextFlight(Heap h) {
	if (h.nrElemente > 0)
		return h.zboruri[0].destinatie;
	return "";
}
