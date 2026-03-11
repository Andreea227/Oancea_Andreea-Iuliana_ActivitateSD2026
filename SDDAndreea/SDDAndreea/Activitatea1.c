#include<stdio.h>
#include<malloc.h>

typedef struct Frzerie Frizerie;
typedef struct Nod Nod;

typedef struct Frizerie {
	char* nume;
	int nrMediuClienti;
	float costServiciu;
};

typedef struct Nod Nod;
struct Nod {
	struct Frizerie frizerie;
	struct Nod* next;

};
struct Frizerie initializareFrizerie(char* fnume, int fnrMediuClienti, float fcostServiciu) {
	struct Frizerie f1;
	f1.nume = malloc(sizeof(char) * (strlen(fnume) + 1));
	strcpy_s(f1.nume, strlen(fnume) + 1, fnume);
	f1.nrMediuClienti = fnrMediuClienti;
	f1.costServiciu = fcostServiciu;

	return f1;
}