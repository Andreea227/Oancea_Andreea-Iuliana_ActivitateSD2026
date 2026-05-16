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