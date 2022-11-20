
#ifndef ECECITY_GAMEPLAY_H
#define ECECITY_GAMEPLAY_H

#include "jeu.h"
#include <stdlib.h>
#include "sim/sim.h"
#include "ui.h"
#include "spritesheet.h"
#include "utils/grille.h"
#include "affichage.h"
#include "bfs.h"
#include "stdio.h"
#include "dirent.h"
#include "dir.h"

typedef struct {

    FILE* fichierTxt;
    FILE* fichierTxtWrite;
    FILE* autoTxt;
    FILE* autoTxtWrite;
    int nb_sauvegardes;
    char nom_sauvegardes[10][260];
    DIR* directory;
    char* sauvegardes_time[10];

} Loader_t;



typedef struct GameplayScreen_t {
    ScreenInfo_t screen_info;
    /// La simulation
    SimWorld_t* world;
    /// Les textures pour le dessin de l'IU.
    UIState state;
    /// Les textures pour le dessin de la carte.
    SpriteSheet_t spriteSheet;
    /// Position de la souris sur la carte.
    Vector2I mousePos;
    /// Temps écoulé depuis la dernière seconde.
    float elapsedTime;
    /// Les fichiers pour le chargement de la carte.
    Loader_t loader;

    /// Débogage
    int dbgDisplayChateauNeighbors;
    int dbgDisplayCentraleNeighbors;
} GameplayScreen_t;

/// Crée un écran de gameplay prêt à être utilisé.
GameplayScreen_t* gameplay_create_screen();

void gameplay_on_enter(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_on_exit(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_update(Jeu_t* jeu, GameplayScreen_t *gameplay);

void gameplay_draw(Jeu_t* jeu, GameplayScreen_t *gameplay);


#endif //ECECITY_GAMEPLAY_H
