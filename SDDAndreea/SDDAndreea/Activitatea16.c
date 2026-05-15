#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct StructuraProdus {
	int id;
	int stoc;
	float pret;
	char* denumire;
	char* producator;
	unsigned char categorie;
};
typedef struct StructuraProdus Produs;

struct Nod {
	Produs info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;