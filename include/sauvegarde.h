#ifndef ECECITY_SAUVEGARDE_H
#define ECECITY_SAUVEGARDE_H

#include "screens/gameplay.h"

void affichage_menu_sauvegarde(GameplayScreen_t* gameplay);

void update_menu_sauvegarde(GameplayScreen_t* gameplay);

void sim_sauvegarder(SimWorld_t *world, const char *nomFichier);

#endif
