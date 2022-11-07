
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

/// Place une entité dans la carte de la simulation aux coordonnées données.
void sim_place_entity(SimWorld_t* world, CaseKind_t type, int x, int y) {
    switch (type) {
        case Habitation:
        {
            Habitation_t* habitation = habitation_alloc(TERRAIN_VAGUE);
            habitation->position = (Vector2I) {x, y};

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    world->map[x + i][y + j].type = Habitation;
                    world->map[x + i][y + j].donnees = habitation;
                }
            }

            liste_ajouter_fin(world->habitations, habitation);
        }
        break;

        case CentraleE:
        {

        }
        break;

        case ChateauE: {

        }
        break;

        case Route: {
            Route_t* route = route_alloc();
            route->position = (Vector2I) {x, y};
            liste_ajouter_fin(world->routes, route);

            world->map[x][y].type = Route;
            world->map[x][y].donnees = route;
        }
        break;

        default:
            break;
    }
}

bool sim_check_can_place(SimWorld_t* world, bool isBat, int x, int y, int w, int h) {
    // Si le bâtiment dépasse du terrain, on ne peut pas le placer.
    if (x < 0 || y < 0 || x + w > SIM_MAP_LARGEUR || y + h > SIM_MAP_HAUTEUR)
        return false;

    // on vérifie d'abord que la surface de la grille ou l'on veut placer le bâtiment est vide.
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (world->map[x + i][y + j].type != Vide)
                return false;
        }
    }

    if (isBat) {
        // on vérifie ensuite que les cases adjacentes sont vides.
        for (int i = 0; i < w; ++i) {
            if (world->map[x + i][y - 1].type == Route || world->map[x + i][y + h].type == Route)
                return true;
        }

        for (int i = 0; i < h; ++i) {
            if (world->map[x - 1][y + i].type == Route || world->map[x + w][y + i].type == Route)
                return true;
        }
    } else
        return true;

    return false;
}