
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
}

void gameplay_on_exit(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    sim_world_destroy(gameplay->world);
}

void gameplay_update(Jeu_t* jeu, GameplayScreen_t *gameplay) {
    sim_world_step(gameplay->world);
}

void gameplay_draw(Jeu_t* jeu, GameplayScreen_t *gameplay) {


    // dessin du terrain vide
    for (int i = 0; i < 45; ++i)
        for (int j = 0; j < 35; ++j)
            sprite_sheet_draw_sprite(&gameplay->spriteSheet, TERRAIN_0, WHITE, i, j);


    sprite_sheet_draw_sprite(&gameplay->spriteSheet, EAU_6X4, WHITE, 0, 0);

    int x = GetMouseX() / LARGUEUR_TUILE_ISO;
    int y = GetMouseY() / HAUTEUR_TUILE_ISO;

    Vector2I v = cartesien_to_iso((Vector2I){x, y});
    sprite_sheet_draw_sprite(&gameplay->spriteSheet, EAU_4X6, RED, v.x, v.y);

    ui_draw_toolbar(&gameplay->textures, gameplay->world);
}
