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
	unsigned char an;
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

	s.an = *strtok(NULL, sep);

	return s;
}
void afisareStudent(Student s) {
	printf("Id: %d\n", s.id);
	printf("Varsta: %d\n", s.varsta);
	printf("Medie: %.2f\n", s.medie);
	printf("Nume: %s\n", s.nume);
	printf("Facultate: %s\n", s.facultate);
	printf("An: %c\n\n", s.an);
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
	int pozMax = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.studenti[pozMax].medie < heap.studenti[pozSt].medie) {
		pozMax = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.studenti[pozMax].medie < heap.studenti[pozDr].medie) {
		pozMax = pozDr;
	}

	if (pozMax != pozitieNod) {
		Student aux = heap.studenti[pozMax];
		heap.studenti[pozMax] = heap.studenti[pozitieNod];
		heap.studenti[pozitieNod] = aux;

		if (pozMax < (heap.nrElemente - 2) / 2) {
			filtreazaHeap(heap, pozMax);
		}
	}
}