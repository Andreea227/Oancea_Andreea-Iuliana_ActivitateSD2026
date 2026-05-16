#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraPrajitura {
	int id;
	int calorii;
	float pret;
	char* nume;
	char* cofetarie;
	unsigned char tip;
};
typedef struct StructuraPrajitura Prajitura;

struct Heap {
	int capacitate;
	Prajitura* prajituri;
	int nrElemente;
};
typedef struct Heap Heap;