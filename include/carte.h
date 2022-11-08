#ifndef ECECITY_CARTE_H
#define ECECITY_CARTE_H

#include "tuile.h"

void initMap(SimWorld_t* eceCity);

void resetMatrice(SimWorld_t* eceCity);

void afficherFondMap(SimWorld_t* eceCity);

void affichageHover(SimWorld_t* eceCity);

void texteDebug(SimWorld_t* eceCity);

void affichageTypeBloc(SimWorld_t* eceCity);

void transfertMatriceEnTypeBloc(SimWorld_t* eceCity);

void typeBlocRoute(SimWorld_t* eceCity);

void actionReloadMatrice(SimWorld_t* eceCity);


#endif //ECECITY_CARTE_H
