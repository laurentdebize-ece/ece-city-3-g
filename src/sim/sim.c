
#include <stdio.h>
#include "sim/sim.h"
#include "bfs.h"
#include "sim/casernes.h"

void sim_reset_flow_distribution(SimWorld_t* world);
void sim_update_voisins_chateaux(SimWorld_t* world);
void sim_update_voisins_centrales(SimWorld_t* world);

/// Crée un monde de simulation vide.
SimWorld_t* sim_world_create(SimRules_t rules, int monnaie) {
    SimWorld_t* world = malloc(sizeof(SimWorld_t));
    world->habitations = liste_alloc();
    world->centrales = liste_alloc();
    world->chateaux = liste_alloc();
    world->routes = liste_alloc();
    world->casernes = liste_alloc();
    world->nb_total_habitants = 0;

    // mise à zéro de la carte.
    for (int i = 0; i < SIM_MAP_LARGEUR; i++) {
        for (int j = 0; j < SIM_MAP_HAUTEUR; j++) {
            world->map[i][j].donnees = NULL;
            world->map[i][j].type = KIND_VIDE;
            world->map[i][j].connexe = 0;
        }
    }

    world->monnaie = monnaie;
    world->rules = rules;
    world->n_ticks = 0;
    world->qte_totale_eau = 0;
    world->qte_totale_electricite = 0;
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
    world->nb_total_habitants = 0;
    sim_reset_flow_distribution(world);

    world->qte_totale_eau = 0;
    world->qte_totale_electricite = 0;


    /// évolution et récolte des impôts des habitations
    struct Maillon_t *maisons = world->habitations->premier;
    while (maisons) {
        Habitation_t *hab = (Habitation_t *) maisons->data;
        world->monnaie += habitation_step(hab, Communiste_t);
        world->nb_total_habitants += habitation_get_nb_habitants(hab);
        maisons = maisons->next;
    }

    /// maj des qte d'eau et d'électricité
    struct Maillon_t* chateaux = world->chateaux->premier;
    while (chateaux) {
        world->qte_totale_eau += ((ChateauEau_t*)chateaux->data)->capacite;
        chateaux = chateaux->next;
    }

    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        world->qte_totale_electricite += ((CentraleElectrique_t*)centrales->data)->capacite;
        centrales = centrales->next;
    }

    /// quatrième étape: sim des capacités d'évolution des bâtiments.
}

/// Remet à zéro la répartition de l'eau et de l'électricité pour les bâtiments.
void sim_reset_flow_distribution(SimWorld_t* world) {
    struct Maillon_t *maisons = world->habitations->premier;
    while (maisons) {
        Habitation_t *hab = (Habitation_t *) maisons->data;
        hab->eau = 0;
        hab->electricite = 0;
        maisons = maisons->next;
    }

    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        centrale_step((CentraleElectrique_t *) centrales->data, world->rules);
        centrales = centrales->next;
    }

    struct Maillon_t* chateau_eau = world->chateaux->premier;
    while (chateau_eau) {
        chateau_step((ChateauEau_t *) chateau_eau->data, world->rules);
        chateau_eau = chateau_eau->next;
    }
}

/// Place une entité dans la carte de la simulation aux coordonnées données.
void sim_place_entity(SimWorld_t* world, CaseKind_t type, int x, int y, bool reload) {
    switch (type) {
        case KIND_HABITATION:
        {
            Habitation_t* habitation = habitation_alloc(NIVEAU_TERRAIN_VAGUE);
            habitation->position = (Vector2I) {x, y};

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    world->map[x + i][y + j].type = KIND_HABITATION;
                    world->map[x + i][y + j].donnees = habitation;
                }
            }

            liste_ajout_tri(world->habitations, habitation, habitation_tri_par_distance);
        }
        break;

        case KIND_CENTRALE:
        {
            CentraleElectrique_t* centrale = centrale_alloc();
            centrale->position = (Vector2I) {x, y};
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 4; ++j) {
                    world->map[x + i][y + j].type = KIND_CENTRALE;
                    world->map[x + i][y + j].donnees = centrale;
                }
            }

            liste_ajouter_fin(world->centrales, centrale);
        }
        break;

        case KIND_CHATEAU: {
            ChateauEau_t* chateau = chateau_alloc();
            chateau->position = (Vector2I) {x, y};
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 6; ++j) {
                    world->map[x + i][y + j].type = KIND_CHATEAU;
                    world->map[x + i][y + j].donnees = chateau;
                }
            }

            liste_ajouter_fin(world->chateaux, chateau);
        }
        break;

        case KIND_CASERNE: {
            CasernePompier_t *casernes = alloc_caserne();
            casernes->position = (Vector2I) {x, y};
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    world->map[x + i][y + j].type = KIND_CASERNE;
                    world->map[x + i][y + j].donnees = casernes;
                }
            }
            liste_ajouter_fin(world->casernes, casernes);
            break;
        }


            case KIND_ROUTE: {
            world->map[x][y].type = KIND_ROUTE;
            world->map[x][y].donnees = NULL;
        }
        break;

        default:
            break;
    }

    if (reload)
        sim_update_voisins(world);
}

bool sim_check_can_place(SimWorld_t* world, bool isBat, int x, int y, int w, int h) {
    // Si le bâtiment dépasse du terrain, on ne peut pas le placer.
    if (x < 0 || y < 0 || x + w > SIM_MAP_LARGEUR || y + h > SIM_MAP_HAUTEUR)
        return false;

    // on vérifie d'abord que la surface de la grille ou l'on veut placer le bâtiment est vide.
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (world->map[x + i][y + j].type != KIND_VIDE)
                return false;
        }
    }

    if (isBat) {
        // on vérifie ensuite que les cases adjacentes sont vides.
        for (int i = 0; i < w; ++i) {
            if (world->map[x + i][y - 1].type == KIND_ROUTE || world->map[x + i][y + h].type == KIND_ROUTE)
                return true;
        }

        for (int i = 0; i < h; ++i) {
            if (world->map[x - 1][y + i].type == KIND_ROUTE || world->map[x + w][y + i].type == KIND_ROUTE)
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

    if (world->map[x][y].type != KIND_VIDE) {
        switch (world->map[x][y].type) {
            case KIND_HABITATION:
            {
                Habitation_t* habitation = (Habitation_t *) world->map[x][y].donnees;
                liste_supprimer(world->habitations, habitation);
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        world->map[habitation->position.x + i][habitation->position.y + j].type = KIND_VIDE;
                        world->map[habitation->position.x + i][habitation->position.y + j].donnees = NULL;
                    }
                }
                habitation_free(habitation);
            }
            break;

            case KIND_CENTRALE:
            {
                CentraleElectrique_t* centrale = (CentraleElectrique_t *) world->map[x][y].donnees;
                liste_supprimer(world->centrales, centrale);
                for (int i = 0; i < 6; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        world->map[centrale->position.x + i][centrale->position.y + j].type = KIND_VIDE;
                        world->map[centrale->position.x + i][centrale->position.y + j].donnees = NULL;
                    }
                }
                centrale_free(centrale);
            }
            break;

            case KIND_CHATEAU:
            {
                ChateauEau_t* chateau = (ChateauEau_t *) world->map[x][y].donnees;
                liste_supprimer(world->chateaux, chateau);
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        world->map[chateau->position.x + i][chateau->position.y + j].type = KIND_VIDE;
                        world->map[chateau->position.x + i][chateau->position.y + j].donnees = NULL;
                    }
                }
                chateau_free(chateau);
            }
            break;

            case KIND_CASERNE:
            {
                CasernePompier_t* caserne = (CasernePompier_t *) world->map[x][y].donnees;
                liste_supprimer(world->casernes, caserne);
                for (int i = 0; i < 6; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        world->map[caserne->position.x + i][caserne->position.y + j].type = KIND_VIDE;
                        world->map[caserne->position.x + i][caserne->position.y + j].donnees = NULL;
                    }
                }
                caserne_free(caserne);
            }
                break;

            case KIND_ROUTE: {
                world->map[x][y].type = KIND_VIDE;
                world->map[x][y].donnees = NULL;
            }
            break;

            default:
                break;
        }

        sim_update_voisins(world);
    }
}

void sim_update_voisins(SimWorld_t* world) {
    struct Maillon_t* habs = world->habitations->premier;
    while (habs) {
        ((Habitation_t*)habs->data)->alimentee_en_eau = false;
        ((Habitation_t*)habs->data)->alimentee_en_electricite = false;
        habs = habs->next;
    }

    for (int i = 0; i < SIM_MAP_LARGEUR; ++i) {
        for (int j = 0; j < SIM_MAP_HAUTEUR; ++j) {
            world->map[i][j].connexe = false;
        }
    }

    sim_update_voisins_chateaux(world);
    sim_update_voisins_centrales(world);
}

void sim_update_voisins_chateaux(SimWorld_t* world) {
    struct Maillon_t* chateaux = world->chateaux->premier;
    while (chateaux) {
        ChateauEau_t* chateau = chateaux->data;

        /// on vide la liste des chemins calculés.
        vector_free_clear(chateau->habitations);

        /// on fait le BFS depuis le point mentionné
        bfs(world, chateau->position, chateau, chateau->habitations);

        /// on ajoute les chemins
        for (int i = 0; i < chateau->habitations->taille; ++i) {
            HabitationNode_t* node = chateau->habitations->data[i];
            /// on marque que l'habitation est connectée au réseau éléctrique.
            node->habitation->alimentee_en_eau = true;
        }

        chateaux = chateaux->next;
    }
}

void sim_update_voisins_centrales(SimWorld_t* world) {
    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        CentraleElectrique_t* centrale = centrales->data;

        vector_free_clear(centrale->habitations);

        bfs(world, centrale->position, centrale, centrale->habitations);

        for (int i = 0; i < centrale->habitations->taille; ++i) {
            HabitationNode_t* node = centrale->habitations->data[i];
            node->habitation->alimentee_en_electricite = true;
        }

        centrales = centrales->next;
    }
}
