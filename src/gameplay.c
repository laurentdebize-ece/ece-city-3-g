
#include <stdio.h>
#include "screens/gameplay.h"
#include "utils/capacite.h"
#include "sauvegarde.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void try_place_building(GameplayScreen_t *gameplay);
void draw_debug_info(GameplayScreen_t *gameplay);
void update_debug_info(GameplayScreen_t *gameplay);


GameplayScreen_t *gameplay_create_screen(SimWorld_t* world) {
    GameplayScreen_t *gameplay = malloc(sizeof(GameplayScreen_t));
    gameplay->screen_info = (ScreenInfo_t) {
            .draw_callback = gameplay_draw,
            .update_callback = gameplay_update,
            .on_enter_callback = gameplay_on_enter,
            .on_exit_callback = gameplay_on_exit,
            .screen_name = "GAMEPLAY"
    };
    gameplay->world = world;
    return gameplay;
}

void gameplay_on_enter(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    ui_charger_textures(&gameplay->state);
    sprite_sheet_load(&gameplay->spriteSheet);
    gameplay->state.currentBuildMode = BUILD_MODE_NONE;
    gameplay->state.timeScale = 1.0f;
    gameplay->elapsedTime = 0.f;


    gameplay->dbgDisplayChateauNeighbors = 0;
    gameplay->dbgDisplayCentraleNeighbors = 0;

    gameplay->state.stateToolbar.modePlacementChateau = false;
    gameplay->state.stateToolbar.modeMenu = false;
    gameplay->state.stateToolbar.modeSave = false;
    gameplay->state.stateToolbar.modeDestruction = false;
    gameplay->state.stateToolbar.modePlacementRoute = false;
    gameplay->state.stateToolbar.modePlacementCentrale = false;
    gameplay->state.stateToolbar.modePlacementHabitation = false;
    gameplay->state.stateToolbar.modeChangementNiveau = false;
    gameplay->state.stateToolbar.stateMenuSave.modeAjout = false;
    gameplay->state.stateToolbar.stateMenuSave.resetNbSauvegardes = false;
    gameplay->loader.nb_sauvegardes = 0;
    gameplay->state.stateToolbar.stateMenuSave.num_component_select = -1;
    gameplay->state.stateToolbar.stateMenuSave.num_component_hover = -1;
    gameplay->state.stateToolbar.relaod_carte = false;
    gameplay->state.stateToolbar.hoverNiveauNormal = false;
    gameplay->state.stateToolbar.hoverNiveauEau = false;
    gameplay->state.stateToolbar.hoverNiveauElectricite = false;
    gameplay->state.stateToolbar.niveauEau = false;
    gameplay->state.stateToolbar.niveauElectricite = false;
    gameplay->state.stateToolbar.niveauNormal = true;

}

void gameplay_on_exit(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    sim_world_destroy(gameplay->world);
}

void gameplay_update(Jeu_t *jeu, GameplayScreen_t *gameplay) {


    ui_update_toolbar(&gameplay->state, gameplay->world);

    gameplay->mousePos = mouse_to_iso((Vector2I) {GetMouseX(), GetMouseY()},
                                      gameplay->spriteSheet.spriteDetectionTuile);

    gameplay->elapsedTime += GetFrameTime();

    if (gameplay->elapsedTime >= 1.0f / gameplay->state.timeScale) {
        sim_world_step(gameplay->world);
        gameplay->elapsedTime = 0.f;
    }

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            try_place_building(gameplay);
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        try_place_building(gameplay);


    update_menu_sauvegarde(gameplay);

    /// menus de débogage.
    update_debug_info(gameplay);

    if(gameplay->state.stateToolbar.relaod_carte){
        sim_sauvegarder(gameplay->world, "../saves/txt/auto.txt");
    }
}

void gameplay_draw(Jeu_t *jeu, GameplayScreen_t *gameplay) {

    affichage_draw_terrain_background(&gameplay->spriteSheet, gameplay->world);
    affichage_draw_entities(&gameplay->spriteSheet, gameplay->world,
                            gameplay->state.currentBuildMode == BUILD_MODE_ROUTE ? LAYER_ROUTES : LAYER_ALL);

    Vector2I v = mouse_to_iso((Vector2I) {GetMouseX(), GetMouseY()}, gameplay->spriteSheet.spriteDetectionTuile);

    if (gameplay->state.currentBuildMode != BUILD_MODE_NONE)
        affichage_draw_build_preview(&gameplay->spriteSheet, gameplay->world, v,
                                     ui_buildmode_to_casekind(gameplay->state.currentBuildMode));


    affichage_menu_sauvegarde(gameplay);

    //draw_debug_info(gameplay);


    ui_draw_toolbar(&gameplay->state, gameplay->world);

    if (gameplay->state.stateToolbar.niveauEau) {
        afficher_level_eau(&gameplay->spriteSheet, gameplay->world);
        afficher_capacite(gameplay->world);
    } else if (gameplay->state.stateToolbar.niveauElectricite) {
        afficher_level_elec(&gameplay->spriteSheet, gameplay->world, gameplay);
        afficher_capacite(gameplay->world);
    }

    afficher_etat_alim_eau(&gameplay->spriteSheet, gameplay->world);
    afficher_etat_alim_elec(&gameplay->spriteSheet, gameplay->world);
}

void try_place_building(GameplayScreen_t *gameplay) {
        switch (gameplay->state.currentBuildMode) {
            case BUILD_MODE_ROUTE:
                if (sim_check_can_place(gameplay->world, false, gameplay->mousePos.x, gameplay->mousePos.y, 1, 1) &&
                    gameplay->world->monnaie >= ROUTE_PRIX_CONSTRUCTION) {
                    sim_place_entity(gameplay->world, KIND_ROUTE, gameplay->mousePos.x, gameplay->mousePos.y, true);
                    gameplay->world->monnaie -= ROUTE_PRIX_CONSTRUCTION;
                    gameplay->state.stateToolbar.relaod_carte = true;
                }
                break;

            case BUILD_MODE_HABITATION:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 3,
                                        3) && gameplay->world->monnaie >= HABITATION_PRIX_CONSTRUCTION) {
                    sim_place_entity(gameplay->world, KIND_HABITATION, gameplay->mousePos.x,
                                     gameplay->mousePos.y, true);
                    gameplay->world->monnaie -= HABITATION_PRIX_CONSTRUCTION;
                    gameplay->state.stateToolbar.relaod_carte = true;
                }
                break;

            case BUILD_MODE_CENTRALE:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 6,
                                        4) && gameplay->world->monnaie >= CENTRALE_PRIX_CONSTRUCTION) {
                    sim_place_entity(gameplay->world, KIND_CENTRALE, gameplay->mousePos.x,
                                     gameplay->mousePos.y, true);
                    gameplay->world->monnaie -= CENTRALE_PRIX_CONSTRUCTION;
                    gameplay->state.stateToolbar.relaod_carte = true;
                }
                break;

            case BUILD_MODE_CHATEAU:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 4,
                                        6) && gameplay->world->monnaie >= CHATEAU_PRIX_CONSTRUCTION) {
                    sim_place_entity(gameplay->world, KIND_CHATEAU, gameplay->mousePos.x, gameplay->mousePos.y, true);
                    gameplay->world->monnaie -= CHATEAU_PRIX_CONSTRUCTION;
                    gameplay->state.stateToolbar.relaod_carte = true;
                }
                break;

            case BUILD_MODE_DESTROY:
                sim_destroy_entity(gameplay->world, gameplay->mousePos.x, gameplay->mousePos.y);
                gameplay->state.stateToolbar.relaod_carte = true;
                break;

            default:
                break;
        }
}


void update_debug_info(GameplayScreen_t* gameplay) {
    if (IsKeyPressed(KEY_H)) {
        gameplay->dbgDisplayChateauNeighbors = (gameplay->dbgDisplayChateauNeighbors + 1) % (gameplay->world->chateaux->taille + 1);
    }

    if (IsKeyPressed(KEY_C)) {
        gameplay->dbgDisplayCentraleNeighbors = (gameplay->dbgDisplayCentraleNeighbors + 1) % (gameplay->world->centrales->taille + 1);
    }

    gameplay->dbgDisplayChateauNeighbors = MIN(gameplay->dbgDisplayChateauNeighbors, gameplay->world->chateaux->taille + 1);
    gameplay->dbgDisplayCentraleNeighbors = MIN(gameplay->dbgDisplayCentraleNeighbors, gameplay->world->centrales->taille + 1);
}

void draw_debug_info(GameplayScreen_t *gameplay) {
    if (gameplay->dbgDisplayChateauNeighbors > 0) {
        struct Maillon_t* chateaux = gameplay->world->chateaux->premier;
        int n = 1;
        while (chateaux) {
            if (n == gameplay->dbgDisplayChateauNeighbors) {
                ChateauEau_t* chateau = chateaux->data;
                affichage_debug_draw_voisins_chateau(&gameplay->spriteSheet, chateau, BLUE);
                break;
            }
            n++;
            chateaux = chateaux->next;
        }
    }

    if (gameplay->dbgDisplayCentraleNeighbors > 0) {
        struct Maillon_t* centrales = gameplay->world->centrales->premier;
        int n = 1;
        while (centrales) {
            if (n == gameplay->dbgDisplayCentraleNeighbors) {
                CentraleElectrique_t* centrale = centrales->data;
                affichage_debug_draw_voisins_centrale(&gameplay->spriteSheet, centrale, ORANGE);
                break;
            }
            n++;
            centrales = centrales->next;
        }
    }
}
