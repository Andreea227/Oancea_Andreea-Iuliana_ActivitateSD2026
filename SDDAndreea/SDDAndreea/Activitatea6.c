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
void inserareHashTable(HashTable tabela, Produs p) {
	if (tabela.dimensiune > 0) {
		int pozitie = hash(tabela.dimensiune, p.stoc);
		if (pozitie >= 0 && pozitie < tabela.dimensiune) {
			inserareLaSfarsit(&(tabela.vector[pozitie]), p);
		}
	}
}

void afisareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++) {
		printf("\nPozitie: %d", i);
		afisareListaProduse(tabela.vector[i]);
	}
}

int calculStocPrimaLista(HashTable tabela) {
	int total = 0;
	Nod* capLista0 = tabela.vector[0];
	while (capLista0 != NULL) {
		total += capLista0->info.stoc;
		capLista0 = capLista0->next;
	}

	return total;
}

void dezalocareLista(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.denumire);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

void dezalocareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++)
	{
		dezalocareLista(&(tabela.vector[i]));
	}
	free(tabela.vector);
}
