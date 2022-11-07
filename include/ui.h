
#ifndef ECECITY_UI_H
#define ECECITY_UI_H

#include <raylib.h>

enum TOOLBAR_ICON {
    ICON_HAMBURGER,
    ICON_SAVE,
    ICON_PEOPLE,
    ICON_ENERGY,
    ICON_WATER,
    ICON_BUILD,
    ICON_DESTROY,
    ICON_TIME,
    ICON_ROAD,
    ICON_HABITATION,
    ICON_CENTRALE,
    ICON_CHATEAU,
    ICON_DOLLAR,
    ICON_NB_LOGOS_TOOLBAR
};

typedef struct UITextures_t {
    Texture2D toolbarIcons[ICON_NB_LOGOS_TOOLBAR];
} UITextures_t;

void ui_charger_textures(UITextures_t* textures);

void ui_draw_toolbar(UITextures_t* textures);

#endif //ECECITY_UI_H
