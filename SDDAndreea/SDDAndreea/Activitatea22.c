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