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

struct nodLdi {
	Cafenea info;
	nodLdi* next;
	nodLdi* prev;
};

struct listaDubla {
	nodLdi* prim;
	nodLdi* ultim;
};

Cafenea Init(char* nume, int nrlocuri, float incasari) {
	Cafenea c;
	c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrLocuri = nrlocuri;
	c.incasari = incasari;
	return c;
}

Cafenea InitCopiere(Cafenea princ) {
	return Init(princ.nume, princ.nrLocuri, princ.incasari);
}