#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCamera {
	int id;
	int nrPaturi;
	float pretNoapte;
	char* tipCamera;
	char* hotel;
	unsigned char etaj;
};
typedef struct StructuraCamera Camera;

struct Nod {
	Camera info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

void afisareCamera(Camera c) {
	printf("Id: %d\n", c.id);
	printf("Nr paturi: %d\n", c.nrPaturi);
	printf("Pret/noapte: %.2f\n", c.pretNoapte);
	printf("Tip camera: %s\n", c.tipCamera);
	printf("Hotel: %s\n", c.hotel);
	printf("Etaj: %c\n\n", c.etaj);
}

Camera initCamera(int id, int paturi, float pret,
	const char* tip, const char* hotel, unsigned char etaj) {

	Camera c;
	c.id = id;
	c.nrPaturi = paturi;
	c.pretNoapte = pret;
	c.etaj = etaj;

	c.tipCamera = malloc(strlen(tip) + 1);
	strcpy(c.tipCamera, tip);

	c.hotel = malloc(strlen(hotel) + 1);
	strcpy(c.hotel, hotel);

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
void adaugaCameraInArbore(Nod** rad, Camera cNou) {
	if (*rad == NULL) {
		Nod* nod = malloc(sizeof(Nod));
		nod->info = cNou;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if (cNou.id < (*rad)->info.id)
			adaugaCameraInArbore(&(*rad)->st, cNou);
		else if (cNou.id > (*rad)->info.id)
			adaugaCameraInArbore(&(*rad)->dr, cNou);
	}

	int dif = calculDiferentaInaltimi(*rad);