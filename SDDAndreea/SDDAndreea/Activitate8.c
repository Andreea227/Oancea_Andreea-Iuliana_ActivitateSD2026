#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Angajat
{
	char* nume;
	int varsta;
	float salariu;
};

struct Nod {
	Angajat info;
	Nod* next;
};