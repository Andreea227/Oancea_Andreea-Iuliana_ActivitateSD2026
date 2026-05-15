#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCont {
	int id;
	int sold;
	float dobanda;
	char* titular;
	char* banca;
	unsigned char tip;
};
typedef struct StructuraCont ContBancar;

struct Heap {
	int lungime;
	ContBancar* conturi;
	int nrElemente;
};
typedef struct Heap Heap;

