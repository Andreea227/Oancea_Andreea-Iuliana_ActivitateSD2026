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