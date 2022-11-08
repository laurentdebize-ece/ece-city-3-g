#include "batiment.h"

void selectionModePlacementBatiment(SimWorld_t *eceCity) {
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1082, 954, 40, 40})) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            //Actions Click New Road
            eceCity->informationsSouris.effetsGraphiques.modePlacementHabitation = !eceCity->informationsSouris.effetsGraphiques.modePlacementHabitation;
        }
    }
}

bool checkCollisionPlacement3X3(SimWorld_t *eceCity) {
    int x = eceCity->informationsSouris.celluleIso.x;
    int y = eceCity->informationsSouris.celluleIso.y;

    if (!eceCity->informationsSouris.outOfMapBorders) {
        if (eceCity->matrice[y][x] == '0' &&
            eceCity->matrice[y][x + 1] == '0' &&
            eceCity->matrice[y][x + 2] == '0' &&
            eceCity->matrice[y + 1][x] == '0' &&
            eceCity->matrice[y + 1][x + 1] == '0' &&
            eceCity->matrice[y + 1][x + 2] == '0' &&
            eceCity->matrice[y + 2][x] == '0' &&
            eceCity->matrice[y + 2][x + 1] == '0' &&
            eceCity->matrice[y + 2][x + 2] == '0') {
            return true; //Pas de collision
        }
    }
    return false; //Collision
}

bool checkConditionsRoutePlacement3X3(SimWorld_t *eceCity) {
    int x = eceCity->informationsSouris.celluleIso.x;
    int y = eceCity->informationsSouris.celluleIso.y;

    if (eceCity->matrice[y][x - 1] == 'R' ||
        eceCity->matrice[y + 1][x - 1] == 'R' ||
        eceCity->matrice[y + 2][x - 1] == 'R' ||
        eceCity->matrice[y][x + 3] == 'R' ||
        eceCity->matrice[y + 1][x + 3] == 'R' ||
        eceCity->matrice[y + 2][x + 3] == 'R' ||
        eceCity->matrice[y + 3][x + 2] == 'R' ||
        eceCity->matrice[y + 3][x + 1] == 'R' ||
        eceCity->matrice[y + 3][x] == 'R' ||
        eceCity->matrice[y - 1][x] == 'R' ||
        eceCity->matrice[y - 1][x + 1] == 'R' ||
        eceCity->matrice[y - 1][x + 2] == 'R') {
        return true; //on peut placer le batiment
    }

    return false; //on ne peut pas placer le batiment

}

void affichagePlacementTemporaireTerrainVague(SimWorld_t *eceCity) {
    if (eceCity->informationsSouris.effetsGraphiques.modePlacementHabitation) {
        if (checkConditionsRoutePlacement3X3(eceCity) && checkCollisionPlacement3X3(eceCity)) {
            DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                           eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].rectangle,
                           (Vector2) {isometricCoordsToScreenX(eceCity) +
                                      eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].decalageXDecor,
                                      isometricCoordsToScreenY(eceCity) +
                                      eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].decalageYDecor}, GREEN);
        } else {
            DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                           eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].rectangle,
                           (Vector2) {isometricCoordsToScreenX(eceCity) +
                                      eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].decalageXDecor,
                                      isometricCoordsToScreenY(eceCity) +
                                      eceCity->carte.spriteSheet[TERRAIN_VAGUE_3X3].decalageYDecor}, RED);
        }
    }
}

void modePlacementBatiment(SimWorld_t *eceCity) {
    if (eceCity->informationsSouris.effetsGraphiques.modePlacementHabitation) {
        if (!eceCity->informationsSouris.outOfMapBorders) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (checkConditionsRoutePlacement3X3(eceCity) && checkCollisionPlacement3X3(eceCity)) {
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x] = 'T';
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y][
                            eceCity->informationsSouris.celluleIso.x + 1] = 'T';
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y][
                            eceCity->informationsSouris.celluleIso.x + 2] = 'T';
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y +
                                     1][eceCity->informationsSouris.celluleIso.x] = 'T';
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][
                            eceCity->informationsSouris.celluleIso.x + 1] = 'T';
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][
                            eceCity->informationsSouris.celluleIso.x + 2] = 'T';
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y +
                                     2][eceCity->informationsSouris.celluleIso.x] = 'T';
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][
                            eceCity->informationsSouris.celluleIso.x + 1] = 'T';
                    eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][
                            eceCity->informationsSouris.celluleIso.x + 2] = 'T';
                    eceCity->carte.reloadMatrice = true;
                    eceCity->informationsSouris.effetsGraphiques.modePlacementHabitation = false;
                }
            }
        }
    }
}

void selectionModePlacementCentraleElec(SimWorld_t *eceCity) {
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1159, 954, 40, 40})) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            //Actions Click New Road
            eceCity->informationsSouris.effetsGraphiques.modePlacementCentrale = !eceCity->informationsSouris.effetsGraphiques.modePlacementCentrale;
        }
    }
}

bool checkCollisionPlacement4X6(SimWorld_t *eceCity) {
    int x = eceCity->informationsSouris.celluleIso.x;
    int y = eceCity->informationsSouris.celluleIso.y;

    if (!eceCity->informationsSouris.outOfMapBorders) {
        if (eceCity->matrice[y][x] == '0' &&
            eceCity->matrice[y][x + 1] == '0' &&
            eceCity->matrice[y][x + 2] == '0' &&
            eceCity->matrice[y][x + 3] == '0' &&
            eceCity->matrice[y + 1][x] == '0' &&
            eceCity->matrice[y + 1][x + 1] == '0' &&
            eceCity->matrice[y + 1][x + 2] == '0' &&
            eceCity->matrice[y + 1][x + 3] == '0' &&
            eceCity->matrice[y + 2][x] == '0' &&
            eceCity->matrice[y + 2][x + 1] == '0' &&
            eceCity->matrice[y + 2][x + 2] == '0' &&
            eceCity->matrice[y + 2][x + 3] == '0' &&
            eceCity->matrice[y + 3][x] == '0' &&
            eceCity->matrice[y + 3][x + 1] == '0' &&
            eceCity->matrice[y + 3][x + 2] == '0' &&
            eceCity->matrice[y + 3][x + 3] == '0' &&
            eceCity->matrice[y + 4][x] == '0' &&
            eceCity->matrice[y + 4][x + 1] == '0' &&
            eceCity->matrice[y + 4][x + 2] == '0' &&
            eceCity->matrice[y + 4][x + 3] == '0' &&
            eceCity->matrice[y + 5][x] == '0' &&
            eceCity->matrice[y + 5][x + 1] == '0' &&
            eceCity->matrice[y + 5][x + 2] == '0' &&
            eceCity->matrice[y + 5][x + 3] == '0') {
            return true; //Pas de collision
        }
    }
    return false; //Collision
}

bool checkCollisionPlacement6X4(SimWorld_t *eceCity) {
    int x = eceCity->informationsSouris.celluleIso.x;
    int y = eceCity->informationsSouris.celluleIso.y;

    if (!eceCity->informationsSouris.outOfMapBorders) {
        if (eceCity->matrice[y][x] == '0' &&
            eceCity->matrice[y][x + 1] == '0' &&
            eceCity->matrice[y][x + 2] == '0' &&
            eceCity->matrice[y][x + 3] == '0' &&
            eceCity->matrice[y][x + 4] == '0' &&
            eceCity->matrice[y][x + 5] == '0' &&
            eceCity->matrice[y + 1][x] == '0' &&
            eceCity->matrice[y + 1][x + 1] == '0' &&
            eceCity->matrice[y + 1][x + 2] == '0' &&
            eceCity->matrice[y + 1][x + 3] == '0' &&
            eceCity->matrice[y + 1][x + 4] == '0' &&
            eceCity->matrice[y + 1][x + 5] == '0' &&
            eceCity->matrice[y + 2][x] == '0' &&
            eceCity->matrice[y + 2][x + 1] == '0' &&
            eceCity->matrice[y + 2][x + 2] == '0' &&
            eceCity->matrice[y + 2][x + 3] == '0' &&
            eceCity->matrice[y + 2][x + 4] == '0' &&
            eceCity->matrice[y + 2][x + 5] == '0' &&
            eceCity->matrice[y + 3][x] == '0' &&
            eceCity->matrice[y + 3][x + 1] == '0' &&
            eceCity->matrice[y + 3][x + 2] == '0' &&
            eceCity->matrice[y + 3][x + 3] == '0' &&
            eceCity->matrice[y + 3][x + 4] == '0' &&
            eceCity->matrice[y + 3][x + 5] == '0') {
            return true; //Pas de collision
        }
    }
    return false; //Collision
}

bool checkConditionsRoutePlacement4X6(SimWorld_t *eceCity) {
    int x = eceCity->informationsSouris.celluleIso.x;
    int y = eceCity->informationsSouris.celluleIso.y;

    if (eceCity->matrice[y][x - 1] == 'R' ||
        eceCity->matrice[y + 1][x - 1] == 'R' ||
        eceCity->matrice[y + 2][x - 1] == 'R' ||
        eceCity->matrice[y + 3][x - 1] == 'R' ||
        eceCity->matrice[y + 4][x - 1] == 'R' ||
        eceCity->matrice[y + 5][x - 1] == 'R' ||
        eceCity->matrice[y + 6][x - 1] == 'R' ||
        eceCity->matrice[y][x + 4] == 'R' ||
        eceCity->matrice[y + 1][x + 4] == 'R' ||
        eceCity->matrice[y + 2][x + 4] == 'R' ||
        eceCity->matrice[y + 3][x + 4] == 'R' ||
        eceCity->matrice[y + 4][x + 4] == 'R' ||
        eceCity->matrice[y + 5][x + 4] == 'R' ||
        eceCity->matrice[y + 6][x + 4] == 'R' ||
        eceCity->matrice[y + 7][x] == 'R' ||
        eceCity->matrice[y + 7][x + 1] == 'R' ||
        eceCity->matrice[y + 7][x + 2] == 'R' ||
        eceCity->matrice[y + 7][x + 3] == 'R' ||
        eceCity->matrice[y - 1][x] == 'R' ||
        eceCity->matrice[y - 1][x + 1] == 'R' ||
        eceCity->matrice[y - 1][x + 2] == 'R' ||
        eceCity->matrice[y - 1][x + 3] == 'R') {
        return true; //on peut placer le batiment
    }
    return false; //on ne peut pas placer le batiment
}

bool checkConditionsRoutePlacement6X4(SimWorld_t *eceCity) {
    int x = eceCity->informationsSouris.celluleIso.x;
    int y = eceCity->informationsSouris.celluleIso.y;

    if (eceCity->matrice[y][x - 1] == 'R' ||
        eceCity->matrice[y + 1][x - 1] == 'R' ||
        eceCity->matrice[y + 2][x - 1] == 'R' ||
        eceCity->matrice[y + 3][x - 1] == 'R' ||
        eceCity->matrice[y + 4][x] == 'R' ||
        eceCity->matrice[y + 4][x + 1] == 'R' ||
        eceCity->matrice[y + 4][x + 2] == 'R' ||
        eceCity->matrice[y + 4][x + 3] == 'R' ||
        eceCity->matrice[y + 4][x + 4] == 'R' ||
        eceCity->matrice[y + 4][x + 5] == 'R' ||
        eceCity->matrice[y][x + 6] == 'R' ||
        eceCity->matrice[y + 1][x + 6] == 'R' ||
        eceCity->matrice[y + 2][x + 6] == 'R' ||
        eceCity->matrice[y + 3][x + 6] == 'R' ||
        eceCity->matrice[y - 1][x] == 'R' ||
        eceCity->matrice[y - 1][x + 1] == 'R' ||
        eceCity->matrice[y - 1][x + 2] == 'R' ||
        eceCity->matrice[y - 1][x + 3] == 'R' ||
        eceCity->matrice[y - 1][x + 4] == 'R' ||
        eceCity->matrice[y - 1][x + 5] == 'R') {

        return true; //on peut placer le batiment
    }
    return false; //on ne peut pas placer le batiment
}

void affichagePlacementTemporaireCentraleElec(SimWorld_t *eceCity) {
    if (eceCity->informationsSouris.effetsGraphiques.modePlacementCentrale) {
        if(eceCity->informationsSouris.effetsGraphiques.rotationCentraleElec){
            if (checkCollisionPlacement4X6(eceCity) && checkConditionsRoutePlacement4X6(eceCity)) {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[ENERGY_4X6].rectangle,
                               (Vector2) {isometricCoordsToScreenX(eceCity) +
                                          eceCity->carte.spriteSheet[ENERGY_4X6].decalageXDecor,
                                          isometricCoordsToScreenY(eceCity) +
                                          eceCity->carte.spriteSheet[ENERGY_4X6].decalageYDecor}, GREEN);
            } else {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[ENERGY_4X6].rectangle,
                               (Vector2) {isometricCoordsToScreenX(eceCity) +
                                          eceCity->carte.spriteSheet[ENERGY_4X6].decalageXDecor,
                                          isometricCoordsToScreenY(eceCity) +
                                          eceCity->carte.spriteSheet[ENERGY_4X6].decalageYDecor}, RED);
            }
        } else {
            if (checkCollisionPlacement6X4(eceCity) && checkConditionsRoutePlacement6X4(eceCity)) {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[ENERGY_6X4].rectangle,
                               (Vector2) {isometricCoordsToScreenX(eceCity) +
                                          eceCity->carte.spriteSheet[ENERGY_6X4].decalageXDecor,
                                          isometricCoordsToScreenY(eceCity) +
                                          eceCity->carte.spriteSheet[ENERGY_6X4].decalageYDecor}, GREEN);
            } else {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[ENERGY_6X4].rectangle,
                               (Vector2) {isometricCoordsToScreenX(eceCity) +
                                          eceCity->carte.spriteSheet[ENERGY_6X4].decalageXDecor,
                                          isometricCoordsToScreenY(eceCity) +
                                          eceCity->carte.spriteSheet[ENERGY_6X4].decalageYDecor}, RED);
            }
        }
    }
}

void modePlacementCentraleElec(SimWorld_t *eceCity) {
    if (eceCity->informationsSouris.effetsGraphiques.modePlacementCentrale) {
        if (!eceCity->informationsSouris.outOfMapBorders) {
            if(IsKeyPressed(KEY_R)){
                eceCity->informationsSouris.effetsGraphiques.rotationCentraleElec = !eceCity->informationsSouris.effetsGraphiques.rotationCentraleElec;
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (eceCity->informationsSouris.effetsGraphiques.rotationCentraleElec) {
                    if (checkCollisionPlacement4X6(eceCity) && checkConditionsRoutePlacement4X6(eceCity)) {

                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 4][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 5][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 4][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 5][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 4][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 5][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 4][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 5][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';

                        eceCity->carte.reloadMatrice = true;
                        eceCity->informationsSouris.effetsGraphiques.modePlacementCentrale = false;
                    }
                } else {
                    if (checkCollisionPlacement6X4(eceCity) && checkConditionsRoutePlacement6X4(eceCity)) {

                        //Actualiser la matrice pour placer une centrale 6X4
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 1] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 2] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 3] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 4] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 4] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 4] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 4] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 5] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 5] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 5] = 'Z';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 5] = 'Z';

                        eceCity->carte.reloadMatrice = true;
                        eceCity->informationsSouris.effetsGraphiques.modePlacementCentrale = false;
                    }
                }
            }
        }
    }
}

void selectionModePlacementChateauEau(SimWorld_t *eceCity) {
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1229, 954, 40, 40})) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            //Actions Click New Road
            eceCity->informationsSouris.effetsGraphiques.modePlacementChateau = !eceCity->informationsSouris.effetsGraphiques.modePlacementChateau;
        }
    }
}

void affichagePlacementTemporaireChateauEau(SimWorld_t *eceCity) {
    if (eceCity->informationsSouris.effetsGraphiques.modePlacementChateau) {
        if(eceCity->informationsSouris.effetsGraphiques.rotationChateau){
            if (checkCollisionPlacement4X6(eceCity) && checkConditionsRoutePlacement4X6(eceCity)) {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[EAU_4X6].rectangle,
                               (Vector2) {isometricCoordsToScreenX(eceCity) +
                                          eceCity->carte.spriteSheet[EAU_4X6].decalageXDecor,
                                          isometricCoordsToScreenY(eceCity) +
                                          eceCity->carte.spriteSheet[EAU_4X6].decalageYDecor}, GREEN);
            } else {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[EAU_4X6].rectangle,
                               (Vector2) {isometricCoordsToScreenX(eceCity) +
                                          eceCity->carte.spriteSheet[EAU_4X6].decalageXDecor,
                                          isometricCoordsToScreenY(eceCity) +
                                          eceCity->carte.spriteSheet[EAU_4X6].decalageYDecor}, RED);
            }
        } else {
            if (checkCollisionPlacement6X4(eceCity) && checkConditionsRoutePlacement6X4(eceCity)) {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[EAU_6X4].rectangle,
                               (Vector2) {isometricCoordsToScreenX(eceCity) +
                                          eceCity->carte.spriteSheet[EAU_6X4].decalageXDecor,
                                          isometricCoordsToScreenY(eceCity) +
                                          eceCity->carte.spriteSheet[EAU_6X4].decalageYDecor}, GREEN);
            } else {
                DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                               eceCity->carte.spriteSheet[EAU_6X4].rectangle,
                               (Vector2) {isometricCoordsToScreenX(eceCity) +
                                          eceCity->carte.spriteSheet[EAU_6X4].decalageXDecor,
                                          isometricCoordsToScreenY(eceCity) +
                                          eceCity->carte.spriteSheet[EAU_6X4].decalageYDecor}, RED);
            }
        }
    }
}

void modePlacementChateauEau(SimWorld_t *eceCity) {
    if (eceCity->informationsSouris.effetsGraphiques.modePlacementChateau) {
        if (!eceCity->informationsSouris.outOfMapBorders) {
            if(IsKeyPressed(KEY_R)){
                eceCity->informationsSouris.effetsGraphiques.rotationChateau = !eceCity->informationsSouris.effetsGraphiques.rotationChateau;
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (eceCity->informationsSouris.effetsGraphiques.rotationChateau) {
                    if (checkCollisionPlacement4X6(eceCity) && checkConditionsRoutePlacement4X6(eceCity)) {

                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 4][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 5][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 4][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 5][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 4][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 5][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 4][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 5][eceCity->informationsSouris.celluleIso.x + 3] = 'E';

                        eceCity->carte.reloadMatrice = true;
                        eceCity->informationsSouris.effetsGraphiques.modePlacementChateau= false;
                    }
                } else {
                    if (checkCollisionPlacement6X4(eceCity) && checkConditionsRoutePlacement6X4(eceCity)) {

                        //Actualiser la matrice pour placer une centrale 6X4
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 1] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 2] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 3] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 4] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 4] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 4] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 4] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y][eceCity->informationsSouris.celluleIso.x + 5] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 1][eceCity->informationsSouris.celluleIso.x + 5] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 2][eceCity->informationsSouris.celluleIso.x + 5] = 'E';
                        eceCity->matrice[eceCity->informationsSouris.celluleIso.y + 3][eceCity->informationsSouris.celluleIso.x + 5] = 'E';

                        eceCity->carte.reloadMatrice = true;
                        eceCity->informationsSouris.effetsGraphiques.modePlacementChateau = false;
                    }
                }
            }
        }
    }
}