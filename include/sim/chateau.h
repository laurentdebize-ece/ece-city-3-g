
#ifndef ECECITY_CHATEAU_H
#define ECECITY_CHATEAU_H

#include <stdlib.h>
#include <utils/grille.h>

#define CAPACITE_CHATEAU_EAU 5000

/// Représente un château d'eau simulé.
typedef struct ChateauEau_t {
    int capacite;

    Vector2I position;
} ChateauEau_t;

/// Crée un château d'eau.
ChateauEau_t* chateau_alloc();

/// Détruit un château d'eau.
void chateau_free(ChateauEau_t* chateau);

/// Incrémente d'un tick la simulation d'un château d'eau.
void chateau_step(ChateauEau_t* chateau);

#endif //ECECITY_CHATEAU_H
