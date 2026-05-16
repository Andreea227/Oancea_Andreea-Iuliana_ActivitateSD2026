#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraPacient {
	int id;
	int varsta;
	float gravitate;
	char* nume;
	char* diagnostic;
	unsigned char sectie;
};
typedef struct StructuraPacient Pacient;

struct Heap {
	int capacitate;
	Pacient* pacienti;
	int nrElemente;
};
typedef struct Heap Heap;
Pacient citirePacientDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);

	char* aux;
	Pacient p;

	aux = strtok(buffer, sep);
	p.id = atoi(aux);

	p.varsta = atoi(strtok(NULL, sep));

	p.gravitate = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	p.nume = malloc(strlen(aux) + 1);
	strcpy(p.nume, aux);

	aux = strtok(NULL, sep);
	p.diagnostic = malloc(strlen(aux) + 1);
	strcpy(p.diagnostic, aux);

	p.sectie = *strtok(NULL, sep);

	return p;
}
void afisarePacient(Pacient p) {
	printf("Id: %d\n", p.id);
	printf("Varsta: %d\n", p.varsta);
	printf("Gravitate: %.2f\n", p.gravitate);
	printf("Nume: %s\n", p.nume);
	printf("Diagnostic: %s\n", p.diagnostic);
	printf("Sectie: %c\n\n", p.sectie);
}
Heap initializareHeap(int capacitate) {
	Heap h;
	h.capacitate = capacitate;
	h.pacienti = malloc(sizeof(Pacient) * capacitate);
	h.nrElemente = 0;
	return h;
}
void filtreazaHeap(Heap heap, int poz) {
	int st = 2 * poz + 1;
	int dr = 2 * poz + 2;
	int min = poz;

	if (st < heap.nrElemente && heap.pacienti[st].gravitate < heap.pacienti[min].gravitate)
		min = st;

	if (dr < heap.nrElemente && heap.pacienti[dr].gravitate < heap.pacienti[min].gravitate)
		min = dr;

	if (min != poz) {
		Pacient aux = heap.pacienti[min];
		heap.pacienti[min] = heap.pacienti[poz];
		heap.pacienti[poz] = aux;

		if (min < (heap.nrElemente - 2) / 2)
			filtreazaHeap(heap, min);
	}
}
Heap citireHeapPacientiDinFisier(const char* numeFisier) {
	Heap h = initializareHeap(10);
	FILE* f = fopen(numeFisier, "r");

	if (f) {
		while (!feof(f)) {
			h.pacienti[h.nrElemente++] = citirePacientDinFisier(f);
		}
	}
	fclose(f);

	for (int i = (h.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(h, i);
	}

	return h;
}
