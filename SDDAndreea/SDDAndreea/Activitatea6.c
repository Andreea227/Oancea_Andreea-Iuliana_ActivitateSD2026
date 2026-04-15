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


