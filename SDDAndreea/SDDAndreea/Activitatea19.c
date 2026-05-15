#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraTelefon {
	int id;
	int stoc;
	float pret;
	char* brand;
	char* model;
	unsigned char memorie;
};
typedef struct StructuraTelefon Telefon;

struct Heap {
	int lungime;
	Telefon* telefoane;
	int nrElemente;
};
typedef struct Heap Heap;