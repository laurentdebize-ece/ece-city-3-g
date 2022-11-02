#include "tuile.h"

void actualiserPositionSourisJoueur(ECECity *eceCity) {
    int beforeX, beforeY, afterX, afterY;

    beforeX = (int) eceCity->interactionExterieure.celluleIso.x; //detecte le chmgt de cellule de la souris
    beforeY = (int) eceCity->interactionExterieure.celluleIso.y;

    calculPositionSourisEnCelluleXY(eceCity);

    calculPositionSourisEnCelluleIso(eceCity);

    calculPositionSoursiEnOffsetDansUneCelluleXY(eceCity);

    calculPositionSourisEnCelluleIsoReactualiseeGraceSpriteCheat(eceCity);

    razOutOfMapBorders(eceCity);

    afterX = eceCity->interactionExterieure.celluleIso.x; //detecte le chmgt de cellule de la souris
    afterY = eceCity->interactionExterieure.celluleIso.y;

    if (beforeX != afterX || beforeY != afterY) { //detecte le chmgt de cellule de la souris
        eceCity->interactionExterieure.boolChangementDeCelluleIso = true;
    } else {
        eceCity->interactionExterieure.boolChangementDeCelluleIso = false;
    }
}

void calculPositionSourisEnCelluleXY(ECECity *eceCity) {
    eceCity->interactionExterieure.celluleXY.x =
            GetMouseX() / eceCity->carte.mapTile[0][0].spriteLargeur;
    eceCity->interactionExterieure.celluleXY.y =
            GetMouseY() / eceCity->carte.mapTile[0][0].spriteHauteur;

}

void razOutOfMapBorders(ECECity *eceCity) {
    if (eceCity->interactionExterieure.celluleIso.x<0 ||
                                                    eceCity->interactionExterieure.celluleIso.x>(
            NBCELLULEX - 1)
        || eceCity->interactionExterieure.celluleIso.y<0
                                                       ||
                                                       eceCity->interactionExterieure.celluleIso.y>(
            NBCELLULEY - 1)) {
        eceCity->interactionExterieure.celluleIso.x = 0;
        eceCity->interactionExterieure.celluleIso.y = 0;
        eceCity->interactionExterieure.outOfMapBorders = true;

    } else {
        eceCity->interactionExterieure.outOfMapBorders = false;
    }
}

void calculPositionSourisEnCelluleIso(ECECity *eceCity) {
    eceCity->interactionExterieure.celluleIso.x =
            (eceCity->interactionExterieure.celluleXY.y - eceCity->carte.Origine.celluleY)
            + (eceCity->interactionExterieure.celluleXY.x -
               eceCity->carte.Origine.celluleX);//celluleX sélectionée iso
    eceCity->interactionExterieure.celluleIso.y =
            (eceCity->interactionExterieure.celluleXY.y - eceCity->carte.Origine.celluleY)
            - (eceCity->interactionExterieure.celluleXY.x -
               eceCity->carte.Origine.celluleX);//celluleY sélectionée iso
}

void calculPositionSoursiEnOffsetDansUneCelluleXY(ECECity *eceCity) {
    eceCity->interactionExterieure.offsetCellule.x =
            GetMouseX() % eceCity->carte.mapTile[0][0].spriteLargeur;
    eceCity->interactionExterieure.offsetCellule.y =
            GetMouseY() % eceCity->carte.mapTile[0][0].spriteHauteur;
}

void calculPositionSourisEnCelluleIsoReactualiseeGraceSpriteCheat(ECECity *eceCity) {
    Color color = GetImageColor(eceCity->carte.spriteCheat, eceCity->interactionExterieure.offsetCellule.x,
                                eceCity->interactionExterieure.offsetCellule.y);

    if (color.r && !color.g && !color.b) {
        //... celule en -1 des X
        eceCity->interactionExterieure.celluleIso.x -= 1;
    } else if (!color.r && color.g && !color.b) {
        //.. cellule en +y
        eceCity->interactionExterieure.celluleIso.y += 1;
    } else if (color.r && color.g && !color.b) {
        //cellule en +x
        eceCity->interactionExterieure.celluleIso.x += 1;
    } else if (!color.r && !color.g && color.b) {
        //cellule  en -y
        eceCity->interactionExterieure.celluleIso.y -= 1;
    }
}

int isometricCoordsToScreenX(ECECity *eceCity) {
    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if (eceCity->interactionExterieure.celluleIso.x == x &&
                eceCity->interactionExterieure.celluleIso.y == y) {
                return eceCity->carte.mapTile[y][x].position.x;
            }
        }
    }
}

int isometricCoordsToScreenY(ECECity *eceCity) {
    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            if (eceCity->interactionExterieure.celluleIso.x == x &&
                eceCity->interactionExterieure.celluleIso.y == y) {
                return eceCity->carte.mapTile[y][x].position.y;
            }
        }
    }
}

Vector2 isometricCoordsToScreen(ECECity *eceCity) {
    Vector2 position;

    position.x = isometricCoordsToScreenX(eceCity);
    position.y = isometricCoordsToScreenY(eceCity);

    return position;
}
