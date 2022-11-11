#include "screens/gameplay.h"

void try_place_building(GameplayScreen_t *gameplay);

GameplayScreen_t *gameplay_create_screen() {
    GameplayScreen_t *gameplay = malloc(sizeof(GameplayScreen_t));
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
    gameplay->world = sim_world_create(Capitaliste_t, 10000);
    ui_charger_textures(&gameplay->state);
    sprite_sheet_load(&gameplay->spriteSheet);
    gameplay->state.currentBuildMode = BUILD_MODE_NONE;
    gameplay->state.timeScale = 1.0f;
    gameplay->elapsedTime = 0.f;
}

void gameplay_on_exit(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    sim_world_destroy(gameplay->world);
}

void gameplay_update(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    ui_update_toolbar(&gameplay->state, gameplay->world);
    gameplay->mousePos = mouse_to_iso((Vector2I) {GetMouseX(), GetMouseY()},
                                      gameplay->spriteSheet.spriteDetectionTuile);
    try_place_building(gameplay);

    gameplay->elapsedTime += GetFrameTime();

    if (gameplay->elapsedTime >= 1.0f / gameplay->state.timeScale) {
        sim_world_step(gameplay->world);
        gameplay->elapsedTime = 0.f;
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

    ui_draw_toolbar(&gameplay->state, gameplay->world);
}


void try_place_building(GameplayScreen_t *gameplay) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        switch (gameplay->state.currentBuildMode) {
            case BUILD_MODE_ROUTE:
                if (sim_check_can_place(gameplay->world, false, gameplay->mousePos.x, gameplay->mousePos.y, 1, 1) &&
                    gameplay->world->monnaie >= 10) {
                    sim_place_entity(gameplay->world, KIND_ROUTE, gameplay->mousePos.x, gameplay->mousePos.y);
                    gameplay->world->monnaie -= 10;
                }
                break;

            case BUILD_MODE_HABITATION:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 3,
                                        3) && gameplay->world->monnaie >= 1000) {
                    sim_place_entity(gameplay->world, KIND_HABITATION, gameplay->mousePos.x,
                                     gameplay->mousePos.y);
                    gameplay->world->monnaie -= 1000;
                }
                break;

            case BUILD_MODE_CENTRALE:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 6,
                                        4) && gameplay->world->monnaie >= 5000) {
                    sim_place_entity(gameplay->world, KIND_CENTRALE, gameplay->mousePos.x,
                                     gameplay->mousePos.y);
                    gameplay->world->monnaie -= 5000;
                }
                break;

            case BUILD_MODE_CHATEAU:
                if (sim_check_can_place(gameplay->world, true, gameplay->mousePos.x, gameplay->mousePos.y, 4,
                                        6) && gameplay->world->monnaie >= 5000) {
                    sim_place_entity(gameplay->world, KIND_CHATEAU, gameplay->mousePos.x, gameplay->mousePos.y);
                    gameplay->world->monnaie -= 5000;
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