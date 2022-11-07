
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
}

void gameplay_on_exit(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    sim_world_destroy(gameplay->world);
}

void gameplay_update(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    sim_world_step(gameplay->world);
}

void gameplay_draw(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    ClearBackground(GREEN);
    ui_draw_toolbar(&gameplay->textures);
}
