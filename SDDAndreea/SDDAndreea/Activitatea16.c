#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct StructuraProdus {
	int id;
	int stoc;
	float pret;
	char* denumire;
	char* producator;
	unsigned char categorie;
};
typedef struct StructuraProdus Produs;

struct Nod {
	Produs info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

Produs citireProdusDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;

	Produs p;

	aux = strtok(buffer, sep);
	p.id = atoi(aux);

	p.stoc = atoi(strtok(NULL, sep));

	p.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);

	p.denumire = malloc(strlen(aux) + 1);
	strcpy_s(p.denumire, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);

	p.producator = malloc(strlen(aux) + 1);
	strcpy_s(p.producator, strlen(aux) + 1, aux);

	p.categorie = *strtok(NULL, sep);

	return p;
}

void afisareProdus(Produs produs) {

	printf("Id: %d\n", produs.id);
	printf("Stoc: %d\n", produs.stoc);
	printf("Pret: %.2f\n", produs.pret);
	printf("Denumire: %s\n", produs.denumire);
	printf("Producator: %s\n", produs.producator);
	printf("Categorie: %c\n\n", produs.categorie);
}

void adaugaProdusInArbore(
	Nod** rad,
	Produs produsNou) {

	if (*rad == NULL) {

		Nod* nod = malloc(sizeof(Nod));

		nod->info = produsNou;

		nod->dr = NULL;
		nod->st = NULL;

		*rad = nod;
	}
	else {

		if ((*rad)->info.id > produsNou.id) {

			adaugaProdusInArbore(
				&((*rad)->st),
				produsNou);
		}

		if ((*rad)->info.id < produsNou.id) {

			adaugaProdusInArbore(
				&((*rad)->dr),
				produsNou);
		}
	}
}

Nod* citireArboreDeProduseDinFisier(
	const char* numeFisier) {

	Nod* rad = NULL;

	FILE* f = fopen(numeFisier, "r");

	if (f) {

		while (!feof(f)) {

			Produs p =
				citireProdusDinFisier(f);

			adaugaProdusInArbore(
				&rad,
				p);
		}
	}

	fclose(f);

	return rad;
}

void afisareProduseDinArbore(Nod* rad) {

	if (rad) {

		afisareProduseDinArbore(rad->st);

		afisareProdus(rad->info);

		afisareProduseDinArbore(rad->dr);
	}
}

void afisarePreordine(Nod* rad) {

	if (rad) {

		afisareProdus(rad->info);

		afisarePreordine(rad->st);

		afisarePreordine(rad->dr);
	}
}

void dezalocareArboreDeProduse(
	Nod** rad) {

	if (*rad) {

		dezalocareArboreDeProduse(
			&(*rad)->st);

		dezalocareArboreDeProduse(
			&(*rad)->dr);

		free((*rad)->info.denumire);

		free((*rad)->info.producator);

		free(*rad);

		*rad = NULL;
	}
}

Produs getProdusByID(
	Nod* rad,
	int id) {

	Produs p;

	p.id = -1;

	if (rad) {

		if (rad->info.id == id) {

			p = rad->info;

			p.denumire = malloc(
				sizeof(char) *
				(strlen(rad->info.denumire) + 1));

			strcpy(
				p.denumire,
				rad->info.denumire);

			p.producator = malloc(
				sizeof(char) *
				(strlen(rad->info.producator) + 1));

			strcpy(
				p.producator,
				rad->info.producator);
		}

		if (id < rad->info.id) {

			p = getProdusByID(
				rad->st,
				id);
		}

		if (id > rad->info.id) {

			p = getProdusByID(
				rad->dr,
				id);
		}
	}

	return p;
}

int determinaNumarNoduri(Nod* rad) {

	if (rad) {

		return determinaNumarNoduri(rad->st) +
			+determinaNumarNoduri(rad->dr) + 1;
	}

	return 0;
}

int maxim(int a, int b) {

	return (a > b ? a : b);
}

int calculeazaInaltimeArbore(Nod* rad) {

	if (rad) {

		return maxim(
			calculeazaInaltimeArbore(rad->st),
			calculeazaInaltimeArbore(rad->dr))
			+ 1;
	}

	return 0;
}

float calculeazaPretTotal(Nod* rad) {

	if (rad) {

		return rad->info.pret +
			+calculeazaPretTotal(rad->st) +
			+calculeazaPretTotal(rad->dr);
	}

	return 0;
}

float calculeazaPretulProduselorUnuiProducator(
	Nod* rad,
	const char* producator) {

	if (rad) {

		float suma =
			calculeazaPretulProduselorUnuiProducator(
				rad->st,
				producator)
			+
			calculeazaPretulProduselorUnuiProducator(
				rad->dr,
				producator);

		if (strcmp(
			rad->info.producator,
			producator) == 0) {

			suma += rad->info.pret;
		}

		return suma;
	}

	return 0;
}