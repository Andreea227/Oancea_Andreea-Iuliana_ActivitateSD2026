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

