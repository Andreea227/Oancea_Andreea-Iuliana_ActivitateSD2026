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

void interschimba(listaDubla ld, int i1, int i2) {
	nodLdi* nod1 = ld.prim;
	nodLdi* nod2 = ld.prim;

	for (int i = 1; i < i1 && nod1 != NULL; i++)
		nod1 = nod1->next;

	for (int i = 1; i < i2 && nod2 != NULL; i++)
		nod2 = nod2->next;

	if (nod1 && nod2) {
		Cafenea temp = nod1->info;
		nod1->info = nod2->info;
		nod2->info = temp;
	}
}

int CalcNrElem(listaDubla ld) {
	int i = 0;
	nodLdi* p = ld.prim;
	while (p) {
		i++;
		p = p->next;
	}
	return i;
}

char palindrom(listaDubla ld) {
	int n = CalcNrElem(ld);
	nodLdi* st = ld.prim;
	nodLdi* dr = ld.ultim;

	for (int i = 0; i < n / 2; i++) {
		if (st->info.nrLocuri != dr->info.nrLocuri)
			return '0';
		st = st->next;
		dr = dr->prev;
	}
	return '1';
}