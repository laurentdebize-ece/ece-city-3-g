#include "sim/sim.h"
#include "screens/gameplay.h"

void sim_reset_flow_distribution(SimWorld_t* world);

/// Crée un monde de simulation vide.
SimWorld_t* sim_world_create(SimRules_t rules, int monnaie) {
    SimWorld_t* world = malloc(sizeof(SimWorld_t));
    world->habitations = liste_alloc();
    world->centrales = liste_alloc();
    world->chateaux = liste_alloc();
    world->routes = liste_alloc();

    // mise à zéro de la carte.
    for (int i = 0; i < SIM_MAP_HAUTEUR; i++) {
        for (int j = 0; j < SIM_MAP_LARGEUR; j++) {
            world->map[i][j].donnees = NULL;
            world->map[i][j].type = KIND_VIDE;
            world->map[i][j].discriminant = 0;
        }
    }

    world->monnaie = monnaie;
    world->rules = rules;
    world->n_ticks = 0;

    return world;
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


    struct Maillon_t *maisons = world->habitations->premier;
    while (maisons) {
        Habitation_t *hab = (Habitation_t *) maisons->data;
        habitation_step(hab, Communiste_t);
        maisons = maisons->next;
    }

    world->monnaie += 10000;

    /// seconde étape: répartition de la capacité d'eau pour les bâtiments (BFS + tri de l'ordre).
    /// troisième étape: répartition de l'électricité pour les bâtiments. (BFS + tri de l'ordre).
    /// quatrième étape: sim des capacités d'évolution des bâtiments.
}

/// Remet à zéro la répartition de l'eau et de l'électricité pour les bâtiments.
void sim_reset_flow_distribution(SimWorld_t* world) {
    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        centrale_step((CentraleElectrique_t *) centrales->data);
        centrales = centrales->next;
    }

    struct Maillon_t* chateau_eau = world->chateaux->premier;
    while (chateau_eau) {
        chateau_step((ChateauEau_t *) chateau_eau->data);
        chateau_eau = chateau_eau->next;
    }
}

/// Place une entité dans la carte de la simulation aux coordonnées données.
void sim_place_entity(SimWorld_t* world, CaseKind_t type, int x, int y) {
    switch (type) {
        case KIND_TERRAIN_VAGUE:
        {
            Habitation_t* habitation = habitation_alloc(NIVEAU_TERRAIN_VAGUE);
            habitation->position = (Vector2) {x, y};

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    world->map[y + j][x + i].type = KIND_TERRAIN_VAGUE;
                    world->map[y + j][x + i].donnees = habitation;
                }
            }

            liste_ajout_tri(world->habitations, habitation, habitation_tri_par_distance);
        }
        break;

        case KIND_CENTRALE:
        {
            CentraleElectrique_t* centrale = centrale_alloc();
            centrale->position = (Vector2) {x, y};
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 4; ++j) {
                    world->map[y + j][x + i].type = KIND_CENTRALE;
                    world->map[y + j][x + i].donnees = centrale;
                }
            }

            liste_ajouter_fin(world->centrales, centrale);
        }
        break;

        case KIND_CHATEAU: {
            ChateauEau_t* chateau = chateau_alloc();
            chateau->position = (Vector2) {x, y};
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 6; ++j) {
                    world->map[y + j][x + i].type = KIND_CHATEAU;
                    world->map[y + j][x + i].donnees = chateau;
                }
            }

            liste_ajouter_fin(world->chateaux, chateau);
        }
        break;

        case KIND_ROUTE: {
            world->map[y][x].type = KIND_ROUTE;
            world->map[y][x].donnees = NULL;
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
            if (world->map[y + i][x + j].type != KIND_VIDE)
                return false;
        }
    }

    if (isBat) {
        // on vérifie ensuite que les cases adjacentes sont vides.
        for (int i = 0; i < w; ++i) {
            if (world->map[y + i][x - 1].type == KIND_ROUTE || world->map[y + i][x + h].type == KIND_ROUTE)
                return true;
        }

        for (int i = 0; i < h; ++i) {
            if (world->map[y - 1][x + i].type == KIND_ROUTE || world->map[y + w][x + i].type == KIND_ROUTE)
                return true;
        }
    } else
        return true;

    return false;
}

/// Détruit l'entitée séléctionnée.
void sim_destroy_entity(SimWorld_t* world, int x, int y) {
    if (x >= SIM_MAP_LARGEUR || y >= SIM_MAP_HAUTEUR || x < 0 || y < 0)
        return;

    if (world->map[y][x].type != KIND_VIDE) {
        switch (world->map[y][x].type) {
            case KIND_HABITATION:
            {
                Habitation_t* habitation = (Habitation_t *) world->map[y][x].donnees;
                liste_supprimer(world->habitations, habitation);
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        world->map[(int) habitation->position.y + j][(int) habitation->position.x + i].type = KIND_VIDE;
                        world->map[(int) habitation->position.y + j][(int) habitation->position.x + i].donnees = NULL;
                    }
                }
                habitation_free(habitation);
            }
            break;

            case KIND_CENTRALE:
            {
                CentraleElectrique_t* centrale = (CentraleElectrique_t *) world->map[y][x].donnees;
                liste_supprimer(world->centrales, centrale);
                for (int i = 0; i < 6; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        world->map[(int)centrale->position.y + j][(int)centrale->position.x + i].type = KIND_VIDE;
                        world->map[(int)centrale->position.y + j][(int)centrale->position.x + i].donnees = NULL;
                    }
                }
                centrale_free(centrale);
            }
            break;

            case KIND_CHATEAU:
            {
                ChateauEau_t* chateau = (ChateauEau_t *) world->map[y][x].donnees;
                liste_supprimer(world->chateaux, chateau);
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        world->map[(int)chateau->position.y + j][(int)chateau->position.x + i].type = KIND_VIDE;
                        world->map[(int)chateau->position.y + j][(int)chateau->position.x + i].donnees = NULL;
                    }
                }
                chateau_free(chateau);
            }
            break;

            case KIND_ROUTE: {
                world->map[y][x].type = KIND_VIDE;
                world->map[y][x].donnees = NULL;
            }
            break;

            default:
                break;
        }
    }
}
