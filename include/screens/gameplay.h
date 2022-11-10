#ifndef ECECITY_GAMEPLAY_H
#define ECECITY_GAMEPLAY_H

#include "jeu.h"
#include "sim/sim.h"
#include "ui.h"
#include "spritesheet.h"
#include "stdio.h"

#define SPRITELARGEUR 40
#define SPRITEHAUTEUR 20

#define ORIGINEX 17
#define ORIGINEY 3

#define SIM_MAP_LARGEUR 45
#define SIM_MAP_HAUTEUR 35

typedef struct {

    FILE* fichierTxt;
    FILE* fichierTxtWrite;
    FILE* autoTxt;
    FILE* autoTxtWrite;

} Loader_t;

typedef struct GameplayScreen_t {
    ScreenInfo_t screen_info;
    /// La simulation
    SimWorld_t* world;
    /// Les textures pour le dessin de l'IU.
    UIState state;
    /// Les textures pour le dessin de la carte.
    SpriteSheet_t spriteSheet;
    /// Permet de savoir s'il y a eu un changement sur l'affichage de la carte (placement, destruction)
    bool reloadCarte;
    /// Les fichiers pour le chargement de la carte.
    Loader_t loader;
} GameplayScreen_t;

// callbacks de l'écran.

/// Crée un écran de gameplay prêt à être utilisé.
GameplayScreen_t* gameplay_create_screen();

void gameplay_on_enter(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_on_exit(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_update(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_draw(Jeu_t* jeu, GameplayScreen_t *gameplay);

#endif //ECECITY_GAMEPLAY_H
