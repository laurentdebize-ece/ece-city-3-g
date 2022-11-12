#include <stdio.h>
#include "ui.h"
#include "jeu.h"

const char* timeToDate(SimWorld_t* s) {
    const char* months[] = { "JAN", "FEV", "MAR", "AVR", "MAI", "JUN", "JUL", "AOU", "SEP", "OCT", "NOV", "DEC" };

    int year = (s->n_ticks / N_TICKS_EVOLUTION) / 12;
    int month = (s->n_ticks / N_TICKS_EVOLUTION) % 12;
    return TextFormat("%s %d", months[month], 2000 + year);
}

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

    DrawText(TextFormat("%d", sim->habitations->taille), 271, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", 0), 493, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", 0), 717, 954, 20, (Color) { 0, 0, 0, 255 });


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
    if (textures->stateToolbar.hoverDestruction) {
        DrawCircle(1400, 970, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modeDestruction) {
        DrawCircle(1400, 970, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_DESTROY], 1376, 954, WHITE);

    Color timeColor = WHITE;
    if (textures->timeScale > 1.0f)
        timeColor = YELLOW;

    DrawTexture(textures->toolbarIcons[ICON_TIME], 1466, 954, timeColor);
    DrawText(TextFormat("x%d", (int)textures->timeScale), 1486, 994, 16, timeColor);

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

    // dessin du temps actuel
    DrawRectangleRounded((Rectangle) {
            .x = -5,
            .y = -5,
            .width = 200,
            .height = 50
    }, 0.2f, 8, (Color) { 0, 194, 255, 191 });
    DrawText(timeToDate(sim), 10, 10, 24, WHITE);

    // dessin de la monnaie
    DrawRectangleRounded((Rectangle) {
            .x = FENETRE_JEU_LARGEUR - 195,
            .y = -5,
            .width = 200,
            .height = 50
    }, 0.2f, 8, (Color) { 0, 194, 255, 191 });
    DrawText(TextFormat("%d $", sim->monnaie), FENETRE_JEU_LARGEUR - 190, 10, 24, WHITE);

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
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {109, 954, textures->toolbarIcons[ICON_SAVE].width,
                                                          textures->toolbarIcons[ICON_SAVE].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {211, 954, textures->toolbarIcons[ICON_PEOPLE].width,
                                                          textures->toolbarIcons[ICON_PEOPLE].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {446, 954, textures->toolbarIcons[ICON_ENERGY].width,
                                                          textures->toolbarIcons[ICON_ENERGY].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {668, 954, textures->toolbarIcons[ICON_WATER].width,
                                                          textures->toolbarIcons[ICON_WATER].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {892, 954, textures->toolbarIcons[ICON_BUILD].width,
                                                          textures->toolbarIcons[ICON_BUILD].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1376, 954, textures->toolbarIcons[ICON_DESTROY].width,
                                                          textures->toolbarIcons[ICON_DESTROY].height})) {
            textures->stateToolbar.modeDestruction = !textures->stateToolbar.modeDestruction;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1466, 954, textures->toolbarIcons[ICON_TIME].width,
                                                          textures->toolbarIcons[ICON_TIME].height})) {
            textures->timeScale *= 2.0f;
            if (textures->timeScale >= 256.0f)
                textures->timeScale = 1.0f;
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
            textures->stateToolbar.hoverMenu = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {109, 954, textures->toolbarIcons[ICON_SAVE].width,
                                                          textures->toolbarIcons[ICON_SAVE].height})) {
            textures->stateToolbar.hoverSave = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {211, 954, textures->toolbarIcons[ICON_PEOPLE].width,
                                                          textures->toolbarIcons[ICON_PEOPLE].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {446, 954, textures->toolbarIcons[ICON_ENERGY].width,
                                                          textures->toolbarIcons[ICON_ENERGY].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {668, 954, textures->toolbarIcons[ICON_WATER].width,
                                                          textures->toolbarIcons[ICON_WATER].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {892, 954, textures->toolbarIcons[ICON_BUILD].width,
                                                          textures->toolbarIcons[ICON_BUILD].height})) {
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1376, 954, textures->toolbarIcons[ICON_DESTROY].width,
                                                          textures->toolbarIcons[ICON_DESTROY].height})) {
            textures->stateToolbar.hoverDestruction = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1466, 954, textures->toolbarIcons[ICON_TIME].width,
                                                          textures->toolbarIcons[ICON_TIME].height})) {
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