
#ifndef ECECITY_SPRITESHEET_H
#define ECECITY_SPRITESHEET_H

#include <raylib.h>

#define SPRITELARGEUR 40
#define SPRITEHAUTEUR 20

#define ORIGINEX 17
#define ORIGINEY 3

enum SPRITE_MAP {
    CHEAT,
    HOOVER,
    CONTOUR,
    TERRAIN_0,
    TERRAIN_1,
    TERRAIN_2,
    TERRAIN_3,
    TERRAIN_4,
    TERRAIN_5,
    TERRAIN_6,
    ROUTE_0,
    ROUTE_1,
    ROUTE_2,
    ROUTE_3,
    ROUTE_4,
    ROUTE_5,
    ROUTE_6,
    ROUTE_7,
    ROUTE_8,
    ROUTE_9,
    ROUTE_10,
    ROUTE_11,
    ROUTE_12,
    ROUTE_13,
    ROUTE_14,
    TERRAIN_VAGUE_3X3,
    RUINE_3X3,
    CABANE_3X3,
    MAISON_3X3,
    IMMEUBLE_3X3,
    GRATTE_CIEL_3X3,
    ENERGY_4X6,
    ENERGY_6X4,
    EAU_4X6,
    EAU_6X4,
    VIDE,
    NB_SPRITES
};

typedef struct Sprite_t {
    Rectangle rectangle;
    int decalageXDecor;
    int decalageYDecor;
} Sprite_t;

typedef struct SpriteSheet_t {
    Texture2D spriteSheetTexture;
    Image spriteCheatImage;
    Sprite_t sprites[NB_SPRITES];
} SpriteSheet_t;

void sprite_sheet_load(SpriteSheet_t* spriteSheet);

void sprite_sheet_draw_sprite(SpriteSheet_t* spriteSheet, enum SPRITE_MAP map, Color teinte, int x, int y);

#endif //ECECITY_SPRITESHEET_H
