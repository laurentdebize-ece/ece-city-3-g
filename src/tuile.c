#include "tuile.h"

void actualiserPositionSourisJoueur(SimWorld_t*eceCity) {
    int beforeX, beforeY, afterX, afterY;

    beforeX = (int) eceCity->informationsSouris.celluleIso.x; //detecte le chmgt de cellule de la souris
    beforeY = (int) eceCity->informationsSouris.celluleIso.y;

    calculPositionSourisEnCelluleXY(eceCity);

    calculPositionSourisEnCelluleIso(eceCity);

    calculPositionSoursiEnOffsetDansUneCelluleXY(eceCity);

    calculPositionSourisEnCelluleIsoReactualiseeGraceSpriteCheat(eceCity);

    razOutOfMapBorders(eceCity);

    afterX = eceCity->informationsSouris.celluleIso.x; //detecte le chmgt de cellule de la souris
    afterY = eceCity->informationsSouris.celluleIso.y;

    if (beforeX != afterX || beforeY != afterY) { //detecte le chmgt de cellule de la souris
        eceCity->informationsSouris.boolChangementDeCelluleIso = true;
    } else {
        eceCity->informationsSouris.boolChangementDeCelluleIso = false;
    }
}

void calculPositionSourisEnCelluleXY(SimWorld_t*eceCity) {
    eceCity->informationsSouris.celluleXY.x =
            GetMouseX() / eceCity->carte.mapTile[0][0].spriteLargeur;
    eceCity->informationsSouris.celluleXY.y =
            GetMouseY() / eceCity->carte.mapTile[0][0].spriteHauteur;

}

void razOutOfMapBorders(SimWorld_t*eceCity) {
    if (eceCity->informationsSouris.celluleIso.x<0 ||
                                                    eceCity->informationsSouris.celluleIso.x>(
            NBCELLULEX - 1)
        || eceCity->informationsSouris.celluleIso.y<0
                                                       ||
                                                       eceCity->informationsSouris.celluleIso.y>(
            NBCELLULEY - 1)) {
        eceCity->informationsSouris.celluleIso.x = 0;
        eceCity->informationsSouris.celluleIso.y = 0;
        eceCity->informationsSouris.outOfMapBorders = true;

    } else {
        eceCity->informationsSouris.outOfMapBorders = false;
    }
}

void calculPositionSourisEnCelluleIso(SimWorld_t*eceCity) {
    eceCity->informationsSouris.celluleIso.x =
            (eceCity->informationsSouris.celluleXY.y - eceCity->carte.Origine.celluleY)
            + (eceCity->informationsSouris.celluleXY.x -
               eceCity->carte.Origine.celluleX);//celluleX sélectionée iso
    eceCity->informationsSouris.celluleIso.y =
            (eceCity->informationsSouris.celluleXY.y - eceCity->carte.Origine.celluleY)
            - (eceCity->informationsSouris.celluleXY.x -
               eceCity->carte.Origine.celluleX);//celluleY sélectionée iso
}

void calculPositionSoursiEnOffsetDansUneCelluleXY(SimWorld_t*eceCity) {
    eceCity->informationsSouris.offsetCellule.x =
            GetMouseX() % eceCity->carte.mapTile[0][0].spriteLargeur;
    eceCity->informationsSouris.offsetCellule.y =
            GetMouseY() % eceCity->carte.mapTile[0][0].spriteHauteur;
}

void calculPositionSourisEnCelluleIsoReactualiseeGraceSpriteCheat(SimWorld_t*eceCity) {
    Color color = GetImageColor(eceCity->loader.spriteCheat, eceCity->informationsSouris.offsetCellule.x,
                                eceCity->informationsSouris.offsetCellule.y);

    if (color.r && !color.g && !color.b) {
        //... celule en -1 des X
        eceCity->informationsSouris.celluleIso.x -= 1;
    } else if (!color.r && color.g && !color.b) {
        //.. cellule en +y
        eceCity->informationsSouris.celluleIso.y += 1;
    } else if (color.r && color.g && !color.b) {
        //cellule en +x
        eceCity->informationsSouris.celluleIso.x += 1;
    } else if (!color.r && !color.g && color.b) {
        //cellule  en -y
        eceCity->informationsSouris.celluleIso.y -= 1;
    }
}

int isometricCoordsToScreenX(SimWorld_t*eceCity) {
    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if (eceCity->informationsSouris.celluleIso.x == x &&
                eceCity->informationsSouris.celluleIso.y == y) {
                return eceCity->carte.mapTile[y][x].position.x;
            }
        }
    }
}

int isometricCoordsToScreenY(SimWorld_t*eceCity) {
    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if (eceCity->informationsSouris.celluleIso.x == x &&
                eceCity->informationsSouris.celluleIso.y == y) {
                return eceCity->carte.mapTile[y][x].position.y;
            }
        }
    }
}

Vector2 celluleIsoToScreen(SimWorld_t* eceCity, Vector2 vector2D){
    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if(vector2D.x == x && vector2D.y == y){
                return (Vector2){eceCity->carte.mapTile[y][x].position.x, eceCity->carte.mapTile[y][x].position.y};
            }
        }
    }
}

Vector2 isometricCoordsToScreen(SimWorld_t*eceCity) {
    Vector2 position;

    position.x = isometricCoordsToScreenX(eceCity);
    position.y = isometricCoordsToScreenY(eceCity);

    return position;
}
