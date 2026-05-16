#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraIngredient {
	int id;
	int cantitate;
	float pret;
	char* nume;
	char* unitate;
	unsigned char cod;
};
typedef struct StructuraIngredient Ingredient;

struct Nod {
	Ingredient info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;