#ifndef ECECITY_SAUVEGARDE_H
#define ECECITY_SAUVEGARDE_H

#include "sim/sim.h"
#include <stdio.h>
#include <assert.h>

/// Sauvegarde la partie dans un fichier.
void sim_sauvegarder(SimWorld_t* world, const char* nomFichier);

/// Charge une partie depuis un fichier.
void sim_charger(SimWorld_t* world, const char* nomFichier);

#endif //ECECITY_SAUVEGARDE_H
