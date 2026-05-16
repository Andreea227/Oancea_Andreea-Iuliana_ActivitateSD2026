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
Ingredient initIngredient(int id, int cantitate, float pret,
	const char* nume, const char* unitate, unsigned char cod) {

	Ingredient i;
	i.id = id;
	i.cantitate = cantitate;
	i.pret = pret;
	i.cod = cod;

	i.nume = malloc(strlen(nume) + 1);
	strcpy(i.nume, nume);

	i.unitate = malloc(strlen(unitate) + 1);
	strcpy(i.unitate, unitate);

	return i;
}
int maxim(int a, int b) {
	return (a > b ? a : b);
}

int calculeazaInaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(
			calculeazaInaltimeArbore(rad->st),
			calculeazaInaltimeArbore(rad->dr)
		) + 1;
	}
	return 0;
}