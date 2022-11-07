
#ifndef ECECITY_AFFICHAGE_H
#define ECECITY_AFFICHAGE_H

#include <raylib.h>
#include "sim/sim.h"
#include "spritesheet.h"

/// Dessine le fond de la carte.
void affichage_draw_terrain_background(SpriteSheet_t* sheet);

/// Dessine les tuiles de la carte.
void affichage_draw_entities(SpriteSheet_t* sheet, SimWorld_t* world);

#endif //ECECITY_AFFICHAGE_H
