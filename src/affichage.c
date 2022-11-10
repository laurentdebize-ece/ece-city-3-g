#include "affichage.h"
#include "sim/chateau.h"


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