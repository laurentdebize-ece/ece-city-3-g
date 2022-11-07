
#include "affichage.h"

void affichage_draw_terrain_background(SpriteSheet_t* sheet) {
    for (int i = 0; i < 45; ++i)
        for (int j = 0; j < 35; ++j)
            sprite_sheet_draw_sprite(sheet, TERRAIN_0, WHITE, i, j);
}

/// Dessine les tuiles de la carte.
void affichage_draw_entities(SpriteSheet_t* sheet, SimWorld_t* world) {
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        sprite_sheet_draw_sprite(sheet, MAISON_3X3, WHITE, hab->position.x, hab->position.y);
        maison = maison->next;
    }
}