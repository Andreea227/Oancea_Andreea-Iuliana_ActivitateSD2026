#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCont {
	int id;
	int sold;
	float dobanda;
	char* titular;
	char* tipCont;
	unsigned char cod;
};
typedef struct StructuraCont Cont;

struct Nod {
	Cont info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;
