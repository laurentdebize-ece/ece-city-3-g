#ifndef ECECITY_BFS_H
#define ECECITY_BFS_H

#include <stdbool.h>
#include "raylib.h"
#include "sim/sim.h"
#include "screens/gameplay.h"

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
void update_liste_bfs(GameplayScreen_t* gameplay);
void update_liste_habitation_triee_par_chateau(GameplayScreen_t* gameplay);

#endif
