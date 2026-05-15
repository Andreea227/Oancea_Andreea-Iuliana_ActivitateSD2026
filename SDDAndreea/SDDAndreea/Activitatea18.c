#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraLaptop {
	int id;
	int ram;
	float pret;
	char* brand;
	char* procesor;
	unsigned char generatie;
};
typedef struct StructuraLaptop Laptop;

struct Heap {
	int lungime;
	Laptop* laptopuri;
	int nrElemente;
};
typedef struct Heap Heap;

Laptop citireLaptopDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);

	char* aux;
	Laptop l;

	aux = strtok(buffer, sep);
	l.id = atoi(aux);

	l.ram = atoi(strtok(NULL, sep));

	l.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	l.brand = malloc(strlen(aux) + 1);
	strcpy_s(l.brand, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	l.procesor = malloc(strlen(aux) + 1);
	strcpy_s(l.procesor, strlen(aux) + 1, aux);

	l.generatie = *strtok(NULL, sep);

	return l;
}

void afisareLaptop(Laptop l) {
	printf("Id: %d\n", l.id);
	printf("RAM: %d\n", l.ram);
	printf("Pret: %.2f\n", l.pret);
	printf("Brand: %s\n", l.brand);
	printf("Procesor: %s\n", l.procesor);
	printf("Generatie: %c\n\n", l.generatie);
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.laptopuri = malloc(sizeof(Laptop) * lungime);
	heap.nrElemente = 0;
	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.laptopuri[pozMin].pret > heap.laptopuri[pozSt].pret) {
		pozMin = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.laptopuri[pozMin].pret > heap.laptopuri[pozDr].pret) {
		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {
		Laptop aux = heap.laptopuri[pozMin];
		heap.laptopuri[pozMin] = heap.laptopuri[pozitieNod];
		heap.laptopuri[pozitieNod] = aux;

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
			heap.laptopuri[heap.nrElemente++] =
				citireLaptopDinFisier(f);
		}
	}

	fclose(f);

	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}

	return heap;
}