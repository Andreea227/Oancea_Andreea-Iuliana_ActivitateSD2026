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
