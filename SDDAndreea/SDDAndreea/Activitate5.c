#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Masina {
	int id;
	char* marca;
	float pret;
} Masina;

typedef struct Nod {
	Masina info;
	struct Nod* next;
} Nod;