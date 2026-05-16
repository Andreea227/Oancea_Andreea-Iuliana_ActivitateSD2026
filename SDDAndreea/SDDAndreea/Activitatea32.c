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