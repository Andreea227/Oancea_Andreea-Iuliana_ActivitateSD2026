#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct StructuraStudent {
	int id;
	int varsta;
	float medie;
	char* nume;
	char* facultate;
	unsigned char grupa;
};
typedef struct StructuraStudent Student;

struct Heap {
	int lungime;
	Student* studenti;
	int nrElemente;
};
typedef struct Heap Heap;

Student citireStudentDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;
	Student s;

	aux = strtok(buffer, sep);
	s.id = atoi(aux);

	s.varsta = atoi(strtok(NULL, sep));

	s.medie = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	s.nume = malloc(strlen(aux) + 1);
	strcpy_s(s.nume, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	s.facultate = malloc(strlen(aux) + 1);
	strcpy_s(s.facultate, strlen(aux) + 1, aux);

	s.grupa = *strtok(NULL, sep);

	return s;
}

void afisareStudent(Student student) {

	printf("Id: %d\n", student.id);
	printf("Varsta: %d\n", student.varsta);
	printf("Medie: %.2f\n", student.medie);
	printf("Nume: %s\n", student.nume);
	printf("Facultate: %s\n", student.facultate);
	printf("Grupa: %c\n\n", student.grupa);
}

Heap initializareHeap(int lungime) {

	Heap heap;

	heap.lungime = lungime;
	heap.studenti = malloc(sizeof(Student) * lungime);
	heap.nrElemente = 0;

	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.studenti[pozMin].medie > heap.studenti[pozSt].medie) {

		pozMin = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.studenti[pozMin].medie > heap.studenti[pozDr].medie) {

		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {

		Student aux = heap.studenti[pozMin];
		heap.studenti[pozMin] = heap.studenti[pozitieNod];
		heap.studenti[pozitieNod] = aux;

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
			heap.studenti[heap.nrElemente++] =
				citireStudentDinFisier(f);
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
		afisareStudent(heap.studenti[i]);
	}
}

void afiseazaElementeAscunse(Heap heap) {

	for (int i = heap.nrElemente; i < heap.lungime; i++) {
		afisareStudent(heap.studenti[i]);
	}
}

Student extrageStudent(Heap* heap) {

	Student student;
	student.id = -1;

	if (heap->nrElemente > 0) {

		student = heap->studenti[0];

		heap->studenti[0] =
			heap->studenti[heap->nrElemente - 1];

		heap->studenti[heap->nrElemente - 1] = student;

		heap->nrElemente--;

		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
	}

	return student;
}

void dezalocareHeap(Heap* heap) {

	for (int i = 0; i < heap->lungime; i++) {

		free(heap->studenti[i].nume);
		free(heap->studenti[i].facultate);
	}

	free(heap->studenti);

	heap->studenti = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}