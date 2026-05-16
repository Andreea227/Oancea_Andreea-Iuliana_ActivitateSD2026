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