#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Masina {
	int id;
	char* marca;
	float pret;
} Masina;

typedef struct Nod {
	Masina info;
	struct Nod* next;
} Nod;

Masina creareMasina(int id, const char* marca, float pret) {
	Masina m;
	m.id = id;

	m.marca = (char*)malloc(strlen(marca) + 1);
	strcpy(m.marca, marca);

	m.pret = pret;

	return m;
}

void afisareMasina(Masina m) {
	printf("ID: %d | Marca: %s | Pret: %.2f\n", m.id, m.marca, m.pret);
}

Nod* inserareInceput(Nod* cap, Masina m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = cap;
	return nou;
}

void inserareFinal(Nod** cap, Masina m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* p = *cap;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void dezalocare(Nod** cap) {
	while (*cap != NULL) {
		free((*cap)->info.marca);
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
	}
}

int main() {
	Nod* cap = NULL;

	Masina m1 = creareMasina(1, "BMW", 20000);
	Masina m2 = creareMasina(2, "Audi", 25000);
	Masina m3 = creareMasina(3, "Mercedes", 30000);

	cap = inserareInceput(cap, m1);
	cap = inserareInceput(cap, m2);

	inserareFinal(&cap, m3);

	afisareLista(cap);

	dezalocare(&cap);

	return 0;
}