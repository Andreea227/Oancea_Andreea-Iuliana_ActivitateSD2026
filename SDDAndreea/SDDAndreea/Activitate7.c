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
void afisareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++) {
		printf("\nPozitie: %d", i);
		afisareListaCarti(tabela.vector[i]);
	}
}

int calculPaginiPrimaLista(HashTable tabela) {
	int total = 0;
	Nod* cap = tabela.vector[0];

	while (cap != NULL) {
		total += cap->info.nrPagini;
		cap = cap->next;
	}

	return total;
}

void dezalocareLista(Nod** cap) {
	while (*cap != NULL) {
		free((*cap)->info.titlu);
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

int main() {
	HashTable tabela = initHashTable(4);

	inserareHashTable(tabela, initCarte("C", 200, 50));
	inserareHashTable(tabela, initCarte("Java", 350, 80));
	inserareHashTable(tabela, initCarte("Python", 150, 60));

	afisareHashTable(tabela);

	printf("\nTotal pagini prima lista: %d",
		calculPaginiPrimaLista(tabela));

	dezalocareHashTable(tabela);

	return 0;
}