#ifndef ECECITY_POMPIER_H
#define ECECITY_POMPIER_H
#include <stdlib.h>
#include <utils/grille.h>
#include "utils/liste.h"
#define CASERNE_PRIX_CONSTRUCTION 10000

typedef struct CasernePompier_t {
    /// La liste des bâtiments deservis par la caserne.
    Liste_t* habitations;
    /// La position de la caserne sur la carte.
    Vector2I position;
} CasernePompier_t;

///Créer une caserne
CasernePompier_t* alloc_caserne();

/// Détruit une caserne.
void caserne_free(CasernePompier_t* caserne);

#endif //ECECITY_POMPIER_H