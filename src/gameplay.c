
#include <stdio.h>
#include "screens/gameplay.h"


GameplayScreen_t* gameplay_create_screen() {
    GameplayScreen_t* gameplay = malloc(sizeof(GameplayScreen_t));
    gameplay->screen_info = (ScreenInfo_t) {
            .draw_callback = gameplay_draw,
            .update_callback = gameplay_update,
            .on_enter_callback = gameplay_on_enter,
            .on_exit_callback = gameplay_on_exit,
            .screen_name = "GAMEPLAY"
    };
    return gameplay;
}

void gameplay_on_enter(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    gameplay->world = sim_world_create(Capitaliste_t, 10000);
    ui_charger_textures(&gameplay->state);
    sprite_sheet_load(&gameplay->spriteSheet);
    gameplay->state.currentBuildMode = BUILD_MODE_NONE;
}

void gameplay_on_exit(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    sim_world_destroy(gameplay->world);
}

void gameplay_update(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    sim_world_step(gameplay->world);
    ui_update_toolbar(&gameplay->state, gameplay->world);
}

void gameplay_draw(Jeu_t* jeu, GameplayScreen_t *gameplay) {

    affichage_draw_terrain_background(&gameplay->spriteSheet, gameplay->world);
    affichage_draw_entities(&gameplay->spriteSheet, gameplay->world);

    Vector2I v = mouse_to_iso((Vector2I){GetMouseX(), GetMouseY()}, gameplay->spriteSheet.spriteDetectionTuile);

    int w = 0;
    int h = 0;
    enum SPRITE_MAP bat = SPRITE_HOOVER;
    switch (gameplay->state.currentBuildMode) {
        case BUILD_MODE_ROUTE:
            w = 1;
            h = 1;
            bat = SPRITE_ROUTE_0;
            break;

        case BUILD_MODE_HABITATION:
            w = 3;
            h = 3;
            bat = SPRITE_MAISON_3X3;
            break;

        case BUILD_MODE_CENTRALE:
            w = 6;
            h = 4;
            bat = SPRITE_ENERGY_6X4;
            break;

        case BUILD_MODE_CHATEAU:
            w = 4;
            h = 6;
            bat = SPRITE_EAU_4X6;
            break;

        default:
            break;
    }

    bool is_valid = sim_check_can_place(gameplay->world, w > 1, v.x, v.y, w, h);
    sprite_sheet_draw_sprite(&gameplay->spriteSheet, bat, is_valid ? GREEN : RED, v.x, v.y);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        switch (gameplay->state.currentBuildMode) {
            case BUILD_MODE_ROUTE:
                if (is_valid)
                    sim_place_entity(gameplay->world, KIND_ROUTE, v.x, v.y);
                break;

            case BUILD_MODE_HABITATION:
                if (is_valid)
                    sim_place_entity(gameplay->world, KIND_HABITATION, v.x, v.y);
                break;

            case BUILD_MODE_CENTRALE:
                if (is_valid)
                    sim_place_entity(gameplay->world, KIND_CENTRALE, v.x, v.y);
                break;

            case BUILD_MODE_CHATEAU:
                if (is_valid)
                    sim_place_entity(gameplay->world, KIND_CHATEAU, v.x, v.y);
                break;


            case BUILD_MODE_DESTROY:
                sim_destroy_entity(gameplay->world, v.x, v.y);
                break;

                
            default:
                break;
        }
    }

    ui_draw_toolbar(&gameplay->state, gameplay->world);
}
