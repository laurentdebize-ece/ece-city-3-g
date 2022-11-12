#include <stdio.h>
#include "screens/gameplay.h"
#include "affichage.h"
#include "carte.h"
#include "placement.h"
#include "utils/grille.h"
#include "destruction.h"
#include "bfs.h"

void try_place_building(GameplayScreen_t *gameplay);

GameplayScreen_t *gameplay_create_screen() {
    GameplayScreen_t *gameplay = calloc(1, sizeof(GameplayScreen_t));
    gameplay->screen_info = (ScreenInfo_t) {
            .draw_callback = gameplay_draw,
            .update_callback = gameplay_update,
            .on_enter_callback = gameplay_on_enter,
            .on_exit_callback = gameplay_on_exit,
            .screen_name = "GAMEPLAY"
    };
    return gameplay;
}

void gameplay_on_enter(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    gameplay->world = sim_world_create(Capitaliste_t, 500000);
    ui_charger_textures(&gameplay->state);
    sprite_sheet_load(&gameplay->spriteSheet);
    gameplay->state.currentBuildMode = BUILD_MODE_NONE;
    init_world(gameplay);
    gameplay->reloadCarte = true;
    gameplay->state.timeScale = 1.0f;
    gameplay->elapsedTime = 0.f;
}

void gameplay_on_exit(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    sim_world_destroy(gameplay->world);
}

void gameplay_update(Jeu_t *jeu, GameplayScreen_t *gameplay) {
void gameplay_update(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    /// Actualisation des données positions souris et états souris
    update_state_mouse(gameplay);
    /// Actualisation des états de la toolbar (hover, click, etc.)
    ui_update_toolbar(&gameplay->state, gameplay->world);
    gameplay->mousePos = mouse_to_iso((Vector2I) {GetMouseX(), GetMouseY()},
                                      gameplay->spriteSheet.spriteDetectionTuile);
    try_place_building(gameplay);

    gameplay->elapsedTime += GetFrameTime();

    if (gameplay->elapsedTime >= 1.0f / gameplay->state.timeScale) {
        sim_world_step(gameplay->world);
        gameplay->elapsedTime = 0.f;
    }
    /// En mode placement route création de la route en surbrillance
    check_changement_cellule_placement_route(gameplay);
    /// Placement de la route et des bâtiments
    update_placement_batiment(gameplay);
    /// Actualisation lors de la destruction d'un bâtiment
    check_destruction(gameplay);
    /// Actualisation de la carte après placement si nécessaire
    check_upadate_carte(gameplay);
    /// Actualisation de la carte après évolution si nécessaire
    sim_world_step(gameplay->world);


    /// Tests debug
    if(IsKeyPressed(KEY_P)){
        struct Maillon_t* parcours = gameplay->world->habitations->premier;

        while (parcours != NULL){
            for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
                printf("Habitation (%2.f, %2.f), Chateau (%2.f, %2.f) : distance : %d, Connexion electrique : %d\n",
                       ((Habitation_t *) parcours->data)->position.x, ((Habitation_t *) parcours->data)->position.y,
                       ((Habitation_t *) parcours->data)->position_chateau_eau[j].x,
                       ((Habitation_t *) parcours->data)->position_chateau_eau[j].y,
                       ((Habitation_t *) parcours->data)->distance_chateau_eau[j],
                       ((Habitation_t *)parcours->data)->connexion_reseau_electrique);
            }
            parcours = parcours->next;
        }
    }
}

void gameplay_draw(Jeu_t *jeu, GameplayScreen_t *gameplay) {

    /// Affichage de la toolbar
    ui_draw_toolbar(&gameplay->state, gameplay->world);

    /// Affichage de la carte
    draw_map(gameplay);

    Vector2I v = mouse_to_iso((Vector2I) {GetMouseX(), GetMouseY()}, gameplay->spriteSheet.spriteDetectionTuile);
    /// Affichage demm la cellule iso sous la souris (hover)
    if(!gameplay->state.stateMouse.outOfMapBorders)
    {
        bool is_valid = sim_check_can_place(gameplay->world, false, v.x, v.y, 1, 1);
        sprite_sheet_draw_sprite(&gameplay->spriteSheet, SPRITE_HOOVER, is_valid ? GREEN : RED, v.x, v.y);
    }

    /// Affichage de la route en surbrillance
    draw_route_selectionee(gameplay);
    /// Affichage du bâtiment à placer en surbrillance
    draw_placement_batiment(gameplay);


    /// Tests debug
    DrawText(TextFormat("%d", gameplay->state.stateMouse.outOfMapBorders), 10, 10, 20, RED);
    DrawText(TextFormat("(%d, %d)", gameplay->state.stateMouse.celluleIso.x, gameplay->state.stateMouse.celluleIso.y),
             10, 30, 20, RED);
    bool test = false;
    if(gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].type == KIND_ROUTE){
        test = true;
    } else {
        test = false;
    }
    DrawText(TextFormat("KIND_ROUTE : %d", test), 10, 50, 20, BLACK);
}
    affichage_draw_terrain_background(&gameplay->spriteSheet, gameplay->world);
    affichage_draw_entities(&gameplay->spriteSheet, gameplay->world,
                            gameplay->state.currentBuildMode == BUILD_MODE_ROUTE ? LAYER_ROUTES : LAYER_ALL);

    Vector2I v = mouse_to_iso((Vector2I) {GetMouseX(), GetMouseY()}, gameplay->spriteSheet.spriteDetectionTuile);

    if (gameplay->state.currentBuildMode != BUILD_MODE_NONE)
        affichage_draw_build_preview(&gameplay->spriteSheet, gameplay->world, v,
                                     ui_buildmode_to_casekind(gameplay->state.currentBuildMode));

    ui_draw_toolbar(&gameplay->state, gameplay->world);
}


void try_place_building(GameplayScreen_t *gameplay) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        switch (gameplay->state.currentBuildMode) {
            case BUILD_MODE_ROUTE:
                if (sim_check_can_place(gameplay->world, false, gameplay->mousePos.x, gameplay->mousePos.y, 1, 1) &&
                    gameplay->world->monnaie >= ROUTE_PRIX_CONSTRUCTION) {
                    sim_place_entity(gameplay->world, KIND_ROUTE, gameplay->mousePos.x, gameplay->mousePos.y);
                    gameplay->world->monnaie -= ROUTE_PRIX_CONSTRUCTION;
                }
                break;

            case BUILD_MODE_HABITATION:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 3,
                                        3) && gameplay->world->monnaie >= HABITATION_PRIX_CONSTRUCTION) {
                    sim_place_entity(gameplay->world, KIND_HABITATION, gameplay->mousePos.x,
                                     gameplay->mousePos.y);
                    gameplay->world->monnaie -= HABITATION_PRIX_CONSTRUCTION;
                }
                break;

            case BUILD_MODE_CENTRALE:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 6,
                                        4) && gameplay->world->monnaie >= CENTRALE_PRIX_CONSTRUCTION) {
                    sim_place_entity(gameplay->world, KIND_CENTRALE, gameplay->mousePos.x,
                                     gameplay->mousePos.y);
                    gameplay->world->monnaie -= CENTRALE_PRIX_CONSTRUCTION;
                }
                break;

            case BUILD_MODE_CHATEAU:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 4,
                                        6) && gameplay->world->monnaie >= CHATEAU_PRIX_CONSTRUCTION) {
                    sim_place_entity(gameplay->world, KIND_CHATEAU, gameplay->mousePos.x, gameplay->mousePos.y);
                    gameplay->world->monnaie -= CHATEAU_PRIX_CONSTRUCTION;
                }
                break;

            case BUILD_MODE_DESTROY:
                sim_destroy_entity(gameplay->world, gameplay->mousePos.x, gameplay->mousePos.y);
                break;

            default:
                break;
        }
    }
}