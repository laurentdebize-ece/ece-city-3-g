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
    textures->toolbarIcons[ICON_GRID] = LoadTexture("../assets/textures/icones/grid.png");
    textures->toolbarIcons[ICON_WATER_GRID] = LoadTexture("../assets/textures/icones/water_grid.png");
    textures->toolbarIcons[ICON_ELECTRICITY_GRID] = LoadTexture("../assets/textures/icones/electricity_grid.png");
    textures->toolbarIcons[ICON_CHECK] = LoadTexture("../assets/textures/icones/check.png");
    textures->toolbarIcons[ICON_CANCEL] = LoadTexture("../assets/textures/icones/cancel.png");
    textures->toolbarIcons[ICON_ADD] = LoadTexture("../assets/textures/icones/add.png");
}

void draw_affichage_niveaux(UIState* textures){
    DrawRectangleRounded((Rectangle) {15, 830, 300, 75}, 0.2f, 8, (Color) { 0, 194, 255, 191 });
    if (textures->stateToolbar.hoverNiveauNormal) {
        DrawCircle(58, 868, 30, (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.niveauNormal) {
        DrawCircle(58, 868, 30, (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_GRID], 40, 851, textures->stateToolbar.niveauNormal ? YELLOW : WHITE);
    if (textures->stateToolbar.hoverNiveauElectricite) {
        DrawCircle(168, 868, 30, (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.niveauElectricite) {
        DrawCircle(168, 868, 30, (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_ELECTRICITY_GRID], 150, 851, textures->stateToolbar.niveauElectricite ? YELLOW : WHITE);
    if (textures->stateToolbar.hoverNiveauEau) {
        DrawCircle(283, 868, 30, (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.niveauEau) {
        DrawCircle(283, 868, 30, (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_WATER_GRID], 265, 851, textures->stateToolbar.niveauEau ? YELLOW : WHITE);

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
    if (textures->stateToolbar.hoverMenu) {
        DrawCircle(50, 975, 35 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modeMenu) {
        DrawCircle(50, 975, 35 , (Color) { 0, 0, 0, 45 });
        draw_affichage_niveaux(textures);
    }
    DrawTexture(textures->toolbarIcons[ICON_HAMBURGER], 26, 954, textures->stateToolbar.modeMenu ? YELLOW : WHITE);
    if (textures->stateToolbar.hoverSave) {
        DrawCircle(128, 975, 35 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modeSave) {
        DrawCircle(128, 975, 35 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_SAVE], 109, 954, textures->stateToolbar.modeSave ? YELLOW : WHITE);
    DrawTexture(textures->toolbarIcons[ICON_PEOPLE], 211, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_ENERGY], 446, 954, WHITE);
    DrawTexture(textures->toolbarIcons[ICON_WATER], 668, 954, WHITE);
    if (textures->stateToolbar.hoverChangementNiveau) {
        DrawCircle(910, 975, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modeChangementNiveau) {
        DrawCircle(910, 975, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_BUILD], 892, 954, textures->stateToolbar.modeChangementNiveau ? YELLOW : WHITE);
    if (textures->stateToolbar.hoverDestruction) {
        DrawCircle(1395, 975, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modeDestruction) {
        DrawCircle(1395, 975, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_DESTROY], 1376, 954, textures->stateToolbar.modeDestruction ? YELLOW : WHITE);
    if (textures->stateToolbar.hoverRoute) {
        DrawCircle(1030, 970, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modePlacementRoute) {
        DrawCircle(1030, 970, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_ROAD], 1012, 954, textures->stateToolbar.modePlacementRoute ? YELLOW : WHITE);

    if (textures->stateToolbar.hoverHabitation) {
        DrawCircle(1105, 975, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modePlacementHabitation) {
        DrawCircle(1105, 975, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_HABITATION], 1082, 954, textures->stateToolbar.modePlacementHabitation ? YELLOW : WHITE);

    if (textures->stateToolbar.hoverCentrale) {
        DrawCircle(1180, 975, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modePlacementCentrale) {
        DrawCircle(1180, 975, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_CENTRALE], 1159, 954, textures->stateToolbar.modePlacementCentrale ? YELLOW : WHITE);

    if (textures->stateToolbar.hoverChateau) {
        DrawCircle(1247, 975, 30 , (Color) { 0, 0, 0, 20 });
    } else if (textures->stateToolbar.modePlacementChateau) {
        DrawCircle(1247, 975, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(textures->toolbarIcons[ICON_CHATEAU], 1229, 954, textures->stateToolbar.modePlacementChateau ? YELLOW : WHITE);

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

    textures->stateToolbar.hoverMenu = false;
    textures->stateToolbar.hoverSave = false;
    textures->stateToolbar.hoverDestruction = false;
    textures->stateToolbar.hoverRoute = false;
    textures->stateToolbar.hoverHabitation = false;
    textures->stateToolbar.hoverCentrale = false;
    textures->stateToolbar.hoverChateau = false;
    textures->stateToolbar.hoverChangementNiveau = false;
    textures->stateToolbar.hoverNiveauElectricite = false;
    textures->stateToolbar.hoverNiveauEau = false;
    textures->stateToolbar.hoverNiveauNormal = false;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        if (textures->stateToolbar.modeMenu) {
            if (CheckCollisionPointRec(mousePos, (Rectangle) {40, 851, 40, 40})) {
                textures->stateToolbar.niveauNormal = true;
                textures->stateToolbar.niveauEau = false;
                textures->stateToolbar.niveauElectricite = false;
            }

            if (CheckCollisionPointRec(mousePos,
                                       (Rectangle) {150, 851, 40, 40})) {
                textures->stateToolbar.niveauElectricite = !textures->stateToolbar.niveauElectricite;
                if (textures->stateToolbar.niveauElectricite == false) {
                    textures->stateToolbar.niveauEau = false;
                    textures->stateToolbar.niveauNormal = true;
                } else {
                    textures->stateToolbar.niveauEau = false;
                    textures->stateToolbar.niveauNormal = false;
                }
            }

            if (CheckCollisionPointRec(mousePos, (Rectangle) {265, 851, 40, 40})) {
                textures->stateToolbar.niveauEau = !textures->stateToolbar.niveauEau;
                if (textures->stateToolbar.niveauEau == false) {
                    textures->stateToolbar.niveauElectricite = false;
                    textures->stateToolbar.niveauNormal = true;
                } else {
                    textures->stateToolbar.niveauElectricite = false;
                    textures->stateToolbar.niveauNormal = false;
                }
            }
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {26, 954, textures->toolbarIcons[ICON_HAMBURGER].width,
                                                          textures->toolbarIcons[ICON_HAMBURGER].height})) {
            textures->stateToolbar.modeMenu = !textures->stateToolbar.modeMenu;
            textures->stateToolbar.modeChangementNiveau = false;
            textures->stateToolbar.modeSave = false;
            textures->stateToolbar.modePlacementRoute = false;
            textures->stateToolbar.modePlacementHabitation = false;
            textures->stateToolbar.modePlacementCentrale = false;
            textures->stateToolbar.modePlacementChateau = false;
            textures->stateToolbar.modeDestruction = false;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {109, 954, textures->toolbarIcons[ICON_SAVE].width,
                                                          textures->toolbarIcons[ICON_SAVE].height})) {
            textures->stateToolbar.modeSave = !textures->stateToolbar.modeSave;
            if(textures->stateToolbar.modeSave){
                textures->stateToolbar.stateMenuSave.resetNbSauvegardes = true;
            }
            textures->stateToolbar.modeMenu = false;
            textures->stateToolbar.modeChangementNiveau = false;
            textures->stateToolbar.modePlacementRoute = false;
            textures->stateToolbar.modePlacementHabitation = false;
            textures->stateToolbar.modePlacementCentrale = false;
            textures->stateToolbar.modePlacementChateau = false;
            textures->stateToolbar.modeDestruction = false;
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
            textures->stateToolbar.modeChangementNiveau = !textures->stateToolbar.modeChangementNiveau;
            textures->stateToolbar.modeMenu = false;
            textures->stateToolbar.modeSave = false;
            textures->stateToolbar.modePlacementRoute = false;
            textures->stateToolbar.modePlacementHabitation = false;
            textures->stateToolbar.modePlacementCentrale = false;
            textures->stateToolbar.modePlacementChateau = false;
            textures->stateToolbar.modeDestruction = false;
            textures->stateToolbar.niveauNormal = true;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1376, 954, textures->toolbarIcons[ICON_DESTROY].width,
                                                          textures->toolbarIcons[ICON_DESTROY].height})) {
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_DESTROY ? BUILD_MODE_NONE : BUILD_MODE_DESTROY);
            textures->stateToolbar.modeDestruction = !textures->stateToolbar.modeDestruction;
            textures->stateToolbar.modeMenu = false;
            textures->stateToolbar.modeSave = false;
            textures->stateToolbar.modePlacementRoute = false;
            textures->stateToolbar.modePlacementHabitation = false;
            textures->stateToolbar.modePlacementCentrale = false;
            textures->stateToolbar.modePlacementChateau = false;
            textures->stateToolbar.modeChangementNiveau = false;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1466, 954, textures->toolbarIcons[ICON_TIME].width,
                                                          textures->toolbarIcons[ICON_TIME].height})) {

            textures->timeScale *= 2.0f;
            if (textures->timeScale >= 256.0f)
                textures->timeScale = 1.0f;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1012, 954, textures->toolbarIcons[ICON_ROAD].width,
                                                          textures->toolbarIcons[ICON_ROAD].height})){
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_ROUTE ? BUILD_MODE_NONE : BUILD_MODE_ROUTE);
            textures->stateToolbar.modePlacementRoute = !textures->stateToolbar.modePlacementRoute;
            textures->stateToolbar.modeMenu = false;
            textures->stateToolbar.modeSave = false;
            textures->stateToolbar.modeDestruction = false;
            textures->stateToolbar.modePlacementHabitation = false;
            textures->stateToolbar.modePlacementCentrale = false;
            textures->stateToolbar.modePlacementChateau = false;
            textures->stateToolbar.modeChangementNiveau = false;
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1082, 954, textures->toolbarIcons[ICON_HABITATION].width,
                                                          textures->toolbarIcons[ICON_HABITATION].height})){
            textures->stateToolbar.modePlacementHabitation = !textures->stateToolbar.modePlacementHabitation;
            textures->stateToolbar.modeMenu = false;
            textures->stateToolbar.modeSave = false;
            textures->stateToolbar.modeDestruction = false;
            textures->stateToolbar.modePlacementRoute = false;
            textures->stateToolbar.modePlacementCentrale = false;
            textures->stateToolbar.modePlacementChateau = false;
            textures->stateToolbar.modeChangementNiveau = false;
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_HABITATION ? BUILD_MODE_NONE : BUILD_MODE_HABITATION);
        }

        if (CheckCollisionPointRec(mousePos, (Rectangle) {1159, 954, textures->toolbarIcons[ICON_CENTRALE].width,
                                                          textures->toolbarIcons[ICON_CENTRALE].height})){
            textures->stateToolbar.modePlacementCentrale = !textures->stateToolbar.modePlacementCentrale;
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_CENTRALE ? BUILD_MODE_NONE : BUILD_MODE_CENTRALE);
            textures->stateToolbar.modeMenu = false;
            textures->stateToolbar.modeSave = false;
            textures->stateToolbar.modeDestruction = false;
            textures->stateToolbar.modePlacementRoute = false;
            textures->stateToolbar.modePlacementHabitation = false;
            textures->stateToolbar.modePlacementChateau = false;
            textures->stateToolbar.modeChangementNiveau = false;
        }
        if (CheckCollisionPointRec(mousePos, (Rectangle) {1229, 954, textures->toolbarIcons[ICON_CHATEAU].width,
                                                          textures->toolbarIcons[ICON_CHATEAU].height})) {
            textures->stateToolbar.modePlacementChateau = !textures->stateToolbar.modePlacementChateau;
            textures->stateToolbar.modeMenu = false;
            textures->stateToolbar.modeSave = false;
            textures->stateToolbar.modeDestruction = false;
            textures->stateToolbar.modePlacementRoute = false;
            textures->stateToolbar.modePlacementCentrale = false;
            textures->stateToolbar.modePlacementHabitation = false;
            textures->stateToolbar.modeChangementNiveau = false;
            textures->currentBuildMode = (textures->currentBuildMode == BUILD_MODE_CHATEAU ? BUILD_MODE_NONE
                                                                                           : BUILD_MODE_CHATEAU);
        }
    } else {
        if (CheckCollisionPointRec(mousePos, (Rectangle) {40, 851, textures->toolbarIcons[ICON_GRID].width,
                                                          textures->toolbarIcons[ICON_GRID].height})) {
            textures->stateToolbar.hoverNiveauNormal = true;
        }
        if (CheckCollisionPointRec(mousePos, (Rectangle) {150, 851, textures->toolbarIcons[ICON_ELECTRICITY_GRID].width,
                                                          textures->toolbarIcons[ICON_ELECTRICITY_GRID].height})) {
            textures->stateToolbar.hoverNiveauElectricite = true;
        }
        if (CheckCollisionPointRec(mousePos, (Rectangle) {265, 851, textures->toolbarIcons[ICON_WATER_GRID].width,
                                                          textures->toolbarIcons[ICON_WATER_GRID].height})) {
            textures->stateToolbar.hoverNiveauEau = true;
        }
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
            textures->stateToolbar.hoverChangementNiveau = true;
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
            textures->stateToolbar.hoverRoute = true;
        }
        if (CheckCollisionPointRec(mousePos, (Rectangle) {1082, 954, textures->toolbarIcons[ICON_HABITATION].width,
                                                          textures->toolbarIcons[ICON_HABITATION].height})) {
            textures->stateToolbar.hoverHabitation = true;
        }
        if (CheckCollisionPointRec(mousePos, (Rectangle) {1159, 954, textures->toolbarIcons[ICON_CENTRALE].width,
                                                          textures->toolbarIcons[ICON_CENTRALE].height})) {
            textures->stateToolbar.hoverCentrale = true;
        }
        if (CheckCollisionPointRec(mousePos, (Rectangle) {1229, 954, textures->toolbarIcons[ICON_CHATEAU].width,
                                                          textures->toolbarIcons[ICON_CHATEAU].height})) {
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