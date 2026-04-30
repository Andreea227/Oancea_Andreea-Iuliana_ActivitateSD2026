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