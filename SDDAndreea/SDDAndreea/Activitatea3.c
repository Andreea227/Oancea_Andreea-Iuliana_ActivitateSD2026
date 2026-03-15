#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Restaurant Restaurant;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Restaurant {
    int id;
    char* nume;
    float rating;
};

struct Nod {
    Restaurant info;
    Nod* next;
    Nod* prev;
};

struct ListaDubla {
    Nod* prim;
    Nod* ultim;
};