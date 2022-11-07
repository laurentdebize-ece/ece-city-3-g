
#include "sim/route.h"

Route_t* route_alloc() {
    Route_t* route = malloc(sizeof (Route_t));
    route->nb_voisins = 0;
    return route;
}

void route_free(Route_t* route) {
    free(route);
}