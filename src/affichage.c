
#include "affichage.h"

void affichage_draw_terrain_background(SpriteSheet_t* sheet) {
    for (int i = 0; i < 45; ++i)
        for (int j = 0; j < 35; ++j)
            sprite_sheet_draw_sprite(sheet, TERRAIN_0, WHITE, i, j);
}