#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraTara {
	int id;
	int populatie;
	float pib;
	char* numeTara;
	char* capitala;
	unsigned char continent;
};
typedef struct StructuraTara Tara;

struct Nod {
	Tara info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

Tara citireTaraDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);

	char* aux;
	Tara t1;

	aux = strtok(buffer, sep);
	t1.id = atoi(aux);

	t1.populatie = atoi(strtok(NULL, sep));

	t1.pib = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	t1.numeTara = malloc(strlen(aux) + 1);
	strcpy_s(t1.numeTara, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	t1.capitala = malloc(strlen(aux) + 1);
	strcpy_s(t1.capitala, strlen(aux) + 1, aux);

	t1.continent = *strtok(NULL, sep);

	return t1;
}

void afisareTara(Tara tara) {
	printf("Id: %d\n", tara.id);
	printf("Populatie: %d\n", tara.populatie);
	printf("PIB: %.2f\n", tara.pib);
	printf("Nume tara: %s\n", tara.numeTara);
	printf("Capitala: %s\n", tara.capitala);
	printf("Continent: %c\n\n", tara.continent);
}

void adaugaTaraInArbore(Nod** rad, Tara taraNoua) {
	if (*rad == NULL) {
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = taraNoua;
		nod->st = NULL;
		nod->dr = NULL;
		*rad = nod;
	}
	else {
		if ((*rad)->info.id > taraNoua.id) {
			adaugaTaraInArbore(&((*rad)->st), taraNoua);
		}
		if ((*rad)->info.id < taraNoua.id) {
			adaugaTaraInArbore(&((*rad)->dr), taraNoua);
		}
	}
}
Nod* citireArboreDeTariDinFisier(const char* numeFisier) {
	Nod* rad = NULL;
	FILE* f = fopen(numeFisier, "r");

	if (f) {
		while (!feof(f)) {
			Tara t = citireTaraDinFisier(f);
			adaugaTaraInArbore(&rad, t);
		}
	}
	fclose(f);

	return rad;
}
void afisareTariInArbore(Nod* rad) {
	if (rad) {
		afisareTariInArbore(rad->st);
		afisareTara(rad->info);
		afisareTariInArbore(rad->dr);
	}
}
void afisarePreordine(Nod* rad) {
	if (rad) {
		afisareTara(rad->info);
		afisarePreordine(rad->st);
		afisarePreordine(rad->dr);
	}
}
void dezalocareArboreDeTari(Nod** rad) {
	if (*rad) {
		dezalocareArboreDeTari(&(*rad)->st);
		dezalocareArboreDeTari(&(*rad)->dr);

		free((*rad)->info.numeTara);
		free((*rad)->info.capitala);
		free(*rad);

		*rad = NULL;
	}
}