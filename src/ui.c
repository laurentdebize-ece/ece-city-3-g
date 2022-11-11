#include <stdio.h>
#include "ui.h"
#include "jeu.h"

void ui_charger_textures(UIState* textures) {
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

void ui_draw_toolbar(UIState* textures, SimWorld_t* sim) {
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
    DrawTexture(textures->toolbarIcons[ICON_DESTROY], 1376, 954, textures->currentBuildMode == BUILD_MODE_DESTROY ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_TIME], 1466, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_ROAD], 1012, 954, textures->currentBuildMode == BUILD_MODE_ROUTE ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_HABITATION], 1082, 954, textures->currentBuildMode == BUILD_MODE_HABITATION ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_CENTRALE], 1159, 954, textures->currentBuildMode == BUILD_MODE_CENTRALE ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_CHATEAU], 1229, 954, textures->currentBuildMode == BUILD_MODE_CHATEAU ? YELLOW : WHITE);
}

void ui_update_toolbar(UIState* textures, SimWorld_t* sim) {
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        if (CheckCollisionPointRec(mousePos, (Rectangle) {26, 954, textures->toolbarIcons[ICON_HAMBURGER].width,
                                                          textures->toolbarIcons[ICON_HAMBURGER].height})) {
            printf("Hamburger\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {109, 954, textures->toolbarIcons[ICON_SAVE].width,
                                                          textures->toolbarIcons[ICON_SAVE].height})) {
            printf("Save\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {211, 954, textures->toolbarIcons[ICON_PEOPLE].width,
                                                          textures->toolbarIcons[ICON_PEOPLE].height})) {
            printf("People\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {446, 954, textures->toolbarIcons[ICON_ENERGY].width,
                                                          textures->toolbarIcons[ICON_ENERGY].height})) {
            printf("Energy\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {668, 954, textures->toolbarIcons[ICON_WATER].width,
                                                          textures->toolbarIcons[ICON_WATER].height})) {
            printf("Water\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {892, 954, textures->toolbarIcons[ICON_BUILD].width,
                                                          textures->toolbarIcons[ICON_BUILD].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1376, 954, textures->toolbarIcons[ICON_DESTROY].width,
                                                          textures->toolbarIcons[ICON_DESTROY].height})) {
            if (textures->currentBuildMode == BUILD_MODE_DESTROY)
                textures->currentBuildMode = BUILD_MODE_NONE;
            else
                textures->currentBuildMode = BUILD_MODE_DESTROY;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1466, 954, textures->toolbarIcons[ICON_TIME].width,
                                                          textures->toolbarIcons[ICON_TIME].height})) {
            printf("Time\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1012, 954, textures->toolbarIcons[ICON_ROAD].width,
                                                          textures->toolbarIcons[ICON_ROAD].height})) {
            if (textures->currentBuildMode == BUILD_MODE_ROUTE)
                textures->currentBuildMode = BUILD_MODE_NONE;
            else
                textures->currentBuildMode = BUILD_MODE_ROUTE;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1082, 954, textures->toolbarIcons[ICON_HABITATION].width,
                                                          textures->toolbarIcons[ICON_HABITATION].height})) {

            if (textures->currentBuildMode == BUILD_MODE_HABITATION)
                textures->currentBuildMode = BUILD_MODE_NONE;
            else
                textures->currentBuildMode = BUILD_MODE_HABITATION;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1159, 954, textures->toolbarIcons[ICON_CENTRALE].width,
                                                          textures->toolbarIcons[ICON_CENTRALE].height})) {
            if (textures->currentBuildMode == BUILD_MODE_CENTRALE)
                textures->currentBuildMode = BUILD_MODE_NONE;
            else
                textures->currentBuildMode = BUILD_MODE_CENTRALE;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1229, 954, textures->toolbarIcons[ICON_CHATEAU].width,
                                                          textures->toolbarIcons[ICON_CHATEAU].height})) {
            if (textures->currentBuildMode == BUILD_MODE_CHATEAU)
                textures->currentBuildMode = BUILD_MODE_NONE;
            else
                textures->currentBuildMode = BUILD_MODE_CHATEAU;
        }
    }
}

CaseKind_t ui_buildmode_to_casekind(BuildMode mode) {
    switch (mode) {
        case BUILD_MODE_ROUTE:
            return KIND_ROUTE;
        case BUILD_MODE_HABITATION:
            return KIND_HABITATION;
        case BUILD_MODE_CENTRALE:
            return KIND_CENTRALE;
        case BUILD_MODE_CHATEAU:
            return KIND_CHATEAU;
        default:
            return KIND_VIDE;
    }
}