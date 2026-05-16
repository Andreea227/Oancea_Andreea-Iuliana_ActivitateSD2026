#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraPacient {
	int id;
	int varsta;
	float gravitate;
	char* nume;
	char* diagnostic;
	unsigned char sectie;
};
typedef struct StructuraPacient Pacient;

struct Heap {
	int capacitate;
	Pacient* pacienti;
	int nrElemente;
};
typedef struct Heap Heap;