#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMembru {
	int id;
	int varsta;
	float abonament;
	char* nume;
	char* tipAbonament;
	unsigned char cod;
};
typedef struct StructuraMembru Membru;

struct Nod {
	Membru info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

void afisareMembru(Membru m) {
	printf("Id: %d\n", m.id);
	printf("Varsta: %d\n", m.varsta);
	printf("Abonament: %.2f\n", m.abonament);
	printf("Nume: %s\n", m.nume);
	printf("Tip abonament: %s\n", m.tipAbonament);
	printf("Cod: %c\n\n", m.cod);
}
Membru initMembru(int id, int varsta, float abonament,
	const char* nume, const char* tipAbonament, unsigned char cod) {

	Membru m;
	m.id = id;
	m.varsta = varsta;
	m.abonament = abonament;
	m.cod = cod;

	m.nume = malloc(strlen(nume) + 1);
	strcpy(m.nume, nume);

	m.tipAbonament = malloc(strlen(tipAbonament) + 1);
	strcpy(m.tipAbonament, tipAbonament);

	return m;
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
void adaugaMembruInArbore(Nod** rad, Membru mNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = mNou;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if (mNou.id < (*rad)->info.id)
			adaugaMembruInArbore(&(*rad)->st, mNou);
		else if (mNou.id > (*rad)->info.id)
			adaugaMembruInArbore(&(*rad)->dr, mNou);
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
		afisareMembru(rad->info);
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