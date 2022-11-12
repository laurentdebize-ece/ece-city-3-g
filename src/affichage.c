#include "affichage.h"
#include "sim/chateau.h"
#include "screens/gameplay.h"

enum SPRITE_MAP get_route_sprite_variant(SimWorld_t *eceCity, int x, int y) {
    if (eceCity->map[y + 1][x].type == KIND_ROUTE &&
        eceCity->map[y - 1][x].type == KIND_ROUTE &&
        eceCity->map[y][x + 1].type == KIND_ROUTE &&
        eceCity->map[y][x - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_14;
    } else if (eceCity->map[y][x - 1].type == KIND_ROUTE &&
               eceCity->map[y - 1][x].type == KIND_ROUTE &&
               eceCity->map[y][x + 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_13;
    } else if (eceCity->map[y + 1][x].type == KIND_ROUTE &&
               eceCity->map[y - 1][x].type == KIND_ROUTE &&
               eceCity->map[y][x - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_12;
    } else if (eceCity->map[y + 1][x].type == KIND_ROUTE &&
               eceCity->map[y][x - 1].type == KIND_ROUTE &&
               eceCity->map[y][x + 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_11;
    } else if (eceCity->map[y + 1][x].type == KIND_ROUTE &&
               eceCity->map[y - 1][x].type == KIND_ROUTE &&
               eceCity->map[y][x + 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_10;
    } else if (eceCity->map[y - 1][x].type == KIND_ROUTE &&
               eceCity->map[y][x - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_9;
    } else if (eceCity->map[y + 1][x].type == KIND_ROUTE &&
               eceCity->map[y][x + 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_8;
    } else if (eceCity->map[y + 1][x].type == KIND_ROUTE &&
               eceCity->map[y][x - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_7;
    } else if (eceCity->map[y - 1][x].type == KIND_ROUTE &&
               eceCity->map[y][x + 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_6;
    } else if (eceCity->map[y + 1][x].type == KIND_ROUTE &&
               eceCity->map[y - 1][x].type == KIND_ROUTE) {
        return SPRITE_ROUTE_5;
    } else if (eceCity->map[y][x + 1].type == KIND_ROUTE &&
               eceCity->map[y][x - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_4;
    } else if (eceCity->map[y][x - 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_3;
    } else if (eceCity->map[y + 1][x].type == KIND_ROUTE) {
        return SPRITE_ROUTE_2;
    } else if (eceCity->map[y][x + 1].type == KIND_ROUTE) {
        return SPRITE_ROUTE_1;
    } else if (eceCity->map[y - 1][x].type == KIND_ROUTE) {
        return SPRITE_ROUTE_0;
    }

    return SPRITE_ROUTE_0;
}

/*void affichage_draw_terrain_background(SpriteSheet_t *sheet, SimWorld_t *world) {
    for (int i = 0; i < 45; ++i) {
        for (int j = 0; j < 35; ++j) {
            switch (world->map[j][i].type) {

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
}*/

void affichage_draw_terrain_background(GameplayScreen_t *gameplay) {
    for (int i = 0; i < SIM_MAP_HAUTEUR; ++i) {
        for (int j = 0; j < SIM_MAP_LARGEUR; ++j) {
            if (gameplay->world->map[i][j].sprite != SPRITE_VIDE) {
                DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                               gameplay->spriteSheet.sprites[gameplay->world->map[i][j].sprite].rectangle,
                               (Vector2) {gameplay->world->map[i][j].position.x +
                                          gameplay->spriteSheet.sprites[gameplay->world->map[i][j].sprite].decalageXDecor,
                                          gameplay->world->map[i][j].position.y +
                                          gameplay->spriteSheet.sprites[gameplay->world->map[i][j].sprite].decalageYDecor},
                               WHITE);
            }
        }
    }
}

void affichage_draw_entities(GameplayScreen_t *gameplay, struct Buffer *buffer, int nbBuffer) {
    for (int i = 0; i < nbBuffer; i++) {
        DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                       gameplay->spriteSheet.sprites[buffer[i].typeBloc].rectangle, (Vector2) {
                        gameplay->spriteSheet.sprites[buffer[i].typeBloc].decalageXDecor +
                        gameplay->world->map[(int) buffer[i].position.y][(int) buffer[i].position.x].position.x,
                        gameplay->spriteSheet.sprites[buffer[i].typeBloc].decalageYDecor +
                        gameplay->world->map[(int) buffer[i].position.y][(int) buffer[i].position.x].position.y},
                       WHITE);
    }
}

void draw_map(GameplayScreen_t *gameplay) {

    struct Buffer buffer[100];
    int nbBuffer = 0;

    for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
        for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
            if (gameplay->world->map[y][x].sprite != SPRITE_VIDE) {
                switch (gameplay->world->map[y][x].sprite) {
                    case SPRITE_ENERGY_4X6: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_ENERGY_4X6;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_ENERGY_6X4: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_ENERGY_6X4;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_EAU_4X6: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_EAU_4X6;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_EAU_6X4: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_EAU_6X4;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_TERRAIN_VAGUE_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_TERRAIN_VAGUE_3X3;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_RUINE_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_RUINE_3X3;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_CABANE_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_CABANE_3X3;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_MAISON_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_MAISON_3X3;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_IMMEUBLE_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_IMMEUBLE_3X3;
                        nbBuffer++;
                        break;
                    }
                    case SPRITE_GRATTE_CIEL_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = SPRITE_GRATTE_CIEL_3X3;
                        nbBuffer++;
                        break;
                    }
                    default: {

                        break;
                    }
                }
            }
        }
    }

    affichage_draw_terrain_background(gameplay);
    affichage_draw_entities(gameplay, buffer, nbBuffer);
}

void draw_hover(GameplayScreen_t* gameplay){
    if(!gameplay->state.stateMouse.outOfMapBorders){
        switch (gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].type) {
            case KIND_VIDE:
            {
                DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                               gameplay->spriteSheet.sprites[SPRITE_HOOVER].rectangle,
                               (Vector2) {
                                       gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].position.x,
                                       gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].position.y},
                               GREEN);
                break;
            }
            default:
            {
                DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                               gameplay->spriteSheet.sprites[SPRITE_HOOVER].rectangle,
                               (Vector2) {
                                       gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].position.x,
                                       gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].position.y},
                               RED);
                break;
            }

        }
    }
}

/*
 * void affichage_draw_terrain_background(SpriteSheet_t* sheet, SimWorld_t* world) {
    for (int i = 0; i < 45; ++i) {
        for (int j = 0; j < 35; ++j) {
            switch (world->map[i][j].type) {
                case KIND_VIDE:
                    sprite_sheet_draw_sprite(sheet, SPRITE_TERRAIN_0, WHITE, i, j);
                    break;
                case KIND_ROUTE:
                    sprite_sheet_draw_sprite(sheet, SPRITE_ROUTE_0, WHITE, i, j);
                    break;
                default:
                    break;
            }
        }
    }
}
/// Dessine les tuiles de la carte.
void affichage_draw_entities(SpriteSheet_t* sheet, SimWorld_t* world) {
    //todo: trier les entités a dessiner par ordre croissant de distance à l'origine dans un tableau dynamique.
    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        CentraleElectrique_t* centrale = (CentraleElectrique_t*)centrales->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_ENERGY_6X4, WHITE, centrale->position.x, centrale->position.y);
        centrales = centrales->next;
    }
    struct Maillon_t* chateaux = world->chateaux->premier;
    while (chateaux) {
        ChateauEau_t* chateau = (ChateauEau_t*) chateaux->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_EAU_4X6, WHITE, chateau->position.x, chateau->position.y);
        chateaux = chateaux->next;
    }
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_GRATTE_CIEL_3X3, WHITE, hab->position.x, hab->position.y);
        maison = maison->next;
    }
}
 */