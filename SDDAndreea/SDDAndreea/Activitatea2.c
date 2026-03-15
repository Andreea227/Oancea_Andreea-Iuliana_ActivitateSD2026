#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StructuraCarte Carte;
typedef struct Nod Nod;

struct StructuraCarte {
	int id;
	int nrPagini;
	float pret;
	char* titlu;
	char* autor;
	unsigned char categorie;
};

struct Nod {
	Carte info;
	struct Nod* next;
};

Carte citireCarteDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	Carte c;

	fgets(buffer, 100, file);

	aux = strtok(buffer, sep);
	c.id = atoi(aux);
	c.nrPagini = atoi(strtok(NULL, sep));
	c.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	c.titlu = malloc(strlen(aux) + 1);
	if (c.titlu != NULL) {
		strcpy(c.titlu, aux);
	}

	aux = strtok(NULL, sep);
	c.autor = malloc(strlen(aux) + 1);
	if (c.autor != NULL) {
		strcpy(c.autor, aux);
	}

	c.categorie = *strtok(NULL, sep);

	return c;
}

void afisareCarte(Carte c) {
	printf("ID: %d\n", c.id);
	printf("Pagini: %d\n", c.nrPagini);
	printf("Pret: %.2f\n", c.pret);
	printf("Titlu: %s\n", c.titlu);
	printf("Autor: %s\n", c.autor);
	printf("Categorie: %c\n\n", c.categorie);
}

void afisareListaCarti(Nod* cap) {
	while (cap != NULL) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void adaugaCarteInLista(Nod** cap, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	if (nou != NULL) {
		nou->info = carteNoua;
		nou->next = NULL;

		if (*cap) {
			Nod* p = *cap;
			while (p->next) {
				p = p->next;
			}
			p->next = nou;
		}
		else {
			*cap = nou;
		}
	}
}

void adaugaLaInceputInLista(Nod** cap, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	if (nou != NULL) {
		nou->info = carteNoua;
		nou->next = *cap;
		*cap = nou;
	}
}

Nod* citireListaCartiDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			adaugaCarteInLista(&cap, citireCarteDinFisier(f));
		}
		fclose(f);
	}

	return cap;
}

void dezalocareListaCarti(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;

		*cap = p->next;
		free(p->info.titlu);
		free(p->info.autor);

		free(p);
	}
}

float calculeazaPretMediu(Nod* cap) {
	float suma = 0;
	int contor = 0;

	while (cap) {
		suma += cap->info.pret;
		contor++;
		cap = cap->next;
	}

	return (contor > 0) ? suma / contor : 0;
}