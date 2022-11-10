#include "utils/grille.h"
#include "screens/gameplay.h"

Vector2 iso_to_screen(GameplayScreen_t *gameplay, Vector2I position) {
    for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
        for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
            if (x == position.x &&
                y == position.y) {
                return (Vector2) gameplay->world->map[y][x].position;
            }
        }
    }
}

void razOutOfMapBorders(GameplayScreen_t *gameplay) {
    if (gameplay->state.stateMouse.celluleIso.x<0 || gameplay->state.stateMouse.celluleIso.x>(SIM_MAP_LARGEUR - 1) || gameplay->state.stateMouse.celluleIso.y<0 || gameplay->state.stateMouse.celluleIso.y > (SIM_MAP_HAUTEUR - 1)) {
        gameplay->state.stateMouse.outOfMapBorders = true;
    } else {
        gameplay->state.stateMouse.outOfMapBorders = false;
    }
}

void calculPositionSourisEnCelluleIso(GameplayScreen_t *gameplay) {
    gameplay->state.stateMouse.celluleIso.x =
            (gameplay->state.stateMouse.celluleXY.y - ORIGINEY)
            + (gameplay->state.stateMouse.celluleXY.x -
               ORIGINEX);//celluleX sélectionée iso
    gameplay->state.stateMouse.celluleIso.y =
            (gameplay->state.stateMouse.celluleXY.y - ORIGINEY)
            - (gameplay->state.stateMouse.celluleXY.x -
               ORIGINEX);//celluleY sélectionée iso
}

void calculPositionSoursiEnOffsetDansUneCelluleXY(GameplayScreen_t *gameplay) {
    gameplay->state.stateMouse.offsetCellule.x = (GetMouseX() % SPRITELARGEUR);
    gameplay->state.stateMouse.offsetCellule.y = (GetMouseY() %  SPRITEHAUTEUR);
}

void calculPositionSourisEnCelluleIsoReactualiseeGraceSpriteCheat(GameplayScreen_t *gameplay) {
    Color color = GetImageColor(gameplay->spriteSheet.spriteDetectionTuile, gameplay->state.stateMouse.offsetCellule.x,
                                gameplay->state.stateMouse.offsetCellule.y);

    if (color.r && !color.g && !color.b) {
        //... celule en -1 des X
        gameplay->state.stateMouse.celluleIso.x -= 1;
    } else if (!color.r && color.g && !color.b) {
        //.. cellule en +y
        gameplay->state.stateMouse.celluleIso.y += 1;
    } else if (color.r && color.g && !color.b) {
        //cellule en +x
        gameplay->state.stateMouse.celluleIso.x += 1;
    } else if (!color.r && !color.g && color.b) {
        //cellule  en -y
        gameplay->state.stateMouse.celluleIso.y -= 1;
    }
}

void calculPositionSourisEnCelluleXY(GameplayScreen_t *gameplay) {
    gameplay->state.stateMouse.celluleXY.x = (GetMouseX() / SPRITELARGEUR);
    gameplay->state.stateMouse.celluleXY.y = (GetMouseY() / SPRITEHAUTEUR);
}

void update_state_mouse(GameplayScreen_t *gameplay) {
    int beforeX, beforeY, afterX, afterY;

    beforeX = (int) gameplay->state.stateMouse.celluleIso.x; //detecte le chmgt de cellule de la souris
    beforeY = (int) gameplay->state.stateMouse.celluleIso.y;

    calculPositionSoursiEnOffsetDansUneCelluleXY(gameplay);

    calculPositionSourisEnCelluleXY(gameplay);

    calculPositionSourisEnCelluleIso(gameplay);

    calculPositionSourisEnCelluleIsoReactualiseeGraceSpriteCheat(gameplay);

    razOutOfMapBorders(gameplay);

    if(gameplay->state.stateMouse.outOfMapBorders) {
        gameplay->state.stateMouse.celluleIso.x = -1;
        gameplay->state.stateMouse.celluleIso.y = -1;
    }
    afterX = gameplay->state.stateMouse.celluleIso.x; //detecte le chmgt de cellule de la souris
    afterY = gameplay->state.stateMouse.celluleIso.y;

    if (beforeX != afterX || beforeY != afterY) { //detecte le chmgt de cellule de la souris
        gameplay->state.stateMouse.boolChangementDeCelluleIso = true;
    } else {
        gameplay->state.stateMouse.boolChangementDeCelluleIso = false;
    }
}


Vector2I mouse_to_iso(Vector2I mouse, Image img) {
    Vector2I isoPos = cartesien_to_iso((Vector2I) {
            mouse.x / LARGUEUR_TUILE_ISO,
            mouse.y / HAUTEUR_TUILE_ISO
    });

    int offsetX = mouse.x % LARGUEUR_TUILE_ISO;
    int offsetY = mouse.y % HAUTEUR_TUILE_ISO;

    Color color = GetImageColor(img, offsetX, offsetY);

    if (color.r && !color.g && !color.b) {
        //... cellule en -1 des X
        isoPos.x -= 1;
    } else if (!color.r && color.g && !color.b) {
        //.. cellule en +y
        isoPos.y += 1;
    } else if (color.r && color.g && !color.b) {
        //cellule en +x
        isoPos.x += 1;
    } else if (!color.r && !color.g && color.b) {
        //cellule  en -y
        isoPos.y -= 1;
    }

    return isoPos;
}

Vector2I cartesien_to_iso(Vector2I cartesien) {
    return (Vector2I) {
        .x = (cartesien.y - ISO_ORIGINE_Y) + (cartesien.x - ISO_ORIGINE_X),
        .y = (cartesien.y - ISO_ORIGINE_Y) - (cartesien.x - ISO_ORIGINE_X)
    };
}