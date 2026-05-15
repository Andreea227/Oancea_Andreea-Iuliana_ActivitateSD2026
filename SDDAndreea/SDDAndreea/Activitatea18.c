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