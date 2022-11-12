
#ifndef ECECITY_CHATEAU_H
#define ECECITY_CHATEAU_H

#include <stdlib.h>
#include "raylib.h"

#define CAPACITE_CHATEAU_EAU 5000

typedef enum Orientation_t {ORIENTATION_6X4, ORIENTATION_4X6, ORIENTATION_NULL} Orientation_t;

/// Représente un château d'eau simulé.
typedef struct ChateauEau_t {
    int capacite;
    Orientation_t orientation;
    Vector2 position;
} ChateauEau_t;

/// Crée un château d'eau.
ChateauEau_t* chateau_alloc();

/// Retourne la position d'un chateau
Vector2 get_chateau_position(ChateauEau_t* chateau);

/// Détruit un château d'eau.
void chateau_free(ChateauEau_t* chateau);

/// Incrémente d'un tick la simulation d'un château d'eau.
void chateau_step(ChateauEau_t* chateau);

#endif //ECECITY_CHATEAU_H
