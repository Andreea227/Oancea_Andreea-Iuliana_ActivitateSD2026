#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct StructuraAngajat {
	int id;
	int varsta;
	float salariu;
	char* nume;
	char* departament;
	unsigned char nivel;
};
typedef struct StructuraAngajat Angajat;

struct Heap {
	int lungime;
	Angajat* angajati;
	int nrElemente;
};
typedef struct Heap Heap;