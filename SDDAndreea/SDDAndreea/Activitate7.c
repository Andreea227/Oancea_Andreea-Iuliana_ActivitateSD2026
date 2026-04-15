#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;
typedef struct HashTable HashTable; 

struct Carte
{
	char* titlu;
	int nrPagini;
	float pret;
};

struct Nod {
	Carte info;
	Nod* next;
};

struct HashTable
{
	int dimensiune;
	Nod** vector;
};

Carte initCarte(const char* titlu, int nrPagini, float pret) {
	Carte c;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);

	return c;
}

void afisareCarte(Carte c) {
	printf("\nCartea %s are %d pagini si costa %.2f lei!",
		c.titlu, c.nrPagini, c.pret);
}
void afisareListaCarti(Nod* cap) {
	while (cap != NULL) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = c;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
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

int hash(int dim, int nrPagini) {
	return nrPagini % dim;
}

void inserareHashTable(HashTable tabela, Carte c) {
	int poz = hash(tabela.dimensiune, c.nrPagini);
	inserareLaSfarsit(&(tabela.vector[poz]), c);
}