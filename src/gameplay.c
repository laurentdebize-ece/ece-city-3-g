#include <stdio.h>
#include "screens/gameplay.h"
#include "affichage.h"
#include "carte.h"
#include "placement.h"
#include "utils/grille.h"
#include "destruction.h"
#include "bfs.h"

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
    gameplay->world = sim_world_create(Capitaliste_t, 10000);
    ui_charger_textures(&gameplay->state);
    sprite_sheet_load(&gameplay->spriteSheet);
    gameplay->state.currentBuildMode = BUILD_MODE_NONE;
    init_world(gameplay);
    gameplay->reloadCarte = true;
}

void gameplay_on_exit(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    sim_world_destroy(gameplay->world);
}

void gameplay_update(Jeu_t *jeu, GameplayScreen_t *gameplay) {
    /// Actualisation des données positions souris et états souris
    update_state_mouse(gameplay);
    /// Actualisation des états de la toolbar (hover, click, etc.)
    ui_update_toolbar(&gameplay->state, gameplay->world);
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