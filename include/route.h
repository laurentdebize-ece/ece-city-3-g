#ifndef ECECITY_ROUTE_H
#define ECECITY_ROUTE_H

#include "sim/sim.h"



void modeNewRoad(SimWorld_t* eceCity);

void selectionNewRoad(SimWorld_t* eceCity);

void affichageRouteSelection(SimWorld_t* eceCity);

void actualiserCheminRoute(SimWorld_t* eceCity);

void printChemin(SimWorld_t* eceCity);

void checkChangementCelluleSurPlacementRoute(SimWorld_t* eceCity);

void actualiserMatriceConstructionRoute(SimWorld_t* eceCity);


#endif