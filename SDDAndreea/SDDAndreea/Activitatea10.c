#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Articol {
	char* nume;
	int cantitate;
	float pret;
} Articol;

Articol initArticol(const char* nume, int cantitate, float pret) {
	Articol a;
	a.cantitate = cantitate;
	a.pret = pret;

	a.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(a.nume, nume);

	return a;
}

void afisareArticol(Articol a) {
	printf("\n%s - cantitate: %d - pret: %.2f",
		a.nume, a.cantitate, a.pret);
}

void citireFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");

	char buffer[50];
	int cant;
	float pret;

	while (fscanf(f, "%s %d %f", buffer, &cant, &pret) == 3) {
		Articol a = initArticol(buffer, cant, pret);
		afisareArticol(a);
		free(a.nume);
	}

	fclose(f);
}

void scriereFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "w");

	fprintf(f, "Laptop 10 3500\n");
	fprintf(f, "Telefon 5 2000\n");
	fprintf(f, "Mouse 20 150\n");

	fclose(f);
}