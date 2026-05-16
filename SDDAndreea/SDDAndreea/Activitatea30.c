#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Cinema {
	char* nume;
	int nrSali;
};

Cinema creareCinema(const char* nume, int nrSali) {
	Cinema c;
	c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrSali = nrSali;
	return c;
}

struct Nod {
	Cinema info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dim;
};