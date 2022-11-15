
#include "affichage.h"
#include "sim/chateau.h"

enum SPRITE_MAP get_route_sprite_variant(SimWorld_t *eceCity, int x, int y) {
    if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
        eceCity->map[x][y - 1].type == KIND_ROUTE &&
        eceCity->map[x + 1][y].type == KIND_ROUTE &&
        eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_14;
    } else if (eceCity->map[x - 1][y].type == KIND_ROUTE &&
               eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_13;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_12;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_11;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_10;
    } else if (eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_9;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_8;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_7;
    } else if (eceCity->map[x][y - 1].type == KIND_ROUTE &&
               eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_6;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
               eceCity->map[x][y - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_5;
    } else if (eceCity->map[x + 1][y].type == KIND_ROUTE &&
               eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_4;
    } else if (eceCity->map[x - 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_3;
    } else if (eceCity->map[x][y + 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_2;
    } else if (eceCity->map[x + 1][y].type == KIND_ROUTE) {
        return SPRITE_ROUTE_1;
    } else if (eceCity->map[x][y - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_0;
    }

    return SPRITE_ROUTE_0;
}

void affichage_draw_terrain_background(SpriteSheet_t *sheet, SimWorld_t *world) {
    for (int i = 0; i < 45; ++i) {
        for (int j = 0; j < 35; ++j) {
            switch (world->map[i][j].type) {

                case KIND_ROUTE:
                    sprite_sheet_draw_sprite(sheet, get_route_sprite_variant(world, i, j), WHITE, i, j);
                    break;

                default:
                    sprite_sheet_draw_sprite(sheet, SPRITE_TERRAIN_0, WHITE, i, j);
                    break;
            }
        }
    }
}

/// Dessine les tuiles de la carte.
void affichage_draw_entities(SpriteSheet_t *sheet, SimWorld_t *world, enum RenderLayer layers) {

    Color centralesColor = (layers & LAYER_CENTRALES) != 0 ? WHITE : ColorAlpha(WHITE, 0.5f);
    struct Maillon_t *centrales = world->centrales->premier;
    while (centrales) {
        CentraleElectrique_t *centrale = (CentraleElectrique_t *) centrales->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_ENERGY_6X4, centralesColor, centrale->position.x, centrale->position.y);
        centrales = centrales->next;
    }

    Color chateauxColor = (layers & LAYER_CHATEAUX) != 0 ? WHITE : ColorAlpha(WHITE, 0.5f);
    struct Maillon_t *chateaux = world->chateaux->premier;
    while (chateaux) {
        ChateauEau_t *chateau = (ChateauEau_t *) chateaux->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_EAU_4X6, chateauxColor, chateau->position.x, chateau->position.y);
        chateaux = chateaux->next;
    }


    Color routesColor = (layers & LAYER_HABITATIONS) != 0 ? WHITE : ColorAlpha(WHITE, 0.5f);
    struct Maillon_t *maison = world->habitations->premier;
    while (maison) {
        Habitation_t *hab = (Habitation_t *) maison->data;
        affichage_draw_habitation(sheet, hab, routesColor);
        maison = maison->next;
    }
}

void affichage_draw_build_preview(SpriteSheet_t *sheet, SimWorld_t *world, Vector2I v, CaseKind_t type) {
    int w = 0;
    int h = 0;
    enum SPRITE_MAP bat = SPRITE_HOOVER;
    switch (type) {
        case KIND_ROUTE:
            w = 1;
            h = 1;
            bat = SPRITE_ROUTE_0;
            break;

        case KIND_HABITATION:
            w = 3;
            h = 3;
            bat = SPRITE_MAISON_3X3;
            break;

        case KIND_CENTRALE:
            w = 6;
            h = 4;
            bat = SPRITE_ENERGY_6X4;
            break;

        case KIND_CHATEAU:
            w = 4;
            h = 6;
            bat = SPRITE_EAU_4X6;
            break;

        default:
            break;
    }

    bool is_valid = sim_check_can_place(world, w > 1, v.x, v.y, w, h);
    sprite_sheet_draw_sprite(sheet, bat, is_valid ? GREEN : RED, v.x, v.y);
}

void affichage_draw_habitation(SpriteSheet_t *sheet, Habitation_t *habitation, Color teinte) {
    enum SPRITE_MAP habitation_sprite = SPRITE_TERRAIN_VAGUE_3X3;

    switch (habitation->niveau) {
        case NIVEAU_CABANE:
            habitation_sprite = SPRITE_CABANE_3X3;
            break;

        case NIVEAU_MAISON:
            habitation_sprite = SPRITE_MAISON_3X3;
            break;

        case NIVEAU_GRATTE_CIEL:
            habitation_sprite = SPRITE_GRATTE_CIEL_3X3;
            break;

        case NIVEAU_RUINE:
            habitation_sprite = SPRITE_RUINE_3X3;
            break;

        case NIVEAU_TERRAIN_VAGUE:
            habitation_sprite = SPRITE_TERRAIN_VAGUE_3X3;
            break;

        case NIVEAU_IMMEUBLE:
            habitation_sprite = SPRITE_IMMEUBLE_3X3;
            break;

        default:
            break;
    }

    sprite_sheet_draw_sprite(sheet, habitation_sprite, teinte, habitation->position.x, habitation->position.y);
}

void affichage_debug_draw_voisins_chateau(SpriteSheet_t* sheet, ChateauEau_t* chateau, Color teinte) {
    sprite_sheet_draw_sprite(sheet, SPRITE_EAU_4X6, teinte, chateau->position.x, chateau->position.y);

    struct Maillon_t* voisins = chateau->habitations->premier;
    int no = 0;
    while (voisins) {
        Habitation_t* hab = (Habitation_t*) voisins->data;
        affichage_draw_habitation(sheet, hab, teinte);
        int oX = (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR/2) - hab->position.y * (SPRITELARGEUR/2);
        int oY = (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR/2) + hab->position.x * (SPRITEHAUTEUR/2);
        DrawText(TextFormat("#%d", no), oX, oY, 20, WHITE);
        voisins = voisins->next;
        no++;
    }
}

void affichage_debug_draw_voisins_centrale(SpriteSheet_t* sheet, CentraleElectrique_t* centrale, Color teinte) {
    sprite_sheet_draw_sprite(sheet, SPRITE_ENERGY_6X4, teinte, centrale->position.x, centrale->position.y);
    struct Maillon_t* voisins = centrale->habitations->premier;
    int no = 0;
    while (voisins) {
        Habitation_t* hab = (Habitation_t*) voisins->data;
        affichage_draw_habitation(sheet, hab, teinte);
        int oX = (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR/2) - hab->position.y * (SPRITELARGEUR/2);
        int oY = (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR/2) + hab->position.x * (SPRITEHAUTEUR/2);
        DrawText(TextFormat("#%d", no), oX, oY, 20, WHITE);
        voisins = voisins->next;
        no++;
    }
}