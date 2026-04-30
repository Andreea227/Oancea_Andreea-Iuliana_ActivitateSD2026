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