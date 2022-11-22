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

int trier_noeux_habitations_par_distance(HabitationNode_t* node, HabitationNode_t* node2);

int trier_noeux_habitations_par_niveau(HabitationNode_t* node, HabitationNode_t* node2);

void bfs(SimWorld_t* world, Vector2I start, void* batId, Vector_t* resultats);

#endif //ECECITY_BFS_H
