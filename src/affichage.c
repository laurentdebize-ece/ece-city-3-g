
#include "affichage.h"
#include "sim/chateau.h"

void affichage_draw_terrain_background(SpriteSheet_t* sheet, SimWorld_t* world) {
    for (int i = 0; i < 45; ++i) {
        for (int j = 0; j < 35; ++j) {
            if (world->map[i][j].type == Vide) {
                sprite_sheet_draw_sprite(sheet, TERRAIN_0, WHITE, i, j);
            }
        }
    }
}

/// Dessine les tuiles de la carte.
void affichage_draw_entities(SpriteSheet_t* sheet, SimWorld_t* world) {
    struct Maillon_t* route = world->routes->premier;
    while (route) {
        Route_t* r = (Route_t*) route->data;
        sprite_sheet_draw_sprite(sheet, ROUTE_0, WHITE, r->position.x, r->position.y);
        route = route->next;
    }

    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        sprite_sheet_draw_sprite(sheet, MAISON_3X3, WHITE, hab->position.x, hab->position.y);
        maison = maison->next;
    }

    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        CentraleElectrique_t* centrale = (CentraleElectrique_t*)centrales->data;
        sprite_sheet_draw_sprite(sheet, ENERGY_6X4, WHITE, centrale->position.x, centrale->position.y);
        centrales = centrales->next;
    }

    struct Maillon_t* chateaux = world->chateaux->premier;
    while (chateaux) {
        ChateauEau_t* chateau = (ChateauEau_t*) chateaux->data;
        sprite_sheet_draw_sprite(sheet, EAU_4X6, WHITE, chateau->position.x, chateau->position.y);
        chateaux = chateaux->next;
    }
}