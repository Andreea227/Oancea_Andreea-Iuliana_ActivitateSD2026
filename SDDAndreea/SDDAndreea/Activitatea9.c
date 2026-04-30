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