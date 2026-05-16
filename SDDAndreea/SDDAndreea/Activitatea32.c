#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMembru {
	int id;
	int varsta;
	float abonament;
	char* nume;
	char* tipAbonament;
	unsigned char cod;
};
typedef struct StructuraMembru Membru;

struct Nod {
	Membru info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

void afisareMembru(Membru m) {
	printf("Id: %d\n", m.id);
	printf("Varsta: %d\n", m.varsta);
	printf("Abonament: %.2f\n", m.abonament);
	printf("Nume: %s\n", m.nume);
	printf("Tip abonament: %s\n", m.tipAbonament);
	printf("Cod: %c\n\n", m.cod);
}
