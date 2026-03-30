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

void afisareCafenea(Cafenea c) {
	printf("Cafeneaua %s are %d locuri si incasari %.2f\n",
		c.nume, c.nrLocuri, c.incasari);
}

void inserareListDublaSfarsit(listaDubla* lista, Cafenea cafenea) {
	nodLdi* nod = (nodLdi*)malloc(sizeof(nodLdi));
	nod->info = InitCopiere(cafenea);
	nod->next = NULL;
	nod->prev = lista->ultim;

	if (lista->ultim) {
		lista->ultim->next = nod;
	}
	else {
		lista->prim = nod;
	}

	lista->ultim = nod;
}

void inserareListaDublaInceput(listaDubla* lista, Cafenea cafenea) {
	nodLdi* nod = (nodLdi*)malloc(sizeof(nodLdi));
	nod->info = InitCopiere(cafenea);
	nod->prev = NULL;
	nod->next = lista->prim;

	if (lista->prim) {
		lista->prim->prev = nod;
	}
	else {
		lista->ultim = nod;
	}

	lista->prim = nod;
}

void afisareListaDublaDeLaInceput(listaDubla lista) {
	nodLdi* p = lista.prim;
	while (p) {
		afisareCafenea(p->info);
		p = p->next;
	}
}

void afisareListaDublaDeLaSfarsit(listaDubla lista) {
	nodLdi* p = lista.ultim;
	while (p) {
		afisareCafenea(p->info);
		p = p->prev;
	}
}

void stergereListaDubla(listaDubla* lista) {
	nodLdi* p = lista->prim;
	while (p) {
		free(p->info.nume);
		nodLdi* temp = p->next;
		free(p);
		p = temp;
	}
	lista->prim = NULL;
	lista->ultim = NULL;
}