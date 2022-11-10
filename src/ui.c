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
    if (textures->stateToolbar.hoverMenu) {
        DrawCircle(53, 970, 35 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modeMenu) {
        DrawCircle(53, 970, 35 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_HAMBURGER], 26, 954, WHITE);
    if (textures->stateToolbar.hoverMenu) {
        DrawCircle(120, 980, 35 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modeMenu) {
        DrawCircle(120, 970, 35 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_SAVE], 109, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_PEOPLE], 211, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_ENERGY], 446, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_WATER], 668, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_BUILD], 892, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_DESTROY], 1376, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_TIME], 1466, 954, WHITE);

    if (textures->stateToolbar.hoverRoute) {
        DrawCircle(1030, 970, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modePlacementRoute) {
        DrawCircle(1030, 970, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_ROAD], 1012, 954, WHITE);

    if (textures->stateToolbar.hoverHabitation) {
        DrawCircle(1100, 970, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modePlacementHabitation) {
        DrawCircle(1100, 970, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_HABITATION], 1082, 954, WHITE);

    if (textures->stateToolbar.hoverCentrale) {
        DrawCircle(1177, 970, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modePlacementCentrale) {
        DrawCircle(1177, 970, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_CENTRALE], 1159, 954, WHITE);

    if (textures->stateToolbar.hoverChateau) {
        DrawCircle(1250, 970, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modePlacementChateau) {
        DrawCircle(1250, 970, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_CHATEAU], 1229, 954, WHITE);
}

void ui_update_toolbar(UIState* textures, SimWorld_t* sim) {
    Vector2 mousePos = GetMousePosition();

    textures->stateToolbar.hoverMenu = false;
    textures->stateToolbar.hoverSave = false;
    textures->stateToolbar.hoverDestruction = false;
    textures->stateToolbar.hoverRoute = false;
    textures->stateToolbar.hoverHabitation = false;
    textures->stateToolbar.hoverCentrale = false;
    textures->stateToolbar.hoverChateau = false;


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
            printf("Build\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1376, 954, textures->toolbarIcons[ICON_DESTROY].width,
                                                          textures->toolbarIcons[ICON_DESTROY].height})) {
            printf("Destroy\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1466, 954, textures->toolbarIcons[ICON_TIME].width,
                                                          textures->toolbarIcons[ICON_TIME].height})) {
            printf("Time\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1012, 954, textures->toolbarIcons[ICON_ROAD].width,
                                                          textures->toolbarIcons[ICON_ROAD].height})) {
            //textures->currentBuildMode = BUILD_MODE_ROUTE;
            textures->stateToolbar.modePlacementRoute = !textures->stateToolbar.modePlacementRoute;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1082, 954, textures->toolbarIcons[ICON_HABITATION].width,
                                                          textures->toolbarIcons[ICON_HABITATION].height})) {
            //textures->currentBuildMode = BUILD_MODE_HABITATION;
            textures->stateToolbar.modePlacementHabitation = !textures->stateToolbar.modePlacementHabitation;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1159, 954, textures->toolbarIcons[ICON_CENTRALE].width,
                                                          textures->toolbarIcons[ICON_CENTRALE].height})) {
            //textures->currentBuildMode = BUILD_MODE_CENTRALE;
            textures->stateToolbar.modePlacementCentrale = !textures->stateToolbar.modePlacementCentrale;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1229, 954, textures->toolbarIcons[ICON_CHATEAU].width,
                                                          textures->toolbarIcons[ICON_CHATEAU].height})) {
            //textures->currentBuildMode =  BUILD_MODE_CHATEAU;
            textures->stateToolbar.modePlacementChateau = !textures->stateToolbar.modePlacementChateau;
        }
    } else {
        if (CheckCollisionPointRec(mousePos, (Rectangle) {26, 954, textures->toolbarIcons[ICON_HAMBURGER].width,
                                                          textures->toolbarIcons[ICON_HAMBURGER].height})) {
            printf("Hamburger\n");
            textures->stateToolbar.hoverMenu = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {109, 954, textures->toolbarIcons[ICON_SAVE].width,
                                                          textures->toolbarIcons[ICON_SAVE].height})) {
            printf("Save\n");
            textures->stateToolbar.hoverSave = true;
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
            printf("Build\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1376, 954, textures->toolbarIcons[ICON_DESTROY].width,
                                                          textures->toolbarIcons[ICON_DESTROY].height})) {
            printf("Destroy\n");
            textures->stateToolbar.hoverDestruction = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1466, 954, textures->toolbarIcons[ICON_TIME].width,
                                                          textures->toolbarIcons[ICON_TIME].height})) {
            printf("Time\n");
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1012, 954, textures->toolbarIcons[ICON_ROAD].width,
                                                          textures->toolbarIcons[ICON_ROAD].height})) {
            //textures->currentBuildMode = BUILD_MODE_ROUTE;
            textures->stateToolbar.hoverRoute = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1082, 954, textures->toolbarIcons[ICON_HABITATION].width,
                                                          textures->toolbarIcons[ICON_HABITATION].height})) {
            //textures->currentBuildMode = BUILD_MODE_HABITATION;
            textures->stateToolbar.hoverHabitation = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1159, 954, textures->toolbarIcons[ICON_CENTRALE].width,
                                                          textures->toolbarIcons[ICON_CENTRALE].height})) {
            //textures->currentBuildMode = BUILD_MODE_CENTRALE;
            textures->stateToolbar.hoverCentrale = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1229, 954, textures->toolbarIcons[ICON_CHATEAU].width,
                                                          textures->toolbarIcons[ICON_CHATEAU].height})) {
            //textures->currentBuildMode =  BUILD_MODE_CHATEAU;
            textures->stateToolbar.hoverChateau = true;
        }
    }
}