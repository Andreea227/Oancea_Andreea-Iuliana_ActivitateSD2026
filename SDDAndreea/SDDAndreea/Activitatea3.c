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

Restaurant citireRestaurant(FILE* f)
{
    char buffer[100];
    char sep[3] = ",\n";

    fgets(buffer, 100, f);

    Restaurant r;

    char* aux = strtok(buffer, sep);
    r.id = atoi(aux);

    aux = strtok(NULL, sep);
    r.nume = (char*)malloc(strlen(aux) + 1);
    strcpy(r.nume, aux);

    r.rating = atof(strtok(NULL, sep));

    return r;
}

void adauga(ListaDubla* lista, Restaurant r)
{
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = r;
    nou->next = NULL;
    nou->prev = NULL;

    if (lista->prim == NULL)
    {
        lista->prim = lista->ultim = nou;
    }
    else
    {
        nou->prev = lista->ultim;
        lista->ultim->next = nou;
        lista->ultim = nou;
    }
}