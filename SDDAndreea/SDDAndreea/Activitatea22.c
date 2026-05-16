#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraAnimal {
	int id;
	int varsta;
	float greutate;
	char* specie;
	char* nume;
	unsigned char tipHrana;
};
typedef struct StructuraAnimal Animal;

struct Nod {
	Animal info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

void afisareAnimal(Animal a) {
	printf("Id: %d\n", a.id);
	printf("Varsta: %d\n", a.varsta);
	printf("Greutate: %.2f\n", a.greutate);
	printf("Specie: %s\n", a.specie);
	printf("Nume: %s\n", a.nume);
	printf("Tip hrana: %c\n\n", a.tipHrana);
}
Animal initAnimal(int id, int varsta, float greutate,
	const char* specie, const char* nume, unsigned char tipHrana) {

	Animal a;
	a.id = id;
	a.varsta = varsta;
	a.greutate = greutate;
	a.tipHrana = tipHrana;

	a.specie = malloc(strlen(specie) + 1);
	strcpy(a.specie, specie);

	a.nume = malloc(strlen(nume) + 1);
	strcpy(a.nume, nume);

	return a;
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
void adaugaAnimalInArbore(Nod** rad, Animal aNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = aNou;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if (aNou.id < (*rad)->info.id)
			adaugaAnimalInArbore(&(*rad)->st, aNou);
		else if (aNou.id > (*rad)->info.id)
			adaugaAnimalInArbore(&(*rad)->dr, aNou);
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
		afisareAnimal(rad->info);
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
float calculeazaGreutateTotala(Nod* rad) {
	if (rad) {
		return rad->info.greutate
			+ calculeazaGreutateTotala(rad->st)
			+ calculeazaGreutateTotala(rad->dr);
	}
	return 0;
}

float calculeazaGreutatePeHrana(Nod* rad, char tip) {
	if (rad) {
		float s = calculeazaGreutatePeHrana(rad->st, tip)
			+ calculeazaGreutatePeHrana(rad->dr, tip);

		if (rad->info.tipHrana == tip)
			s += rad->info.greutate;

		return s;
	}
	return 0;
}

void dezalocareArbore(Nod** rad) {
	if (*rad) {
		dezalocareArbore(&(*rad)->st);
		dezalocareArbore(&(*rad)->dr);

		free((*rad)->info.specie);
		free((*rad)->info.nume);
		free(*rad);
		*rad = NULL;
	}
}