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

int functieHash(int dim, const char* nume) {
	return strlen(nume) % dim;
}
HashTable creareTabela(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dim);

	for (int i = 0; i < dim; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}
void inserareInLista(Nod* cap, Cinema c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;

	while (cap->next) {
		cap = cap->next;
	}
	cap->next = nou;
}
void inserareCinemaInTabela(Cinema c, HashTable h) {
	int cod = functieHash(h.dim, c.nume);

	if (h.vector[cod] == NULL) {
		h.vector[cod] = (Nod*)malloc(sizeof(Nod));
		h.vector[cod]->info = c;
		h.vector[cod]->next = NULL;
	}
	else {
		inserareInLista(h.vector[cod], c);
	}
}
void afisareCinema(Cinema c) {
	printf("Cinema %s are %d sali\n", c.nume, c.nrSali);
}

void afisareLista(Nod* cap) {
	while (cap) {
		afisareCinema(cap->info);
		cap = cap->next;
	}
}
