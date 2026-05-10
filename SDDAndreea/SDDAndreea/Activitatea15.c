#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

struct StructuraFilm {
	int id;
	int durata;
	float rating;
	char* titlu;
	char* regizor;
	unsigned char categorie;
};
typedef struct StructuraFilm Film;

struct Heap {
	int lungime;
	Film* filme;
	int nrElemente;
};
typedef struct Heap Heap;

Film citireFilmDinFisier(FILE* file) {

	char buffer[100];
	char sep[3] = ",\n";

	fgets(buffer, 100, file);

	char* aux;
	Film f;

	aux = strtok(buffer, sep);
	f.id = atoi(aux);

	f.durata = atoi(strtok(NULL, sep));

	f.rating = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	f.titlu = malloc(strlen(aux) + 1);
	strcpy_s(f.titlu, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	f.regizor = malloc(strlen(aux) + 1);
	strcpy_s(f.regizor, strlen(aux) + 1, aux);

	f.categorie = *strtok(NULL, sep);

	return f;
}

void afisareFilm(Film film) {

	printf("Id: %d\n", film.id);
	printf("Durata: %d\n", film.durata);
	printf("Rating: %.2f\n", film.rating);
	printf("Titlu: %s\n", film.titlu);
	printf("Regizor: %s\n", film.regizor);
	printf("Categorie: %c\n\n", film.categorie);
}

Heap initializareHeap(int lungime) {

	Heap heap;

	heap.lungime = lungime;
	heap.filme = malloc(sizeof(Film) * lungime);
	heap.nrElemente = 0;

	return heap;
}

void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;

	if (pozSt < heap.nrElemente &&
		heap.filme[pozMin].rating > heap.filme[pozSt].rating) {

		pozMin = pozSt;
	}

	if (pozDr < heap.nrElemente &&
		heap.filme[pozMin].rating > heap.filme[pozDr].rating) {

		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {

		Film aux = heap.filme[pozMin];
		heap.filme[pozMin] = heap.filme[pozitieNod];
		heap.filme[pozitieNod] = aux;

		if (pozMin < (heap.nrElemente - 2) / 2) {
			filtreazaHeap(heap, pozMin);
		}
	}
}

Heap citireHeapDinFisier(const char* numeFisier) {

	Heap heap = initializareHeap(10);

	FILE* f = fopen(numeFisier, "r");

	if (f) {

		while (!feof(f)) {
			heap.filme[heap.nrElemente++] =
				citireFilmDinFisier(f);
		}
	}

	fclose(f);

	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}

	return heap;
}

void afisareHeap(Heap heap) {

	for (int i = 0; i < heap.nrElemente; i++) {
		afisareFilm(heap.filme[i]);
	}
}

void afiseazaElementeAscunse(Heap heap) {

	for (int i = heap.nrElemente; i < heap.lungime; i++) {
		afisareFilm(heap.filme[i]);
	}
}

Film extrageFilm(Heap* heap) {

	Film film;
	film.id = -1;

	if (heap->nrElemente > 0) {

		film = heap->filme[0];

		heap->filme[0] =
			heap->filme[heap->nrElemente - 1];

		heap->filme[heap->nrElemente - 1] = film;

		heap->nrElemente--;

		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
	}

	return film;
}

void dezalocareHeap(Heap* heap) {

	for (int i = 0; i < heap->lungime; i++) {

		free(heap->filme[i].titlu);
		free(heap->filme[i].regizor);
	}

	free(heap->filme);

	heap->filme = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}