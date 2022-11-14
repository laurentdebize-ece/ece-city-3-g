#include "destruction.h"
#include "raylib.h"

void check_destruction(GameplayScreen_t* gameplay){
    if(gameplay->state.stateToolbar.modeDestruction){
        if(!gameplay->state.stateMouse.outOfMapBorders && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            update_word_map_after_destroy(gameplay);
        }
    }
}

void update_boucle_for_destruction(GameplayScreen_t* gameplay, int coordX, int coordY, Orientation_t orientation){

    int w;
    int h;

    if(orientation == ORIENTATION_6X4){
        w = 6;
        h = 4;
    } else if (orientation == ORIENTATION_4X6){
        w = 4;
        h = 6;
    } else if (orientation == ORIENTATION_NULL){
        w = 3;
        h = 3;
    } else {
        w = 1;
        h = 1;
    }


    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            gameplay->world->map[coordY + y][coordX + x].type = KIND_VIDE;
        }
    }
}

void update_word_map_after_destroy(GameplayScreen_t* gameplay){
    if (gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].type != KIND_VIDE){
        switch (gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].type) {
            case KIND_TERRAIN_VAGUE:
            {
                Habitation_t* habitation = (Habitation_t*) gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].donnees;
                update_boucle_for_destruction(gameplay, habitation->position.x, habitation->position.y, habitation->orientation);
                liste_supprimer(gameplay->world->habitations, habitation);
                habitation_free(habitation);
                break;
            }

            case KIND_CABANE:
            {
                Habitation_t* habitation = (Habitation_t*) gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].donnees;
                update_boucle_for_destruction(gameplay, habitation->position.x, habitation->position.y, habitation->orientation);
                liste_supprimer(gameplay->world->habitations, habitation);
                habitation_free(habitation);
                break;
            }

            case KIND_MAISON:
            {
                Habitation_t* habitation = (Habitation_t*) gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].donnees;
                update_boucle_for_destruction(gameplay, habitation->position.x, habitation->position.y, habitation->orientation);
                liste_supprimer(gameplay->world->habitations, habitation);
                habitation_free(habitation);
                break;
            }

            case KIND_IMMEUBLE:
            {
                Habitation_t* habitation = (Habitation_t*) gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].donnees;
                update_boucle_for_destruction(gameplay, habitation->position.x, habitation->position.y, habitation->orientation);
                liste_supprimer(gameplay->world->habitations, habitation);
                habitation_free(habitation);
                break;
            }

            case KIND_GRATTES_CIEL:
            {
                Habitation_t* habitation = (Habitation_t*) gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].donnees;
                update_boucle_for_destruction(gameplay, habitation->position.x, habitation->position.y, habitation->orientation);
                liste_supprimer(gameplay->world->habitations, habitation);
                habitation_free(habitation);
                break;
            }

            case KIND_CENTRALE:
            {
                CentraleElectrique_t* centrale = (CentraleElectrique_t*) gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].donnees;
                liste_supprimer(gameplay->world->centrales, centrale);
                update_boucle_for_destruction(gameplay, centrale->position.x, centrale->position.y, centrale->orientation);
                centrale_free(centrale);
                break;
            }

            case KIND_CHATEAU:
            {
                ChateauEau_t* chateau = (ChateauEau_t*) gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].donnees;
                liste_supprimer(gameplay->world->chateaux, chateau);
                update_boucle_for_destruction(gameplay, chateau->position.x, chateau->position.y, chateau->orientation);
                chateau_free(chateau);
                break;
            }

            case KIND_ROUTE:
            {
                gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].type = KIND_VIDE;
                gameplay->world->map[gameplay->state.stateMouse.celluleIso.y][gameplay->state.stateMouse.celluleIso.x].donnees = NULL;
                break;
            }

            default:
            {
                break;
            }
        }
        gameplay->reloadCarte = true;
    }
}