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
    textures->toolbarIcons[ICON_CASERNE] = LoadTexture("../assets/textures/icones/caserne-de-pompiers.png");
}

void ui_draw_toolbar(UIState* textures, SimWorld_t* sim) {
    DrawRectangle(0, 924, FENETRE_JEU_LARGEUR, 100, (Color) { 0, 194, 255, 191 });

    DrawRectangle(271, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(493, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(717, 954, 125, 40, (Color) { 238,238,238,200});

    DrawText(TextFormat("%d", sim->nb_total_habitants), 271, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", sim->qte_totale_electricite), 493, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", sim->qte_totale_eau), 717, 954, 20, (Color) { 0, 0, 0, 255 });

    DrawTexture(textures->toolbarIcons[ICON_HAMBURGER], 26, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_SAVE], 109, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_PEOPLE], 211, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_ENERGY], 446, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_WATER], 668, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_BUILD], 892, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_DESTROY], 1376, 954, textures->currentBuildMode == BUILD_MODE_DESTROY ? YELLOW : WHITE);

    Color timeColor = WHITE;
    if (textures->timeScale > 1.0f)
        timeColor = YELLOW;

    DrawTexture(textures->toolbarIcons[ICON_TIME], 1466, 954, timeColor);
    DrawText(TextFormat("x%d", (int)textures->timeScale), 1486, 994, 16, timeColor);
    DrawTexture(textures->toolbarIcons[ICON_ROAD], 1012, 954, textures->currentBuildMode == BUILD_MODE_ROUTE ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_HABITATION], 1082, 954, textures->currentBuildMode == BUILD_MODE_HABITATION ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_CENTRALE], 1159, 954, textures->currentBuildMode == BUILD_MODE_CENTRALE ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_CHATEAU], 1229, 954, textures->currentBuildMode == BUILD_MODE_CHATEAU ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_CASERNE], 1299, 954, textures->currentBuildMode == BUILD_MODE_CASERNE ? YELLOW : WHITE);

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
    DrawText(TextFormat("%d £", sim->monnaie), FENETRE_JEU_LARGEUR - 190, 10, 24, WHITE);
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
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_DESTROY ? BUILD_MODE_NONE : BUILD_MODE_DESTROY);
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1466, 954, textures->toolbarIcons[ICON_TIME].width,
                                                          textures->toolbarIcons[ICON_TIME].height})) {

            textures->timeScale *= 2.0f;
            if (textures->timeScale >= 256.0f)
                textures->timeScale = 1.0f;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1012, 954, textures->toolbarIcons[ICON_ROAD].width,
                                                          textures->toolbarIcons[ICON_ROAD].height}))
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_ROUTE ? BUILD_MODE_NONE : BUILD_MODE_ROUTE);

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1082, 954, textures->toolbarIcons[ICON_HABITATION].width,
                                                          textures->toolbarIcons[ICON_HABITATION].height}))
           textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_HABITATION ? BUILD_MODE_NONE : BUILD_MODE_HABITATION);

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1159, 954, textures->toolbarIcons[ICON_CENTRALE].width,
                                                          textures->toolbarIcons[ICON_CENTRALE].height}))
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_CENTRALE ? BUILD_MODE_NONE : BUILD_MODE_CENTRALE);


        if (CheckCollisionPointRec(mousePos, (Rectangle) {1229, 954, textures->toolbarIcons[ICON_CHATEAU].width,
                                                          textures->toolbarIcons[ICON_CHATEAU].height}))
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_CHATEAU ? BUILD_MODE_NONE : BUILD_MODE_CHATEAU);

        if (CheckCollisionPointRec(mousePos, (Rectangle){1299, 954, textures->toolbarIcons[ICON_CASERNE].width,
                                                         textures->toolbarIcons[ICON_CASERNE].height}))
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_CASERNE ? BUILD_MODE_NONE : BUILD_MODE_CASERNE);
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
        case BUILD_MODE_CASERNE:
            return KIND_CASERNE;
        default:
            return KIND_VIDE;
    }
}