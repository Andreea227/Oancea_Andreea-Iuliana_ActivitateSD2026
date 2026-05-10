#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct StructuraAngajat {
	int id;
	int varsta;
	float salariu;
	char* nume;
	char* departament;
	unsigned char nivel;
};
typedef struct StructuraAngajat Angajat;

struct Heap {
	int lungime;
	Angajat* angajati;
	int nrElemente;
};
typedef struct Heap Heap;

Angajat citireAngajatDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;
	Angajat a;

	aux = strtok(buffer, sep);
	a.id = atoi(aux);

	a.varsta = atoi(strtok(NULL, sep));

	a.salariu = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	a.nume = malloc(strlen(aux) + 1);
	strcpy_s(a.nume, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	a.departament = malloc(strlen(aux) + 1);
	strcpy_s(a.departament, strlen(aux) + 1, aux);

	a.nivel = *strtok(NULL, sep);

	return a;
}

void afisareAngajat(Angajat angajat) {

	printf("Id: %d\n", angajat.id);
	printf("Varsta: %d\n", angajat.varsta);
	printf("Salariu: %.2f\n", angajat.salariu);
	printf("Nume: %s\n", angajat.nume);
	printf("Departament: %s\n", angajat.departament);
	printf("Nivel: %c\n\n", angajat.nivel);
}

Heap initializareHeap(int lungime) {

	Heap heap;

	heap.lungime = lungime;
	heap.angajati = malloc(sizeof(Angajat) * lungime);
	heap.nrElemente = 0;

	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.angajati[pozMin].salariu > heap.angajati[pozSt].salariu) {

		pozMin = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.angajati[pozMin].salariu > heap.angajati[pozDr].salariu) {

		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {

		Angajat aux = heap.angajati[pozMin];
		heap.angajati[pozMin] = heap.angajati[pozitieNod];
		heap.angajati[pozitieNod] = aux;

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
			heap.angajati[heap.nrElemente++] =
				citireAngajatDinFisier(f);
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
		afisareAngajat(heap.angajati[i]);
	}
}

void afiseazaElementeAscunse(Heap heap) {

	for (int i = heap.nrElemente; i < heap.lungime; i++) {
		afisareAngajat(heap.angajati[i]);
	}
}

Angajat extrageAngajat(Heap* heap) {

	Angajat angajat;
	angajat.id = -1;

	if (heap->nrElemente > 0) {

		angajat = heap->angajati[0];

		heap->angajati[0] =
			heap->angajati[heap->nrElemente - 1];

		heap->angajati[heap->nrElemente - 1] = angajat;

		heap->nrElemente--;

		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
	}

	return angajat;
}

void dezalocareHeap(Heap* heap) {

	for (int i = 0; i < heap->lungime; i++) {

		free(heap->angajati[i].nume);
		free(heap->angajati[i].departament);
	}

	free(heap->angajati);

	heap->angajati = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}

int main() {

	Heap heap = citireHeapDinFisier("angajati.txt");

	afisareHeap(heap);

	printf("Extragere angajati:\n");

	afisareAngajat(extrageAngajat(&heap));
	afisareAngajat(extrageAngajat(&heap));

	printf("Heap ramas:\n");
	afisareHeap(heap);

	dezalocareHeap(&heap);

	return 0;
}