
#ifndef ECECITY_GAMEPLAY_H
#define ECECITY_GAMEPLAY_H

#include "jeu.h"
#include <stdlib.h>
#include "sim/sim.h"
#include "ui.h"

typedef struct GameplayScreen_t {
    ScreenInfo_t screen_info;
    /// La simulation
    SimWorld_t* world;
    /// Les textures
    UITextures_t textures;
} GameplayScreen_t;

// callbacks de l'écran.

/// Crée un écran de gameplay prêt à être utilisé.
GameplayScreen_t* gameplay_create_screen();

void gameplay_on_enter(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_on_exit(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_update(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_draw(Jeu_t* jeu, GameplayScreen_t *gameplay);


#endif //ECECITY_GAMEPLAY_H
