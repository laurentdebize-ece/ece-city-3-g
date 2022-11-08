#ifndef ECECITY_BATIMENT_H
#define ECECITY_BATIMENT_H

#include "sim/sim.h"
#include "tuile.h"

void affichagePlacementTemporaireTerrainVague(SimWorld_t *eceCity);

void selectionModePlacementBatiment(SimWorld_t *eceCity);

void modePlacementBatiment(SimWorld_t *eceCity);

void selectionModePlacementCentraleElec(SimWorld_t *eceCity);

void affichagePlacementTemporaireCentraleElec(SimWorld_t *eceCity);

void modePlacementCentraleElec(SimWorld_t *eceCity);

void modePlacementChateauEau(SimWorld_t *eceCity);

void affichagePlacementTemporaireChateauEau(SimWorld_t *eceCity);

void selectionModePlacementChateauEau(SimWorld_t *eceCity);



#endif
