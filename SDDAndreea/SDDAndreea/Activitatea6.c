#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Produs Produs;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Produs
{
	char* denumire;
	int stoc;
	float pret;
};

struct Nod {
	Produs info;
	Nod* next;
};

struct HashTable
{
	int dimensiune;
	Nod** vector;
};

Produs initProdus(const char* denumire, int stoc,
	float pret) {
	Produs p;
	p.stoc = stoc;
	p.pret = pret;
	p.denumire = (char*)malloc(sizeof(char)
		* (strlen(denumire) + 1));
	strcpy(p.denumire, denumire);

	return p;
}

void afisareProdus(Produs p) {
	printf("\nProdusul %s are %d bucati in stoc, iar pretul este %.2f lei!",
		p.denumire, p.stoc, p.pret);
}

void afisareListaProduse(Nod* cap) {
	while (cap != NULL) {
		afisareProdus(cap->info);
		cap = cap->next;
	}
}
void inserareLaSfarsit(Nod** cap, Produs p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = p;

	if (*cap == NULL) {
		*cap = nou;
	}
	else
	{
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}
HashTable initHashTable(int size) {
	HashTable tabela;
	tabela.dimensiune = size;
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * size);
	for (int i = 0; i < size; i++) {
		tabela.vector[i] = NULL;
	}

	return tabela;
}
int hash(int dim, int stoc) {
	return stoc % dim;
}