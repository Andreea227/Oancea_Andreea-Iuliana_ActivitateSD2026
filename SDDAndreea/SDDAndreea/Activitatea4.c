#include <stdio.h>
#include <malloc.h>

typedef struct cafenea Cafenea;
typedef struct nod Nod;
typedef struct nodLdi nodLdi;
typedef struct listaDubla listaDubla;

struct cafenea {
	int nrLocuri;
	char* nume;
	float incasari;
};

struct nod {
	Cafenea info;
	Nod* next;
};