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
