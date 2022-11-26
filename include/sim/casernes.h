#ifndef ECECITY_POMPIER_H
#define ECECITY_POMPIER_H
#include <stdlib.h>
#include <utils/grille.h>
#include <utils/vector.h>
#include "utils/liste.h"
#include "screens/gameplay.h"
#define CASERNE_PRIX_CONSTRUCTION 10000

typedef struct CasernePompier_t {
    /// La liste des bâtiments deservis par la caserne.
    Vector_t* habitations;
    /// La position de la caserne sur la carte.
    Vector2I position;
} CasernePompier_t;

///Créer une caserne
CasernePompier_t* alloc_caserne();

void draw_enfeu(GameplayScreen_t *gameplay);

/// Détruit une caserne.
void caserne_free(CasernePompier_t* caserne);

#endif //ECECITY_POMPIER_H
