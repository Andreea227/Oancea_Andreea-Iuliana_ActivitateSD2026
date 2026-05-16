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

void afisareCarte(Carte c) {
	printf("Id: %d\n", c.id);
	printf("An aparitie: %d\n", c.anAparitie);
	printf("Pret: %.2f\n", c.pret);
	printf("Titlu: %s\n", c.titlu);
	printf("Autor: %s\n", c.autor);
	printf("Gen: %c\n\n", c.gen);
}
Carte initCarte(int id, int an, float pret,
	const char* titlu, const char* autor, unsigned char gen) {

	Carte c;
	c.id = id;
	c.anAparitie = an;
	c.pret = pret;
	c.gen = gen;

	c.titlu = malloc(strlen(titlu) + 1);
	strcpy(c.titlu, titlu);

	c.autor = malloc(strlen(autor) + 1);
	strcpy(c.autor, autor);

	return c;
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
void adaugaCarteInArbore(Nod** rad, Carte cNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = cNou;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if (cNou.id < (*rad)->info.id)
			adaugaCarteInArbore(&(*rad)->st, cNou);
		else if (cNou.id > (*rad)->info.id)
			adaugaCarteInArbore(&(*rad)->dr, cNou);
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
		afisareCarte(rad->info);
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
float calculeazaPretPeAutor(Nod* rad, const char* autor) {
	if (rad) {
		float s = calculeazaPretPeAutor(rad->st, autor)
			+ calculeazaPretPeAutor(rad->dr, autor);

		if (strcmp(rad->info.autor, autor) == 0)
			s += rad->info.pret;

		return s;
	}
	return 0;
}