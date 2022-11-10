#ifndef ECECITY_BFS_H
#define ECECITY_BFS_H

#include <stdbool.h>
#include "raylib.h"
#include "sim/sim.h"

typedef struct CentraleElec_t {
    Vector2 position;
    bool type4X6;
    Liste_t habitations;

} CentraleElec_t;

typedef struct Test {
    CentraleElec_t tabCentraleElec[10];
    int nbCentraleElec;
} Parcours_BFS_t;

#endif
