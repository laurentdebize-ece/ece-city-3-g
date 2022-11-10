#include "carte.h"

void init_world(GameplayScreen_t *gameplay) {

    gameplay->state.stateToolbar.stateBuildRoad.depart[0].x = -1;
    gameplay->state.stateToolbar.stateBuildRoad.depart[0].y = -1;

    for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
        for (int x = 0; x < SIM_MAP_LARGEUR; x++) {

            //Permet de définir le type de bloc
            gameplay->world->map[y][x].type = KIND_VIDE;
            gameplay->world->map[y][x].tinte = WHITE;

            gameplay->world->map[y][x].position.x = (ORIGINEX * SPRITELARGEUR) + x * SPRITELARGEUR / 2 - y * SPRITELARGEUR / 2;

            gameplay->world->map[y][x].position.y = (ORIGINEY * SPRITEHAUTEUR) + x * SPRITEHAUTEUR / 2 + y * SPRITEHAUTEUR / 2;

        }
    }
}