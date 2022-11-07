
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
    ui_charger_textures(&gameplay->textures);
    sprite_sheet_load(&gameplay->spriteSheet);
    gameplay->curr_build_mode = 0;
}

void gameplay_on_exit(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    sim_world_destroy(gameplay->world);
}

void gameplay_update(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    sim_world_step(gameplay->world);
    if (IsKeyPressed(KEY_SPACE)) {
        gameplay->curr_build_mode = (gameplay->curr_build_mode + 1) % 3;
        printf("Mode de construction: %d \n\r", gameplay->curr_build_mode);
    }
}

void gameplay_draw(Jeu_t* jeu, GameplayScreen_t *gameplay) {

    affichage_draw_terrain_background(&gameplay->spriteSheet);
    affichage_draw_entities(&gameplay->spriteSheet, gameplay->world);

    int x = GetMouseX() / LARGUEUR_TUILE_ISO;
    int y = GetMouseY() / HAUTEUR_TUILE_ISO;

    Vector2I v = cartesien_to_iso((Vector2I){x, y});

    int w = 0;
    int h = 0;
    enum SPRITE_MAP bat = ROUTE_1;
    switch (gameplay->curr_build_mode) {
        case 0:
            w = 1;
            h = 1;
            bat = ROUTE_0;
            break;

        case 1:
            w = 3;
            h = 3;
            bat = MAISON_3X3;
            break;

        case 2:
            w = 6;
            h = 4;
            bat = ENERGY_6X4;
            break;
    }

    bool is_valid = sim_check_can_place(gameplay->world, v.x, v.y, w, h);
    sprite_sheet_draw_sprite(&gameplay->spriteSheet, bat, is_valid ? GREEN : RED, v.x, v.y);
    ui_draw_toolbar(&gameplay->textures, gameplay->world);
}
