#include "ui.h"
#include "jeu.h"

void ui_charger_textures(UITextures_t* textures) {
    textures->toolbarIcons[ICON_HAMBURGER] = LoadTexture("../assets/textures/icones/hamburger.png");
    textures->toolbarIcons[ICON_SAVE] = LoadTexture("../assets/textures/icones/save.png");
    textures->toolbarIcons[ICON_PEOPLE] = LoadTexture("../assets/textures/icones/people.png");
    textures->toolbarIcons[ICON_ENERGY] = LoadTexture("../assets/textures/icones/energy.png");
    textures->toolbarIcons[ICON_WATER] = LoadTexture("../assets/textures/icones/water.png");
    textures->toolbarIcons[ICON_BUILD] = LoadTexture("../assets/textures/icones/build.png");
    textures->toolbarIcons[ICON_DESTROY] = LoadTexture("../assets/textures/icones/destroy.png");
    textures->toolbarIcons[ICON_TIME] = LoadTexture("../assets/textures/icones/time.png");
    textures->toolbarIcons[ICON_ROAD] = LoadTexture("../assets/textures/icones/road.png");
    textures->toolbarIcons[ICON_HABITATION] = LoadTexture("../assets/textures/icones/house.png");
    textures->toolbarIcons[ICON_CENTRALE] = LoadTexture("../assets/textures/icones/industry.png");
    textures->toolbarIcons[ICON_CHATEAU] = LoadTexture("../assets/textures/icones/valve.png");
}

void ui_draw_toolbar(UITextures_t* textures, SimWorld_t* sim) {
    DrawRectangle(0, 924, FENETRE_JEU_LARGEUR, 100, (Color) { 0, 194, 255, 191 });

    DrawRectangle(271, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(493, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(717, 954, 125, 40, (Color) { 238,238,238,200});

    DrawText(TextFormat("%d", sim->rules), 271, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", sim->monnaie), 493, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", sim->n_ticks), 717, 954, 20, (Color) { 0, 0, 0, 255 });

    DrawTexture(textures->toolbarIcons[ICON_HAMBURGER], 26, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_SAVE], 109, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_PEOPLE], 211, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_ENERGY], 446, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_WATER], 668, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_BUILD], 892, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_DESTROY], 1376, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_TIME], 1466, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_ROAD], 1012, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_HABITATION], 1082, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_CENTRALE], 1159, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_CHATEAU], 1229, 954, WHITE);
}