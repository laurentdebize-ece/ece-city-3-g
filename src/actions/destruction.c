#include "destruction.h"
#include "raylib.h"

void check_destruction(GameplayScreen_t* gameplay){
    if(gameplay->state.stateToolbar.modeDestruction){
        if(!gameplay->state.stateMouse.outOfMapBorders && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            update_word_map_after_destroy(gameplay);
        }
    }
}

void update_boucle_for_destruction(GameplayScreen_t* gameplay, int coordX, int coordY, int w, int h){
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            gameplay->world->map[coordY + y][coordX + x].type = KIND_VIDE;
        }
    }
}

void update_word_map_after_destroy(GameplayScreen_t* gameplay){
    if (gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].sprite != SPRITE_VIDE && gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].sprite != SPRITE_TERRAIN_0){
        switch (gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].type) {
            case KIND_CENTRALE:
                if(gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].sprite == SPRITE_ENERGY_6X4){
                    update_boucle_for_destruction(gameplay, gameplay->state.stateMouse.celluleIso.x, gameplay->state.stateMouse.celluleIso.y, 6, 4);
                } else {
                    update_boucle_for_destruction(gameplay, gameplay->state.stateMouse.celluleIso.x, gameplay->state.stateMouse.celluleIso.y, 4, 6);
                }
                break;
            case KIND_CHATEAU:
                if(gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].sprite == SPRITE_EAU_6X4){
                    update_boucle_for_destruction(gameplay, gameplay->state.stateMouse.celluleIso.x, gameplay->state.stateMouse.celluleIso.y, 6, 4);
                } else {
                    update_boucle_for_destruction(gameplay, gameplay->state.stateMouse.celluleIso.x, gameplay->state.stateMouse.celluleIso.y, 4, 6);
                }
                break;
            case KIND_ROUTE:
                update_boucle_for_destruction(gameplay, gameplay->state.stateMouse.celluleIso.x, gameplay->state.stateMouse.celluleIso.y, 1, 1);
                break;
            default:
                update_boucle_for_destruction(gameplay, gameplay->state.stateMouse.celluleIso.x, gameplay->state.stateMouse.celluleIso.y, 3, 3);
                break;
        }
        gameplay->reloadCarte = true;
    }
}