#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraAnimal {
	int id;
	int varsta;
	float greutate;
	char* specie;
	char* nume;
	unsigned char tipHrana;
};
typedef struct StructuraAnimal Animal;

struct Nod {
	Animal info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

void afisareAnimal(Animal a) {
	printf("Id: %d\n", a.id);
	printf("Varsta: %d\n", a.varsta);
	printf("Greutate: %.2f\n", a.greutate);
	printf("Specie: %s\n", a.specie);
	printf("Nume: %s\n", a.nume);
	printf("Tip hrana: %c\n\n", a.tipHrana);
}
Animal initAnimal(int id, int varsta, float greutate,
	const char* specie, const char* nume, unsigned char tipHrana) {

	Animal a;
	a.id = id;
	a.varsta = varsta;
	a.greutate = greutate;
	a.tipHrana = tipHrana;

	a.specie = malloc(strlen(specie) + 1);
	strcpy(a.specie, specie);

	a.nume = malloc(strlen(nume) + 1);
	strcpy(a.nume, nume);

	return a;
}
int maxim(int a, int b) {
	return (a > b ? a : b);
}

int calculeazaInaltimeArbore(Nod* rad) {
	if (rad) {
		return maxim(
			calculeazaInaltimeArbore(rad->st),
			calculeazaInaltimeArbore(rad->dr)
		) + 1;
	}
	return 0;
}
int calculDiferentaInaltimi(Nod* rad) {
	if (rad) {
		return calculeazaInaltimeArbore(rad->st)
			- calculeazaInaltimeArbore(rad->dr);
	}
	return 0;
}