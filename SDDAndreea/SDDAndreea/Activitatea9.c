#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Apartament Apartament;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Apartament
{
	char* adresa;
	int suprafata;
	float pret;
};

struct Nod {
	Apartament info;
	Nod* next;
};

struct HashTable
{
	int dimensiune;
	Nod** vector;
};

Apartament initApartament(const char* adresa, int suprafata, float pret) {
	Apartament a;
	a.suprafata = suprafata;
	a.pret = pret;
	a.adresa = (char*)malloc(sizeof(char) * (strlen(adresa) + 1));
	strcpy(a.adresa, adresa);

	return a;
}

void afisareApartament(Apartament a) {
	printf("\nApartamentul de la %s are %d mp si costa %.2f euro!",
		a.adresa, a.suprafata, a.pret);
}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		afisareApartament(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Apartament a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->info = a;

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

HashTable initHashTable(int dim) {
	HashTable tabela;
	tabela.dimensiune = dim;
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * dim);

	for (int i = 0; i < dim; i++) {
		tabela.vector[i] = NULL;
	}

	return tabela;
}

int hash(int dim, int suprafata) {
	return suprafata % dim;
}

void inserareHashTable(HashTable tabela, Apartament a) {
	int poz = hash(tabela.dimensiune, a.suprafata);
	inserareLaSfarsit(&(tabela.vector[poz]), a);
}

void afisareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++) {
		printf("\nPozitie: %d", i);
		afisareLista(tabela.vector[i]);
	}
}

int calculSuprafataPrimaLista(HashTable tabela) {
	int total = 0;
	Nod* cap = tabela.vector[0];

	while (cap != NULL) {
		total += cap->info.suprafata;
		cap = cap->next;
	}

	return total;
}

void dezalocareLista(Nod** cap) {
	while (*cap != NULL) {
		free((*cap)->info.adresa);
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

void dezalocareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++) {
		dezalocareLista(&(tabela.vector[i]));
	}
	free(tabela.vector);
}