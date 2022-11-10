#include "bfs.h"
#include "screens/gameplay.h"

void parcours_bfs(GameplayScreen_t* gameplay, Parcours_BFS_t* parcours_bfs) {
    for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
        for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
            if(gameplay->world->map[y][x].sprite == SPRITE_ENERGY_4X6){
                parcours_bfs->tabCentraleElec[parcours_bfs->nbCentraleElec].position = (Vector2) {x, y};
                parcours_bfs->tabCentraleElec[parcours_bfs->nbCentraleElec].type4X6 = true;
                parcours_bfs->nbCentraleElec++;
            } else if(gameplay->world->map[y][x].sprite == SPRITE_ENERGY_6X4){
                parcours_bfs->tabCentraleElec[parcours_bfs->nbCentraleElec].position = (Vector2) {x, y};
                parcours_bfs->tabCentraleElec[parcours_bfs->nbCentraleElec].type4X6 = true;
                parcours_bfs->nbCentraleElec++;
            }
        }

    }

    for (int i = 0; i < parcours_bfs->nbCentraleElec; i++) {

    }
}