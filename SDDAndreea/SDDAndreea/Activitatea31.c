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

void afisareIngredient(Ingredient i) {
	printf("Id: %d\n", i.id);
	printf("Cantitate: %d\n", i.cantitate);
	printf("Pret: %.2f\n", i.pret);
	printf("Nume: %s\n", i.nume);
	printf("Unitate: %s\n", i.unitate);
	printf("Cod: %c\n\n", i.cod);
}