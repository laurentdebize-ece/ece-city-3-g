
#ifndef ECECITY_AFFICHAGE_H
#define ECECITY_AFFICHAGE_H

#include "raylib.h"
#include "sim/sim.h"
#include "spritesheet.h"
#include "screens/gameplay.h"

struct Buffer {
    Vector2 position;
    int typeBloc;
};

/// Dessine le fond de la carte.
void affichage_draw_terrain_background(GameplayScreen_t* gameplay);

/// Dessine les tuiles de la carte.
void affichage_draw_entities(GameplayScreen_t* gameplay, struct Buffer* buffer, int nbBuffer);

void draw_map(GameplayScreen_t *gameplay);

#endif //ECECITY_AFFICHAGE_H
