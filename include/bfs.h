#ifndef ECECITY_BFS_H
#define ECECITY_BFS_H

#include "utils/grille.h"
#include "utils/liste.h"
#include "sim/sim.h"
#include "utils/vector.h"

/// Représente une habitation identifiée lors du parcours en largeur.
typedef struct HabitationNode_t {
    int distance;
    Habitation_t* habitation;
} HabitationNode_t;

void bfs(SimWorld_t* world, Vector2I start, void* batId, Liste_t* resultats);

#endif //ECECITY_BFS_H
