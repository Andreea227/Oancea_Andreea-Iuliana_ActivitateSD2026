#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraObiectMarin {
	int id;
	int capacitate;
	float lungime;
	char* nume;
	char* tip;
	unsigned char steag;
};
typedef struct StructuraObiectMarin ObiectMarin;

struct Nod {
	ObiectMarin info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;