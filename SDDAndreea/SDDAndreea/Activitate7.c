#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Carte Carte;
typedef struct Nod Nod;
typedef struct HashTable HashTable; 

struct Carte
{
	char* titlu;
	int nrPagini;
	float pret;
};