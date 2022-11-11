
#ifndef ECECITY_AFFICHAGE_H
#define ECECITY_AFFICHAGE_H

#include <raylib.h>
#include "sim/sim.h"
#include "spritesheet.h"

/// Dessine le fond de la carte.
void affichage_draw_terrain_background(SpriteSheet_t* sheet, SimWorld_t* world);

/// Dessine les tuiles de la carte.
void affichage_draw_entities(SpriteSheet_t* sheet, SimWorld_t* world);

/// Dessine une habitation sur la carte.
void affichage_draw_habitation(SpriteSheet_t* sheet, Habitation_t* habitation);

/// Dessine l'apercu de construction d'un bâtiment sur la carte.
void affichage_draw_build_preview(SpriteSheet_t* sheet, SimWorld_t* world, Vector2I pos, CaseKind_t type);

#endif //ECECITY_AFFICHAGE_H
