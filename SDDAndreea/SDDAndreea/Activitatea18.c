#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraLaptop {
	int id;
	int ram;
	float pret;
	char* brand;
	char* procesor;
	unsigned char generatie;
};
typedef struct StructuraLaptop Laptop;

struct Heap {
	int lungime;
	Laptop* laptopuri;
	int nrElemente;
};
typedef struct Heap Heap;