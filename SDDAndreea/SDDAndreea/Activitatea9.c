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