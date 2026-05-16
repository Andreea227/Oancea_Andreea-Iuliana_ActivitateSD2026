#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCont {
	int id;
	int sold;
	float dobanda;
	char* titular;
	char* tipCont;
	unsigned char cod;
};
typedef struct StructuraCont Cont;

struct Nod {
	Cont info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

void afisareCont(Cont c) {
	printf("Id: %d\n", c.id);
	printf("Sold: %d\n", c.sold);
	printf("Dobanda: %.2f\n", c.dobanda);
	printf("Titular: %s\n", c.titular);
	printf("Tip cont: %s\n", c.tipCont);
	printf("Cod: %c\n\n", c.cod);
}
Cont initCont(int id, int sold, float dobanda,
	const char* titular, const char* tipCont, unsigned char cod) {

	Cont c;
	c.id = id;
	c.sold = sold;
	c.dobanda = dobanda;
	c.cod = cod;

	c.titular = malloc(strlen(titular) + 1);
	strcpy(c.titular, titular);

	c.tipCont = malloc(strlen(tipCont) + 1);
	strcpy(c.tipCont, tipCont);

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
void adaugaContInArbore(Nod** rad, Cont cNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = cNou;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if (cNou.id < (*rad)->info.id)
			adaugaContInArbore(&(*rad)->st, cNou);
		else if (cNou.id > (*rad)->info.id)
			adaugaContInArbore(&(*rad)->dr, cNou);
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
		afisareCont(rad->info);
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
float calculeazaSoldTotal(Nod* rad) {
	if (rad) {
		return rad->info.sold
			+ calculeazaSoldTotal(rad->st)
			+ calculeazaSoldTotal(rad->dr);
	}
	return 0;
}
float calculeazaValoareDobanda(Nod* rad) {
	if (rad) {
		return (rad->info.sold + rad->info.sold * rad->info.dobanda)
			+ calculeazaValoareDobanda(rad->st)
			+ calculeazaValoareDobanda(rad->dr);
	}
	return 0;
}
void dezalocareArbore(Nod** rad) {
	if (*rad) {
		dezalocareArbore(&(*rad)->st);
		dezalocareArbore(&(*rad)->dr);

		free((*rad)->info.titular);
		free((*rad)->info.tipCont);
		free(*rad);
		*rad = NULL;
	}
}
int main() {
	Nod* rad = NULL;

	adaugaContInArbore(&rad, initCont(1, 1000, 0.05, "Ion Popescu", "Economii", 'E'));
	adaugaContInArbore(&rad, initCont(2, 5000, 0.02, "Maria Ionescu", "Curent", 'C'));
	adaugaContInArbore(&rad, initCont(3, 2000, 0.03, "Vasile Georgescu", "Economii", 'E'));
	adaugaContInArbore(&rad, initCont(4, 10000, 0.04, "Elena Marin", "Premium", 'P'));
	adaugaContInArbore(&rad, initCont(5, 750, 0.01, "George Dima", "Curent", 'C'));

	afisarePreordine(rad);

	printf("Numar conturi: %d\n", determinaNumarNoduri(rad));
	printf("Sold total: %.2f\n", calculeazaSoldTotal(rad));
	printf("Valoare cu dobanda: %.2f\n", calculeazaValoareDobanda(rad));

	dezalocareArbore(&rad);

	return 0;
}