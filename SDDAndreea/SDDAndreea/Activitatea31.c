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
int calculDiferentaInaltimi(Nod* rad) {
	if (rad) {
		return calculeazaInaltimeArbore(rad->st)
			- calculeazaInaltimeArbore(rad->dr);
	}
	return 0;
}
void rotireLaStanga(Nod** rad) {
	Nod* aux = (*rad)->dr;
	(*rad)->dr = aux->st;
	aux->st = (*rad);
	(*rad) = aux;
}
void rotireLaDreapta(Nod** rad) {
	Nod* aux = (*rad)->st;
	(*rad)->st = aux->dr;
	aux->dr = (*rad);
	(*rad) = aux;
}
void adaugaIngredientInArbore(Nod** rad, Ingredient iNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = iNou;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if (iNou.id < (*rad)->info.id)
			adaugaIngredientInArbore(&(*rad)->st, iNou);
		else if (iNou.id > (*rad)->info.id)
			adaugaIngredientInArbore(&(*rad)->dr, iNou);
	}

	int dif = calculDiferentaInaltimi(*rad);
	if (dif == 2) {
		if (calculDiferentaInaltimi((*rad)->st) == -1)
			rotireLaStanga(&(*rad)->st);

		rotireLaDreapta(rad);
	}
	if (dif == -2) {
		if (calculDiferentaInaltimi((*rad)->dr) == 1)
			rotireLaDreapta(&(*rad)->dr);

		rotireLaStanga(rad);
	}
}
void afisarePreordine(Nod* rad) {
	if (rad) {
		afisareIngredient(rad->info);
		afisarePreordine(rad->st);
		afisarePreordine(rad->dr);
	}
}
int determinaNumarNoduri(Nod* rad) {
	if (rad) {
		return determinaNumarNoduri(rad->st)
			+ determinaNumarNoduri(rad->dr)
			+ 1;
	}
	return 0;
}
float calculeazaPretTotal(Nod* rad) {
	if (rad) {
		return rad->info.pret
			+ calculeazaPretTotal(rad->st)
			+ calculeazaPretTotal(rad->dr);
	}
	return 0;
}

float calculeazaValoareStoc(Nod* rad) {
	if (rad) {
		return (rad->info.pret * rad->info.cantitate)
			+ calculeazaValoareStoc(rad->st)
			+ calculeazaValoareStoc(rad->dr);
	}
	return 0;
}
void dezalocareArbore(Nod** rad) {
	if (*rad) {
		dezalocareArbore(&(*rad)->st);
		dezalocareArbore(&(*rad)->dr);

		free((*rad)->info.nume);
		free((*rad)->info.unitate);
		free(*rad);
		*rad = NULL;
	}
}
