
#ifndef ECECITY_ROUTE_H
#define ECECITY_ROUTE_H

#include <stdlib.h>
#include "utils/grille.h"

typedef struct Route_t {
    /// Nombre de voisins a la route.
    int nb_voisins;
    /// Position de la route.
    Vector2I position;
} Route_t;

Route_t* route_alloc();

void route_free(Route_t* route);

#endif //ECECITY_ROUTE_H
