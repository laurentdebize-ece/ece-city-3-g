#ifndef ECECITY_BFS_H
#define ECECITY_BFS_H

#include <stdbool.h>
#include "raylib.h"
#include "sim/sim.h"
#include "screens/gameplay.h"

typedef int typage;

struct cellule {
    Vector2 position;
    struct cellule *suivant;
};

typedef struct cellule* Cellule;

struct file {
    int longueur;
    Cellule tete;
    Cellule queue;
};

typedef struct file* File;


File fileVide();
int longueur(File F);
void enfiler(File F, Vector2 element);
Vector2 defilement(File F);

void bfs(GameplayScreen_t* gameplay);
int get_nb_routes_adj_batiment(GameplayScreen_t* gameplay, Vector2 position, Orientation_t orientation);
void get_routes_adj_batiment(GameplayScreen_t* gameplay, Vector2 position, Orientation_t orientation, Vector2* routes);

#endif
