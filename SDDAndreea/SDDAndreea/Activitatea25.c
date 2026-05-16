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