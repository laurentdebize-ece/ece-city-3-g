#include <utils/liste.h>
#include <sim/habitation.h>
#include <sim/centrale.h>
#include <sim/chateau.h>
#include <screens/gameplay.h>
#ifndef ECECITY_CAPACITE_H
#define ECECITY_CAPACITE_H

void afficher_capacite(SimWorld_t* world);

void afficher_level_eau(SpriteSheet_t* sheet, SimWorld_t* world);

void afficher_level_elec(SpriteSheet_t* sheet, SimWorld_t* world, GameplayScreen_t *gameplay);

void afficher_level(SpriteSheet_t* sheet, SimWorld_t* world, GameplayScreen_t *gameplay);

void afficher_etat_alim_eau(SpriteSheet_t* sheet, SimWorld_t* world);

void afficher_etat_alim_elec(SpriteSheet_t* sheet, SimWorld_t* world);

#endif //ECECITY_CAPACITE_H
