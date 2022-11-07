#include "spritesheet.h"

void sprite_sheet_load(SpriteSheet_t* spriteSheet) {

    spriteSheet->spriteSheetTexture = LoadTexture("../assets/textures/carte/spriteSheet.png");
    spriteSheet->spriteCheatImage = LoadImage("../assets/textures/carte/tileCheat.png");

    spriteSheet->sprites[CHEAT].rectangle.height = SPRITEHAUTEUR;
    spriteSheet->sprites[CHEAT].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[CHEAT].rectangle.x = 0;
    spriteSheet->sprites[CHEAT].rectangle.y = 0;
    spriteSheet->sprites[CHEAT].decalageXDecor = 0;
    spriteSheet->sprites[CHEAT].decalageYDecor = 0;

    spriteSheet->sprites[HOOVER].rectangle.height = SPRITEHAUTEUR;
    spriteSheet->sprites[HOOVER].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[HOOVER].rectangle.x = SPRITELARGEUR * HOOVER;
    spriteSheet->sprites[HOOVER].rectangle.y = 0;
    spriteSheet->sprites[HOOVER].decalageXDecor = 0;
    spriteSheet->sprites[HOOVER].decalageYDecor = 0;

    spriteSheet->sprites[CONTOUR].rectangle.height = 20;
    spriteSheet->sprites[CONTOUR].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[CONTOUR].rectangle.x = SPRITELARGEUR * CONTOUR;
    spriteSheet->sprites[CONTOUR].rectangle.y = 0;
    spriteSheet->sprites[CONTOUR].decalageXDecor = 0;
    spriteSheet->sprites[CONTOUR].decalageYDecor = 0;

    spriteSheet->sprites[TERRAIN_0].rectangle.height = 26;
    spriteSheet->sprites[TERRAIN_0].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[TERRAIN_0].rectangle.x = SPRITELARGEUR * TERRAIN_0;
    spriteSheet->sprites[TERRAIN_0].rectangle.y = 0;
    spriteSheet->sprites[TERRAIN_0].decalageXDecor = 0;
    spriteSheet->sprites[TERRAIN_0].decalageYDecor = 0;

    spriteSheet->sprites[TERRAIN_1].rectangle.height = 26;
    spriteSheet->sprites[TERRAIN_1].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[TERRAIN_1].rectangle.x = SPRITELARGEUR * TERRAIN_1;
    spriteSheet->sprites[TERRAIN_1].rectangle.y = 0;
    spriteSheet->sprites[TERRAIN_1].decalageXDecor = 0;
    spriteSheet->sprites[TERRAIN_1].decalageYDecor = 0;

    spriteSheet->sprites[TERRAIN_2].rectangle.height = 26;
    spriteSheet->sprites[TERRAIN_2].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[TERRAIN_2].rectangle.x = SPRITELARGEUR * TERRAIN_2;
    spriteSheet->sprites[TERRAIN_2].rectangle.y = 0;
    spriteSheet->sprites[TERRAIN_2].decalageXDecor = 0;
    spriteSheet->sprites[TERRAIN_2].decalageYDecor = 0;

    spriteSheet->sprites[TERRAIN_3].rectangle.height = 36;
    spriteSheet->sprites[TERRAIN_3].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[TERRAIN_3].rectangle.x = SPRITELARGEUR * TERRAIN_3;
    spriteSheet->sprites[TERRAIN_3].rectangle.y = 0;
    spriteSheet->sprites[TERRAIN_3].decalageXDecor = 0;
    spriteSheet->sprites[TERRAIN_3].decalageYDecor = -10;

    spriteSheet->sprites[TERRAIN_4].rectangle.height = 26;
    spriteSheet->sprites[TERRAIN_4].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[TERRAIN_4].rectangle.x = SPRITELARGEUR * TERRAIN_4;
    spriteSheet->sprites[TERRAIN_4].rectangle.y = 0;
    spriteSheet->sprites[TERRAIN_4].decalageXDecor = 0;
    spriteSheet->sprites[TERRAIN_4].decalageYDecor = 0;

    spriteSheet->sprites[TERRAIN_5].rectangle.height = 26;
    spriteSheet->sprites[TERRAIN_5].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[TERRAIN_5].rectangle.x = SPRITELARGEUR * TERRAIN_5;
    spriteSheet->sprites[TERRAIN_5].rectangle.y = 0;
    spriteSheet->sprites[TERRAIN_5].decalageXDecor = 0;
    spriteSheet->sprites[TERRAIN_5].decalageYDecor = 0;

    spriteSheet->sprites[TERRAIN_6].rectangle.height = 26;
    spriteSheet->sprites[TERRAIN_6].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[TERRAIN_6].rectangle.x = SPRITELARGEUR * TERRAIN_6;
    spriteSheet->sprites[TERRAIN_6].rectangle.y = 0;
    spriteSheet->sprites[TERRAIN_6].decalageXDecor = 0;
    spriteSheet->sprites[TERRAIN_6].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_0].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_0].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_0].rectangle.x = SPRITELARGEUR * ROUTE_0;
    spriteSheet->sprites[ROUTE_0].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_0].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_0].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_1].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_1].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_1].rectangle.x = SPRITELARGEUR * ROUTE_1;
    spriteSheet->sprites[ROUTE_1].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_1].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_1].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_2].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_2].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_2].rectangle.x = SPRITELARGEUR * ROUTE_2;
    spriteSheet->sprites[ROUTE_2].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_2].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_2].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_3].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_3].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_3].rectangle.x = SPRITELARGEUR * ROUTE_3;
    spriteSheet->sprites[ROUTE_3].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_3].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_3].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_4].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_4].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_4].rectangle.x = SPRITELARGEUR * ROUTE_4;
    spriteSheet->sprites[ROUTE_4].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_4].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_4].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_5].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_5].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_5].rectangle.x = SPRITELARGEUR * ROUTE_5;
    spriteSheet->sprites[ROUTE_5].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_5].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_5].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_7].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_7].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_7].rectangle.x = SPRITELARGEUR * ROUTE_7;
    spriteSheet->sprites[ROUTE_7].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_7].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_7].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_8].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_8].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_8].rectangle.x = SPRITELARGEUR * ROUTE_8;
    spriteSheet->sprites[ROUTE_8].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_8].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_8].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_9].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_9].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_9].rectangle.x = SPRITELARGEUR * ROUTE_9;
    spriteSheet->sprites[ROUTE_9].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_9].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_9].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_10].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_10].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_10].rectangle.x = SPRITELARGEUR * ROUTE_10;
    spriteSheet->sprites[ROUTE_10].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_10].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_10].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_11].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_11].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_11].rectangle.x = SPRITELARGEUR * ROUTE_11;
    spriteSheet->sprites[ROUTE_11].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_11].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_11].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_12].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_12].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_12].rectangle.x = SPRITELARGEUR * ROUTE_12;
    spriteSheet->sprites[ROUTE_12].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_12].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_12].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_13].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_13].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_13].rectangle.x = SPRITELARGEUR * ROUTE_13;
    spriteSheet->sprites[ROUTE_13].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_13].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_13].decalageYDecor = 0;

    spriteSheet->sprites[ROUTE_14].rectangle.height = 26;
    spriteSheet->sprites[ROUTE_14].rectangle.width = SPRITELARGEUR;
    spriteSheet->sprites[ROUTE_14].rectangle.x = SPRITELARGEUR * ROUTE_14;
    spriteSheet->sprites[ROUTE_14].rectangle.y = 0;
    spriteSheet->sprites[ROUTE_14].decalageXDecor = 0;
    spriteSheet->sprites[ROUTE_14].decalageYDecor = 0;

    spriteSheet->sprites[TERRAIN_VAGUE_3X3].rectangle.height = 70;
    spriteSheet->sprites[TERRAIN_VAGUE_3X3].rectangle.width = 120;
    spriteSheet->sprites[TERRAIN_VAGUE_3X3].rectangle.x = 1000;
    spriteSheet->sprites[TERRAIN_VAGUE_3X3].rectangle.y = 0;
    spriteSheet->sprites[TERRAIN_VAGUE_3X3].decalageXDecor = -40;
    spriteSheet->sprites[TERRAIN_VAGUE_3X3].decalageYDecor = -1;

    spriteSheet->sprites[RUINE_3X3].rectangle.height = 70;
    spriteSheet->sprites[RUINE_3X3].rectangle.width = 120;
    spriteSheet->sprites[RUINE_3X3].rectangle.x = 1120;
    spriteSheet->sprites[RUINE_3X3].rectangle.y = 0;
    spriteSheet->sprites[RUINE_3X3].decalageXDecor = -40;
    spriteSheet->sprites[RUINE_3X3].decalageYDecor = 0;

    spriteSheet->sprites[CABANE_3X3].rectangle.height = 75;
    spriteSheet->sprites[CABANE_3X3].rectangle.width = 120;
    spriteSheet->sprites[CABANE_3X3].rectangle.x = 1240;
    spriteSheet->sprites[CABANE_3X3].rectangle.y = 0;
    spriteSheet->sprites[CABANE_3X3].decalageXDecor = -40;
    spriteSheet->sprites[CABANE_3X3].decalageYDecor = -(5);

    spriteSheet->sprites[MAISON_3X3].rectangle.height = 70;
    spriteSheet->sprites[MAISON_3X3].rectangle.width = 120;
    spriteSheet->sprites[MAISON_3X3].rectangle.x = 1360;
    spriteSheet->sprites[MAISON_3X3].rectangle.y = 0;
    spriteSheet->sprites[MAISON_3X3].decalageXDecor = -40;
    spriteSheet->sprites[MAISON_3X3].decalageYDecor = -1;

    spriteSheet->sprites[IMMEUBLE_3X3].rectangle.height = 90;
    spriteSheet->sprites[IMMEUBLE_3X3].rectangle.width = 120;
    spriteSheet->sprites[IMMEUBLE_3X3].rectangle.x = 1480;
    spriteSheet->sprites[IMMEUBLE_3X3].rectangle.y = 0;
    spriteSheet->sprites[IMMEUBLE_3X3].decalageXDecor = -41;
    spriteSheet->sprites[IMMEUBLE_3X3].decalageYDecor = -22;

    spriteSheet->sprites[GRATTE_CIEL_3X3].rectangle.height = 120;
    spriteSheet->sprites[GRATTE_CIEL_3X3].rectangle.width = 120;
    spriteSheet->sprites[GRATTE_CIEL_3X3].rectangle.x = 1600;
    spriteSheet->sprites[GRATTE_CIEL_3X3].rectangle.y = 0;
    spriteSheet->sprites[GRATTE_CIEL_3X3].decalageXDecor = -40;
    spriteSheet->sprites[GRATTE_CIEL_3X3].decalageYDecor = -54;

    spriteSheet->sprites[ENERGY_4X6].rectangle.height = 128;
    spriteSheet->sprites[ENERGY_4X6].rectangle.width = 200;
    spriteSheet->sprites[ENERGY_4X6].rectangle.x = 1720;
    spriteSheet->sprites[ENERGY_4X6].rectangle.y = 0;
    spriteSheet->sprites[ENERGY_4X6].decalageXDecor = -100;
    spriteSheet->sprites[ENERGY_4X6].decalageYDecor = -22;

    spriteSheet->sprites[ENERGY_6X4].rectangle.height = 128;
    spriteSheet->sprites[ENERGY_6X4].rectangle.width = 200;
    spriteSheet->sprites[ENERGY_6X4].rectangle.x = 1920;
    spriteSheet->sprites[ENERGY_6X4].rectangle.y = 0;
    spriteSheet->sprites[ENERGY_6X4].decalageXDecor = -60;
    spriteSheet->sprites[ENERGY_6X4].decalageYDecor = -22;

    spriteSheet->sprites[EAU_4X6].rectangle.height = 136;
    spriteSheet->sprites[EAU_4X6].rectangle.width = 200;
    spriteSheet->sprites[EAU_4X6].rectangle.x = 2120;
    spriteSheet->sprites[EAU_4X6].rectangle.y = 0;
    spriteSheet->sprites[EAU_4X6].decalageXDecor = -100;
    spriteSheet->sprites[EAU_4X6].decalageYDecor = -29;

    spriteSheet->sprites[EAU_6X4].rectangle.height = 130;
    spriteSheet->sprites[EAU_6X4].rectangle.width = 200;
    spriteSheet->sprites[EAU_6X4].rectangle.x = 2320;
    spriteSheet->sprites[EAU_6X4].rectangle.y = 0;
    spriteSheet->sprites[EAU_6X4].decalageXDecor = -60;
    spriteSheet->sprites[EAU_6X4].decalageYDecor = -22;
}

void sprite_sheet_draw_sprite(SpriteSheet_t* spriteSheet, enum SPRITE_MAP sprite, Color teinte, int x, int y) {
    int oX = (ORIGINEX * SPRITELARGEUR) + x * (SPRITELARGEUR/2) - y * (SPRITELARGEUR/2);
    int oY = (ORIGINEY * SPRITEHAUTEUR) + y * (SPRITEHAUTEUR/2) + x * (SPRITEHAUTEUR/2);
    DrawTextureRec(spriteSheet->spriteSheetTexture,
                   spriteSheet->sprites[sprite].rectangle,
                   (Vector2){oX + spriteSheet->sprites[sprite].decalageXDecor, oY + + spriteSheet->sprites[sprite].decalageYDecor}, teinte);
}
