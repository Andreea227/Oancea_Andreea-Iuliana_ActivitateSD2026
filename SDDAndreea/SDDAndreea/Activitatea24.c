#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraObiectMarin {
	int id;
	int capacitate;
	float lungime;
	char* nume;
	char* tip;
	unsigned char steag;
};
typedef struct StructuraObiectMarin ObiectMarin;

struct Nod {
	ObiectMarin info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

void afisareObiect(ObiectMarin o) {
	printf("Id: %d\n", o.id);
	printf("Capacitate: %d\n", o.capacitate);
	printf("Lungime: %.2f\n", o.lungime);
	printf("Nume: %s\n", o.nume);
	printf("Tip: %s\n", o.tip);
	printf("Steag: %c\n\n", o.steag);
}
ObiectMarin initObiect(int id, int cap, float lungime,
	const char* nume, const char* tip, unsigned char steag) {

	ObiectMarin o;
	o.id = id;
	o.capacitate = cap;
	o.lungime = lungime;
	o.steag = steag;

	o.nume = malloc(strlen(nume) + 1);
	strcpy(o.nume, nume);

	o.tip = malloc(strlen(tip) + 1);
	strcpy(o.tip, tip);

	return o;
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
void adaugaObiectInArbore(Nod** rad, ObiectMarin oNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = oNou;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if (oNou.id < (*rad)->info.id)
			adaugaObiectInArbore(&(*rad)->st, oNou);
		else if (oNou.id > (*rad)->info.id)
			adaugaObiectInArbore(&(*rad)->dr, oNou);
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
		afisareObiect(rad->info);
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
int calculeazaCapacitateTotala(Nod* rad) {
	if (rad) {
		return rad->info.capacitate
			+ calculeazaCapacitateTotala(rad->st)
			+ calculeazaCapacitateTotala(rad->dr);
	}
	return 0;
}