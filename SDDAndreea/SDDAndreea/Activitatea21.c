#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraTara {
	int id;
	int populatie;
	float pib;
	char* numeTara;
	char* capitala;
	unsigned char continent;
};
typedef struct StructuraTara Tara;

struct Nod {
	Tara info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;
