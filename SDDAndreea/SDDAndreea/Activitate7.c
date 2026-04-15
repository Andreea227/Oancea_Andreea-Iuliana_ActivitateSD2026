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