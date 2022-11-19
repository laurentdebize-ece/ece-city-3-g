#include "sim/sauvegarde.h"

struct bat_data {
    CaseKind_t type;
    int extra; // données supplémentaires
};

char hab2char(Habitation_t *hab) {
    switch (hab->niveau) {
        case NIVEAU_RUINE:
            return 'R';
        case NIVEAU_TERRAIN_VAGUE:
            return 'V';
        case NIVEAU_CABANE:
            return 'C';
        case NIVEAU_GRATTE_CIEL:
            return 'G';
        case NIVEAU_MAISON:
            return 'M';
        case NIVEAU_IMMEUBLE:
            return 'I';
    }
}

NiveauHabitation_t char2hab(char c) {
    switch (c) {
        case 'R':
            return NIVEAU_RUINE;
        case 'V':
            return NIVEAU_TERRAIN_VAGUE;
        case 'C':
            return NIVEAU_CABANE;
        case 'G':
            return NIVEAU_GRATTE_CIEL;
        case 'M':
            return NIVEAU_MAISON;
        case 'I':
            return NIVEAU_IMMEUBLE;
        default:
            break;
    }
}

/// Sauvegarde la partie dans un fichier.
void sim_sauvegarder(SimWorld_t *world, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "w");
    assert(fichier != NULL && "Impossible d'ouvrir le fichier de sauvegarde pour écriture.");
    for (int i = 0; i < SIM_MAP_HAUTEUR; ++i) {
        for (int j = 0; j < SIM_MAP_LARGEUR; ++j) {
            switch (world->map[j][i].type) {
                case KIND_VIDE:
                    fprintf(fichier, "0");
                    break;
                case KIND_ROUTE:
                    fprintf(fichier, "r");
                    break;
                case KIND_HABITATION: {
                    Habitation_t *hab = world->map[j][i].donnees;
                    fprintf(fichier, "%c", hab2char(hab));
                }
                    break;
                case KIND_CENTRALE:
                    fprintf(fichier, "J");
                    break;
                case KIND_CHATEAU:
                    fprintf(fichier, "W");
                    break;
                default:
                    break;
            }
        }
        fprintf(fichier, "\n");
    }
    /// monnaie
    fprintf(fichier, "%d\n", world->monnaie);
    /// temps ecoule
    fprintf(fichier, "%d\n", world->n_ticks);
    /// mode de jeu
    fprintf(fichier, "%d\n", world->rules);

    fflush(fichier);
    fclose(fichier);
}

/// Charge une partie depuis un fichier.
void sim_charger(SimWorld_t *world, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    assert(fichier != NULL && "Impossible d'ouvrir le fichier de sauvegarde pour lecture.");

    struct bat_data data[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR] = {0};

    /// on charge depuis le fichier texte les positions des batiments dans une matrice
    /// on écrit directement dans le monde les routes.
    for (int i = 0; i < SIM_MAP_HAUTEUR;) {
        for (int j = 0; j < SIM_MAP_LARGEUR;) {
            char cs = fgetc(fichier);
            switch (cs) {
                case '0':
                    world->map[j][i].type = KIND_VIDE;
                    ++j;
                    break;

                case 'r':
                    world->map[j][i].type = KIND_ROUTE;
                    ++j;
                    break;

                case 'J':
                    data[j][i].type = KIND_CENTRALE;
                    ++j;
                    break;

                case 'W':
                    data[j][i].type = KIND_CHATEAU;
                    ++j;
                    break;

                case 'R':
                case 'V':
                case 'C':
                case 'G':
                case 'M':
                case 'I': {
                    data[j][i].type = KIND_HABITATION;
                    data[j][i].extra = char2hab(cs);
                    ++j;
                }
                    break;

                default:
                    break;
            }
        }
        i++;
    }

    fscanf(fichier, "%d", &world->monnaie);
    fscanf(fichier, "%d", &world->n_ticks);
    fscanf(fichier, "%d", &world->rules);

    bool visited[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR] = {false};

    for (int i = 0; i < SIM_MAP_HAUTEUR; ++i) {
        for (int j = 0; j < SIM_MAP_LARGEUR; ++j) {
            if (!visited[j][i]) {
                switch (data[j][i].type) {
                    case KIND_HABITATION: {
                        for (int k = 0; k < 3; ++k) {
                            for (int l = 0; l < 3; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(world, KIND_HABITATION, j, i, false);
                        ((Habitation_t*)world->map[j][i].donnees)->niveau = data[j][i].extra;
                    }
                        break;
                    case KIND_CENTRALE: {
                        for (int k = 0; k < 6; ++k) {
                            for (int l = 0; l < 4; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(world, KIND_CENTRALE, j, i, false);
                    }
                        break;
                    case KIND_CHATEAU: {
                        for (int k = 0; k < 4; ++k) {
                            for (int l = 0; l < 6; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(world, KIND_CHATEAU, j, i, false);
                    }
                        break;

                    default:
                        break;
                }
            }
        }
    }

    sim_update_voisins(world);

    fclose(fichier);
}