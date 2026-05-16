#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCarte {
	int id;
	int anAparitie;
	float pret;
	char* titlu;
	char* autor;
	unsigned char gen;
};
typedef struct StructuraCarte Carte;

struct Nod {
	Carte info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;