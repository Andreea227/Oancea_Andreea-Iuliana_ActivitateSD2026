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

struct HashTable
{
	int dimensiune;
	Nod** vector;
};

Angajat initAngajat(const char* nume, int varsta, float salariu) {
	Angajat a;
	a.varsta = varsta;
	a.salariu = salariu;
	a.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(a.nume, nume);

	return a;
}

void afisareAngajat(Angajat a) {
	printf("\nAngajatul %s are %d ani si salariul %.2f lei!",
		a.nume, a.varsta, a.salariu);
}
void afisareListaAngajati(Nod* cap) {
	while (cap != NULL) {
		afisareAngajat(cap->info);
		cap = cap->next;
	}
}