
#include "sim/sim.h"
#include "sim/chateau.h"


void sim_reset_flow_distribution(SimWorld_t* world);

/// Crée un monde de simulation vide.
SimWorld_t* sim_world_create(SimRules_t rules, int monnaie) {
    SimWorld_t* world = malloc(sizeof(SimWorld_t));
    world->habitations = liste_alloc();
    world->centrales = liste_alloc();
    world->chateaux = liste_alloc();
    world->routes = liste_alloc();

    // mise à zéro de la carte.
    for (int i = 0; i < SIM_MAP_LARGEUR; i++) {
        for (int j = 0; j < SIM_MAP_HAUTEUR; j++) {
            world->map[i][j].donnees = NULL;
            world->map[i][j].type = Vide;
            world->map[i][j].discriminant = 0;
        }
    }

    world->monnaie = monnaie;
    world->rules = rules;
    world->n_ticks = 0;
}

/// Détruit un monde de simulation.
void sim_world_destroy(SimWorld_t* world) {
    liste_free(world->habitations);
    liste_free(world->centrales);
    liste_free(world->chateaux);
    free(world);
}

void sim_world_step(SimWorld_t* world) {
    world->n_ticks++;
    sim_reset_flow_distribution(world);
    /// seconde étape: répartition de la capacité d'eau pour les bâtiments (BFS + tri de l'ordre).
    /// troisième étape: répartition de l'électricité pour les bâtiments. (BFS + tri de l'ordre).
    /// quatrième étape: sim des capacités d'évolution des bâtiments.
}

/// Remet à zéro la répartition de l'eau et de l'électricité pour les bâtiments.
void sim_reset_flow_distribution(SimWorld_t* world) {
    struct Maillon_t* centrale_elec = world->centrales->premier;
    while (centrale_elec) {
        centrale_step((CentraleElectrique_t *) centrale_elec->data);
        centrale_elec = centrale_elec->data;
    }

    struct Maillon_t* chateau_eau = world->chateaux->premier;
    while (chateau_eau) {
        chateau_step((ChateauEau_t *) chateau_eau->data);
        chateau_eau = chateau_eau->data;
    }
}