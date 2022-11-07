#include "carte.h"
#include "sim/sim.h"
#include "stdio.h"
#include "fichier.h"


void initMap(SimWorld_t *eceCity) {

    eceCity->carte.Origine.celluleX = ORIGINEX;
    eceCity->carte.Origine.celluleY = ORIGINEY;

    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {

            eceCity->carte.mapTile[y][x].spriteLargeur = SPRITELARGEUR;
            eceCity->carte.mapTile[y][x].spriteHauteur = SPRITEHAUTEUR;
            eceCity->carte.mapTile[y][x].spriteHalfHauteur = eceCity->carte.mapTile[y][x].spriteHauteur / 2;
            eceCity->carte.mapTile[y][x].spriteHalfLargeur = eceCity->carte.mapTile[y][x].spriteLargeur / 2;


            //Permet de définir le type de bloc
            eceCity->carte.mapTile[y][x].typeBloc = TERRAIN_0;
            eceCity->carte.mapTile[y][x].tinte = WHITE;

            eceCity->carte.mapTile[y][x].cellulesIso.celluleX = x;
            eceCity->carte.mapTile[y][x].cellulesIso.celluleY = y;

            eceCity->carte.mapTile[y][x].position.x =
                    (eceCity->carte.Origine.celluleX * eceCity->carte.mapTile[y][x].spriteLargeur)
                    +
                    x * eceCity->carte.mapTile[y][x].spriteHalfLargeur
                    -
                    y * eceCity->carte.mapTile[y][x].spriteHalfLargeur;

            eceCity->carte.mapTile[y][x].position.y =
                    (eceCity->carte.Origine.celluleY * eceCity->carte.mapTile[y][x].spriteHauteur)
                    +
                    x * eceCity->carte.mapTile[y][x].spriteHalfHauteur
                    +
                    y * eceCity->carte.mapTile[y][x].spriteHalfHauteur;

        }
    }

    eceCity->carte.spriteSheet[CHEAT].rectangle.height = SPRITEHAUTEUR;
    eceCity->carte.spriteSheet[CHEAT].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[CHEAT].rectangle.x = 0;
    eceCity->carte.spriteSheet[CHEAT].rectangle.y = 0;
    eceCity->carte.spriteSheet[CHEAT].decalageXDecor = 0;
    eceCity->carte.spriteSheet[CHEAT].decalageYDecor = 0;

    eceCity->carte.spriteSheet[HOOVER].rectangle.height = SPRITEHAUTEUR;
    eceCity->carte.spriteSheet[HOOVER].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[HOOVER].rectangle.x = SPRITELARGEUR * HOOVER;
    eceCity->carte.spriteSheet[HOOVER].rectangle.y = 0;
    eceCity->carte.spriteSheet[HOOVER].decalageXDecor = 0;
    eceCity->carte.spriteSheet[HOOVER].decalageYDecor = 0;

    eceCity->carte.spriteSheet[CONTOUR].rectangle.height = 20;
    eceCity->carte.spriteSheet[CONTOUR].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[CONTOUR].rectangle.x = SPRITELARGEUR * CONTOUR;
    eceCity->carte.spriteSheet[CONTOUR].rectangle.y = 0;
    eceCity->carte.spriteSheet[CONTOUR].decalageXDecor = 0;
    eceCity->carte.spriteSheet[CONTOUR].decalageYDecor = 0;

    eceCity->carte.spriteSheet[TERRAIN_0].rectangle.height = 26;
    eceCity->carte.spriteSheet[TERRAIN_0].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[TERRAIN_0].rectangle.x = SPRITELARGEUR * TERRAIN_0;
    eceCity->carte.spriteSheet[TERRAIN_0].rectangle.y = 0;
    eceCity->carte.spriteSheet[TERRAIN_0].decalageXDecor = 0;
    eceCity->carte.spriteSheet[TERRAIN_0].decalageYDecor = 0;

    eceCity->carte.spriteSheet[TERRAIN_1].rectangle.height = 26;
    eceCity->carte.spriteSheet[TERRAIN_1].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[TERRAIN_1].rectangle.x = SPRITELARGEUR * TERRAIN_1;
    eceCity->carte.spriteSheet[TERRAIN_1].rectangle.y = 0;
    eceCity->carte.spriteSheet[TERRAIN_1].decalageXDecor = 0;
    eceCity->carte.spriteSheet[TERRAIN_1].decalageYDecor = 0;

    eceCity->carte.spriteSheet[TERRAIN_2].rectangle.height = 26;
    eceCity->carte.spriteSheet[TERRAIN_2].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[TERRAIN_2].rectangle.x = SPRITELARGEUR * TERRAIN_2;
    eceCity->carte.spriteSheet[TERRAIN_2].rectangle.y = 0;
    eceCity->carte.spriteSheet[TERRAIN_2].decalageXDecor = 0;
    eceCity->carte.spriteSheet[TERRAIN_2].decalageYDecor = 0;

    eceCity->carte.spriteSheet[TERRAIN_3].rectangle.height = 36;
    eceCity->carte.spriteSheet[TERRAIN_3].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[TERRAIN_3].rectangle.x = SPRITELARGEUR * TERRAIN_3;
    eceCity->carte.spriteSheet[TERRAIN_3].rectangle.y = 0;
    eceCity->carte.spriteSheet[TERRAIN_3].decalageXDecor = 0;
    eceCity->carte.spriteSheet[TERRAIN_3].decalageYDecor = -10;

    eceCity->carte.spriteSheet[TERRAIN_4].rectangle.height = 26;
    eceCity->carte.spriteSheet[TERRAIN_4].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[TERRAIN_4].rectangle.x = SPRITELARGEUR * TERRAIN_4;
    eceCity->carte.spriteSheet[TERRAIN_4].rectangle.y = 0;
    eceCity->carte.spriteSheet[TERRAIN_4].decalageXDecor = 0;
    eceCity->carte.spriteSheet[TERRAIN_4].decalageYDecor = 0;

    eceCity->carte.spriteSheet[TERRAIN_5].rectangle.height = 26;
    eceCity->carte.spriteSheet[TERRAIN_5].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[TERRAIN_5].rectangle.x = SPRITELARGEUR * TERRAIN_5;
    eceCity->carte.spriteSheet[TERRAIN_5].rectangle.y = 0;
    eceCity->carte.spriteSheet[TERRAIN_5].decalageXDecor = 0;
    eceCity->carte.spriteSheet[TERRAIN_5].decalageYDecor = 0;

    eceCity->carte.spriteSheet[TERRAIN_6].rectangle.height = 26;
    eceCity->carte.spriteSheet[TERRAIN_6].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[TERRAIN_6].rectangle.x = SPRITELARGEUR * TERRAIN_6;
    eceCity->carte.spriteSheet[TERRAIN_6].rectangle.y = 0;
    eceCity->carte.spriteSheet[TERRAIN_6].decalageXDecor = 0;
    eceCity->carte.spriteSheet[TERRAIN_6].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_0].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_0].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_0].rectangle.x = SPRITELARGEUR * ROUTE_0;
    eceCity->carte.spriteSheet[ROUTE_0].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_0].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_0].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_1].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_1].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_1].rectangle.x = SPRITELARGEUR * ROUTE_1;
    eceCity->carte.spriteSheet[ROUTE_1].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_1].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_1].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_2].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_2].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_2].rectangle.x = SPRITELARGEUR * ROUTE_2;
    eceCity->carte.spriteSheet[ROUTE_2].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_2].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_2].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_3].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_3].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_3].rectangle.x = SPRITELARGEUR * ROUTE_3;
    eceCity->carte.spriteSheet[ROUTE_3].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_3].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_3].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_4].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_4].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_4].rectangle.x = SPRITELARGEUR * ROUTE_4;
    eceCity->carte.spriteSheet[ROUTE_4].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_4].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_4].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_5].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_5].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_5].rectangle.x = SPRITELARGEUR * ROUTE_5;
    eceCity->carte.spriteSheet[ROUTE_5].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_5].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_5].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_6].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_6].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_6].rectangle.x = SPRITELARGEUR * ROUTE_6;
    eceCity->carte.spriteSheet[ROUTE_6].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_6].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_6].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_7].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_7].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_7].rectangle.x = SPRITELARGEUR * ROUTE_7;
    eceCity->carte.spriteSheet[ROUTE_7].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_7].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_7].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_8].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_8].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_8].rectangle.x = SPRITELARGEUR * ROUTE_8;
    eceCity->carte.spriteSheet[ROUTE_8].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_8].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_8].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_9].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_9].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_9].rectangle.x = SPRITELARGEUR * ROUTE_9;
    eceCity->carte.spriteSheet[ROUTE_9].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_9].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_9].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_10].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_10].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_10].rectangle.x = SPRITELARGEUR * ROUTE_10;
    eceCity->carte.spriteSheet[ROUTE_10].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_10].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_10].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_11].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_11].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_11].rectangle.x = SPRITELARGEUR * ROUTE_11;
    eceCity->carte.spriteSheet[ROUTE_11].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_11].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_11].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_12].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_12].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_12].rectangle.x = SPRITELARGEUR * ROUTE_12;
    eceCity->carte.spriteSheet[ROUTE_12].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_12].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_12].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_13].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_13].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_13].rectangle.x = SPRITELARGEUR * ROUTE_13;
    eceCity->carte.spriteSheet[ROUTE_13].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_13].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_13].decalageYDecor = 0;

    eceCity->carte.spriteSheet[ROUTE_14].rectangle.height = 26;
    eceCity->carte.spriteSheet[ROUTE_14].rectangle.width = SPRITELARGEUR;
    eceCity->carte.spriteSheet[ROUTE_14].rectangle.x = SPRITELARGEUR * ROUTE_14;
    eceCity->carte.spriteSheet[ROUTE_14].rectangle.y = 0;
    eceCity->carte.spriteSheet[ROUTE_14].decalageXDecor = 0;
    eceCity->carte.spriteSheet[ROUTE_14].decalageYDecor = 0;

    eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].rectangle.height = 70;
    eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].rectangle.width = 120;
    eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].rectangle.x = 1000;
    eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].rectangle.y = 0;
    eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].decalageXDecor = -40;
    eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].decalageYDecor = -1;

    eceCity->carte.spriteSheet[RUINE_3X3].rectangle.height = 70;
    eceCity->carte.spriteSheet[RUINE_3X3].rectangle.width = 120;
    eceCity->carte.spriteSheet[RUINE_3X3].rectangle.x = 1120;
    eceCity->carte.spriteSheet[RUINE_3X3].rectangle.y = 0;
    eceCity->carte.spriteSheet[RUINE_3X3].decalageXDecor = -40;
    eceCity->carte.spriteSheet[RUINE_3X3].decalageYDecor = 0;

    eceCity->carte.spriteSheet[CABANE_3X3].rectangle.height = 75;
    eceCity->carte.spriteSheet[CABANE_3X3].rectangle.width = 120;
    eceCity->carte.spriteSheet[CABANE_3X3].rectangle.x = 1240;
    eceCity->carte.spriteSheet[CABANE_3X3].rectangle.y = 0;
    eceCity->carte.spriteSheet[CABANE_3X3].decalageXDecor = -40;
    eceCity->carte.spriteSheet[CABANE_3X3].decalageYDecor = -(5);

    eceCity->carte.spriteSheet[MAISON_3X3].rectangle.height = 70;
    eceCity->carte.spriteSheet[MAISON_3X3].rectangle.width = 120;
    eceCity->carte.spriteSheet[MAISON_3X3].rectangle.x = 1360;
    eceCity->carte.spriteSheet[MAISON_3X3].rectangle.y = 0;
    eceCity->carte.spriteSheet[MAISON_3X3].decalageXDecor = -40;
    eceCity->carte.spriteSheet[MAISON_3X3].decalageYDecor = -1;

    eceCity->carte.spriteSheet[IMMEUBLE_3X3].rectangle.height = 90;
    eceCity->carte.spriteSheet[IMMEUBLE_3X3].rectangle.width = 120;
    eceCity->carte.spriteSheet[IMMEUBLE_3X3].rectangle.x = 1480;
    eceCity->carte.spriteSheet[IMMEUBLE_3X3].rectangle.y = 0;
    eceCity->carte.spriteSheet[IMMEUBLE_3X3].decalageXDecor = -41;
    eceCity->carte.spriteSheet[IMMEUBLE_3X3].decalageYDecor = -22;

    eceCity->carte.spriteSheet[GRATTE_CIEL_3X3].rectangle.height = 120;
    eceCity->carte.spriteSheet[GRATTE_CIEL_3X3].rectangle.width = 120;
    eceCity->carte.spriteSheet[GRATTE_CIEL_3X3].rectangle.x = 1600;
    eceCity->carte.spriteSheet[GRATTE_CIEL_3X3].rectangle.y = 0;
    eceCity->carte.spriteSheet[GRATTE_CIEL_3X3].decalageXDecor = -40;
    eceCity->carte.spriteSheet[GRATTE_CIEL_3X3].decalageYDecor = -54;

    eceCity->carte.spriteSheet[ENERGY_4X6].rectangle.height = 128;
    eceCity->carte.spriteSheet[ENERGY_4X6].rectangle.width = 200;
    eceCity->carte.spriteSheet[ENERGY_4X6].rectangle.x = 1720;
    eceCity->carte.spriteSheet[ENERGY_4X6].rectangle.y = 0;
    eceCity->carte.spriteSheet[ENERGY_4X6].decalageXDecor = -100;
    eceCity->carte.spriteSheet[ENERGY_4X6].decalageYDecor = -22;

    eceCity->carte.spriteSheet[ENERGY_6X4].rectangle.height = 128;
    eceCity->carte.spriteSheet[ENERGY_6X4].rectangle.width = 200;
    eceCity->carte.spriteSheet[ENERGY_6X4].rectangle.x = 1920;
    eceCity->carte.spriteSheet[ENERGY_6X4].rectangle.y = 0;
    eceCity->carte.spriteSheet[ENERGY_6X4].decalageXDecor = -60;
    eceCity->carte.spriteSheet[ENERGY_6X4].decalageYDecor = -22;

    eceCity->carte.spriteSheet[EAU_4X6].rectangle.height = 136;
    eceCity->carte.spriteSheet[EAU_4X6].rectangle.width = 200;
    eceCity->carte.spriteSheet[EAU_4X6].rectangle.x = 2120;
    eceCity->carte.spriteSheet[EAU_4X6].rectangle.y = 0;
    eceCity->carte.spriteSheet[EAU_4X6].decalageXDecor = -100;
    eceCity->carte.spriteSheet[EAU_4X6].decalageYDecor = -29;

    eceCity->carte.spriteSheet[EAU_6X4].rectangle.height = 130;
    eceCity->carte.spriteSheet[EAU_6X4].rectangle.width = 200;
    eceCity->carte.spriteSheet[EAU_6X4].rectangle.x = 2320;
    eceCity->carte.spriteSheet[EAU_6X4].rectangle.y = 0;
    eceCity->carte.spriteSheet[EAU_6X4].decalageXDecor = -60;
    eceCity->carte.spriteSheet[EAU_6X4].decalageYDecor = -22;

}

void afficherFondMap(SimWorld_t *eceCity) {

    struct Buffer {
        Vector2D position;
        int typeBloc;
    };

    struct Buffer buffer[100];
    int nbBuffer = 0;

    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if (eceCity->carte.mapTile[y][x].typeBloc != VIDE) {

                switch (eceCity->carte.mapTile[y][x].typeBloc) {

                    case ENERGY_4X6: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = ENERGY_4X6;
                        nbBuffer++;
                        break;
                    }

                    case ENERGY_6X4: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = ENERGY_6X4;
                        nbBuffer++;
                        break;
                    }

                    case EAU_4X6: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = EAU_4X6;
                        nbBuffer++;
                        break;
                    }

                    case EAU_6X4: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = EAU_6X4;
                        nbBuffer++;
                        break;
                    }

                    case TERRAIN_VAGUE_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = TERRAIN_VAGUE_3X3;
                        nbBuffer++;
                        break;
                    }

                    case RUINE_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = RUINE_3X3;
                        nbBuffer++;
                        break;
                    }

                    case CABANE_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = CABANE_3X3;
                        nbBuffer++;
                        break;
                    }

                    case MAISON_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = MAISON_3X3;
                        nbBuffer++;
                        break;
                    }

                    case IMMEUBLE_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = IMMEUBLE_3X3;
                        nbBuffer++;
                        break;
                    }

                    case GRATTE_CIEL_3X3: {
                        buffer[nbBuffer].position.x = x;
                        buffer[nbBuffer].position.y = y;
                        buffer[nbBuffer].typeBloc = GRATTE_CIEL_3X3;
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

    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if (eceCity->carte.mapTile[y][x].typeBloc != VIDE) {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[eceCity->carte.mapTile[y][x].typeBloc].rectangle,
                               (Vector2) {
                                       (float) eceCity->carte.spriteSheet[eceCity->carte.mapTile[y][x].typeBloc].decalageXDecor +
                                       (float) eceCity->carte.mapTile[y][x].position.x,
                                       (float) eceCity->carte.mapTile[y][x].position.y +
                                       (float) eceCity->carte.spriteSheet[eceCity->carte.mapTile[y][x].typeBloc].decalageYDecor},
                               eceCity->carte.mapTile[y][x].tinte);
            }
        }
    }

    for (int i = 0; i < nbBuffer; i++) {
        DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                       eceCity->carte.spriteSheet[buffer[i].typeBloc].rectangle, (Vector2) {
                        (float) eceCity->carte.spriteSheet[buffer[i].typeBloc].decalageXDecor +
                        (float) eceCity->carte.mapTile[buffer[i].position.y][buffer[i].position.x].position.x,
                        (float) eceCity->carte.mapTile[buffer[i].position.y][buffer[i].position.x].position.y +
                        (float) eceCity->carte.spriteSheet[buffer[i].typeBloc].decalageYDecor},
                       WHITE);
    }
}

void affichageHover(SimWorld_t *eceCity) {
    if (!eceCity->informationsSouris.outOfMapBorders) {
        if (eceCity->informationsSouris.celluleIso.x >= 0 &&
            eceCity->informationsSouris.celluleIso.x < NBCELLULEX &&
            eceCity->informationsSouris.celluleIso.y >= 0 &&
            eceCity->informationsSouris.celluleIso.y < NBCELLULEY) {
            if (eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x] ==
                '0') {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture, eceCity->carte.spriteSheet[HOOVER].rectangle,
                               isometricCoordsToScreen(eceCity), WHITE);
            } else {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture, eceCity->carte.spriteSheet[HOOVER].rectangle,
                               isometricCoordsToScreen(eceCity), RED);
            }

        }
    }
}

void texteDebug(SimWorld_t *eceCity) {
    char buffer[100];
    sprintf(buffer, "x: %d, y: %d", eceCity->informationsSouris.celluleIso.x,
            eceCity->informationsSouris.celluleIso.y);
    DrawText(buffer, 10, 10, 20, BLACK);
}

void transfertMatriceEnTypeBloc(SimWorld_t *eceCity) {

    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if (eceCity->matrice[y][x] == '0') {
                eceCity->carte.mapTile[y][x].typeBloc = TERRAIN_0;
                //(rand() % (TERRAIN_6 - TERRAIN_0 + 1) + TERRAIN_0);
            }

            if (eceCity->matrice[y][x] == 'R') {
                eceCity->carte.mapTile[y][x].typeBloc = ROUTE_0;
            }

            if (eceCity->matrice[y][x] == 'T') {
                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == TERRAIN_VAGUE_3X3) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == TERRAIN_VAGUE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == TERRAIN_VAGUE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == TERRAIN_VAGUE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == TERRAIN_VAGUE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == TERRAIN_VAGUE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == TERRAIN_VAGUE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == TERRAIN_VAGUE_3X3)) {
                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;
                } else {
                    eceCity->carte.mapTile[y][x].typeBloc = TERRAIN_VAGUE_3X3;
                }
            }

            if (eceCity->matrice[y][x] == 'B') {
                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == RUINE_3X3) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == RUINE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == RUINE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == RUINE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == RUINE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == RUINE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == RUINE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == RUINE_3X3)) {
                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;
                } else {
                    eceCity->carte.mapTile[y][x].typeBloc = RUINE_3X3;
                }
            }

            if (eceCity->matrice[y][x] == 'C') {
                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == CABANE_3X3) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == CABANE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == CABANE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == CABANE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == CABANE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == CABANE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == CABANE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == CABANE_3X3)) {
                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;
                } else {
                    eceCity->carte.mapTile[y][x].typeBloc = CABANE_3X3;
                }
            }

            if (eceCity->matrice[y][x] == 'M') {
                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == MAISON_3X3) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == MAISON_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == MAISON_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == MAISON_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == MAISON_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == MAISON_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == MAISON_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == MAISON_3X3)) {
                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;
                } else {
                    eceCity->carte.mapTile[y][x].typeBloc = MAISON_3X3;
                }
            }

            if (eceCity->matrice[y][x] == 'I') {
                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == IMMEUBLE_3X3) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == IMMEUBLE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == IMMEUBLE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == IMMEUBLE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == IMMEUBLE_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == IMMEUBLE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == IMMEUBLE_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == IMMEUBLE_3X3)) {
                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;
                } else {
                    eceCity->carte.mapTile[y][x].typeBloc = IMMEUBLE_3X3;
                }
            }

            if (eceCity->matrice[y][x] == 'S') {
                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == GRATTE_CIEL_3X3) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == GRATTE_CIEL_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == GRATTE_CIEL_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == GRATTE_CIEL_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == GRATTE_CIEL_3X3) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == GRATTE_CIEL_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == GRATTE_CIEL_3X3) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == GRATTE_CIEL_3X3)) {
                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;
                } else {
                    eceCity->carte.mapTile[y][x].typeBloc = GRATTE_CIEL_3X3;
                }
            }

            if (eceCity->matrice[y][x] == 'Z') {

                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y][x - 3].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 3][x].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 4][x].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 5][x].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 1][x - 3].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 2][x - 3].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 3][x - 1].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 3][x - 2].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 3][x - 3].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 4][x - 1].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 4][x - 2].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 4][x - 3].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 5][x - 1].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 5][x - 2].typeBloc == ENERGY_4X6) ||
                    (eceCity->carte.mapTile[y - 5][x - 3].typeBloc == ENERGY_4X6)) {

                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;

                } else {
                    if (eceCity->matrice[y + 1][x] == 'Z' && eceCity->matrice[y + 2][x] == 'Z'
                        && eceCity->matrice[y + 3][x] == 'Z' && eceCity->matrice[y + 4][x] == 'Z'
                        && eceCity->matrice[y + 5][x] == 'Z' && eceCity->matrice[y][x + 1] == 'Z'
                        && eceCity->matrice[y][x + 2] == 'Z' && eceCity->matrice[y][x + 3] == 'Z') {
                        eceCity->carte.mapTile[y][x].typeBloc = ENERGY_4X6;
                    }
                }


                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y][x - 3].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y][x - 4].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y][x - 5].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 3].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 4].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 5].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 3].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 4].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 5].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 1].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 2].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 3].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 4].typeBloc == ENERGY_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 5].typeBloc == ENERGY_6X4)) {

                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;

                } else {
                    if (eceCity->matrice[y + 1][x] == 'Z' && eceCity->matrice[y + 2][x] == 'Z'
                        && eceCity->matrice[y + 3][x] == 'Z' && eceCity->matrice[y][x + 1] == 'Z'
                        && eceCity->matrice[y][x + 2] == 'Z' && eceCity->matrice[y][x + 3] == 'Z'
                        && eceCity->matrice[y][x + 4] == 'Z' && eceCity->matrice[y][x + 5] == 'Z') {
                        eceCity->carte.mapTile[y][x].typeBloc = ENERGY_6X4;
                    }
                }

            }

            if (eceCity->matrice[y][x] == 'E') {

                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y][x - 3].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 3][x].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 4][x].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 5][x].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 1][x - 3].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 2][x - 3].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 3][x - 1].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 3][x - 2].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 3][x - 3].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 4][x - 1].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 4][x - 2].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 4][x - 3].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 5][x - 1].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 5][x - 2].typeBloc == EAU_4X6) ||
                    (eceCity->carte.mapTile[y - 5][x - 3].typeBloc == EAU_4X6)) {

                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;

                } else {
                    if (eceCity->matrice[y + 1][x] == 'E' && eceCity->matrice[y + 2][x] == 'E'
                        && eceCity->matrice[y + 3][x] == 'E' && eceCity->matrice[y + 4][x] == 'E'
                        && eceCity->matrice[y + 5][x] == 'E' && eceCity->matrice[y][x + 1] == 'E'
                        && eceCity->matrice[y][x + 2] == 'E' && eceCity->matrice[y][x + 3] == 'E') {

                        eceCity->carte.mapTile[y][x].typeBloc = EAU_4X6;
                    }
                }


                if ((eceCity->carte.mapTile[y][x - 1].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y][x - 2].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y][x - 3].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y][x - 4].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y][x - 5].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 1].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 2].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 3].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 4].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 1][x - 5].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 1].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 2].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 3].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 4].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 2][x - 5].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 1].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 2].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 3].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 4].typeBloc == EAU_6X4) ||
                    (eceCity->carte.mapTile[y - 3][x - 5].typeBloc == EAU_6X4)) {
                    eceCity->carte.mapTile[y][x].typeBloc = VIDE;
                } else {
                    if (eceCity->matrice[y + 1][x] == 'E' && eceCity->matrice[y + 2][x] == 'E'
                        && eceCity->matrice[y + 3][x] == 'E' && eceCity->matrice[y][x + 1] == 'E'
                        && eceCity->matrice[y][x + 2] == 'E' && eceCity->matrice[y][x + 3] == 'E'
                        && eceCity->matrice[y][x + 4] == 'E' && eceCity->matrice[y][x + 5] == 'E') {
                        eceCity->carte.mapTile[y][x].typeBloc = EAU_6X4;
                    }
                }
            }

        }
    }

    typeBlocRoute(eceCity);

}

void typeBlocRoute(SimWorld_t *eceCity) {
    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if (eceCity->matrice[y][x] == 'R') {
                if (eceCity->matrice[y + 1][x] == 'R' &&
                    eceCity->matrice[y - 1][x] == 'R' &&
                    eceCity->matrice[y][x + 1] == 'R' &&
                    eceCity->matrice[y][x - 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_14;
                } else if (eceCity->matrice[y][x - 1] == 'R' &&
                           eceCity->matrice[y - 1][x] == 'R' &&
                           eceCity->matrice[y][x + 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_13;
                } else if (eceCity->matrice[y + 1][x] == 'R' &&
                           eceCity->matrice[y - 1][x] == 'R' &&
                           eceCity->matrice[y][x - 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_12;
                } else if (eceCity->matrice[y + 1][x] == 'R' &&
                           eceCity->matrice[y][x - 1] == 'R' &&
                           eceCity->matrice[y][x + 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_11;
                } else if (eceCity->matrice[y + 1][x] == 'R' &&
                           eceCity->matrice[y - 1][x] == 'R' &&
                           eceCity->matrice[y][x + 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_10;
                } else if (eceCity->matrice[y - 1][x] == 'R' &&
                           eceCity->matrice[y][x - 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_9;
                } else if (eceCity->matrice[y + 1][x] == 'R' &&
                           eceCity->matrice[y][x + 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_8;
                } else if (eceCity->matrice[y + 1][x] == 'R' &&
                           eceCity->matrice[y][x - 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_7;
                } else if (eceCity->matrice[y - 1][x] == 'R' &&
                           eceCity->matrice[y][x + 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_6;
                } else if (eceCity->matrice[y + 1][x] == 'R' &&
                           eceCity->matrice[y - 1][x] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_5;
                } else if (eceCity->matrice[y][x + 1] == 'R' &&
                           eceCity->matrice[y][x - 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_4;
                } else if (eceCity->matrice[y][x - 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_3;
                } else if (eceCity->matrice[y + 1][x] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_2;
                } else if (eceCity->matrice[y][x + 1] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_1;
                } else if (eceCity->matrice[y - 1][x] == 'R') {
                    eceCity->carte.mapTile[y][x].typeBloc = ROUTE_0;
                }
            }
        }
    }
}

void affichageTypeBloc(SimWorld_t *eceCity) {
    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {

            printf("%d ", eceCity->carte.mapTile[y][x].typeBloc);

        }
        printf("\n");
    }
}

void actionReloadMatrice(SimWorld_t* eceCity){
    if(eceCity->carte.reloadMatrice){
        transfertMatriceEnTypeBloc(eceCity);
        ecrireFichier(eceCity);
    }
}
