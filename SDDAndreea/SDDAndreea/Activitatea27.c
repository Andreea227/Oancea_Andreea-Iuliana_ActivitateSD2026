#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraZbor {
	int id;
	int durata;
	float intarziere;
	char* destinatie;
	char* companie;
	unsigned char terminal;
};
typedef struct StructuraZbor Zbor;

struct Heap {
	int capacitate;
	Zbor* zboruri;
	int nrElemente;
};
typedef struct Heap Heap;
