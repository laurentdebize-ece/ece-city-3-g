#include "bfs.h"

File fileVide() {
    File F;
    //On alloue dynamiquement la liste
    F = (File) malloc(sizeof(struct file));
    if (F == NULL) printf("erreur allocation fileVide");
    //La liste est vide donc de longueur 0
    F->longueur = 0;
    //La liste est vide donc ne contient aucune cellule
    F->tete = F->queue = NULL;
    return (F);
}

int longueur(File F) {
    if (F == NULL)printf("file existe pas - longueur");
    return (F->longueur);
}

void enfiler(File F, Vector2 position) {
    Cellule cellule;
    if (F == NULL) printf("file existe pas - enfiler");

    //On alloue l'élément de la liste dynamiquement
    cellule = (Cellule) malloc(sizeof(struct cellule));
    //On vérifie l'allocation
    if (cellule == NULL) printf("erreur allocation memoire - enfiler");

    //On assigne à l'élément de la liste le numéro de sommet passé en paramètre
    cellule->position = position;
    //FIFO donc on va défiler par la tête donc on enfile en queue de liste soit le suivant = NULL
    cellule->suivant = NULL;
    //Si la liste est vide : Cellule = tête de liste et aussi queue de liste car 1 élement dans la liste
    if (longueur(F) == 0) {
        F->tete = F->queue = cellule;
    } else {
        //Sinon on part de la queue de la liste et on ajoute notre cellule
        F->queue->suivant = cellule;
        //On fait pointer la queue de la liste vers notre cellule
        F->queue = cellule;
    }
    //On augmente donc la taille de la liste de 1
    ++(F->longueur);
}

Vector2 defilement(File F) {
    Cellule cellule;
    Vector2 element;
    //La file n'existe pas
    if (F == NULL || longueur(F) == 0) printf("File existe pas - defilement");

    //On assigne une cellule temporaire à la cellule de tête de file
    cellule = F->tete;
    //On assigne au temporaire element le sommet de la cellule en tête de file
    element = cellule->position;

    //Si la file est de longueur 1
    if (longueur(F) == 1) {
        //On vide la file car l'objectif de cette fonction est d'enlever un élément de la liste
        //soit dans ce if de la mettre à 0
        F->tete = F->queue = NULL;
    } else {
        //Sinon on met l'élément de la file numéro 2 en tête de liste
        F->tete = F->tete->suivant;
    }
    //On libère l'ex-tête de liste
    free(cellule);
    //On réduit la longueur de la file
    --(F->longueur);
    //On retourne le sommet qui a été enlevé de la file
    return (element);
}

int get_nb_routes_adj_batiment(GameplayScreen_t *gameplay, Vector2 position, Orientation_t orientation) {

    int compteur = 0;
    int w = 0;
    int h = 0;

    if (orientation == ORIENTATION_4X6) {
        w = 4;
        h = 6;
    } else if (orientation == ORIENTATION_6X4) {
        w = 6;
        h = 4;
    } else if (orientation == ORIENTATION_NULL) {
        w = 3;
        h = 3;
    }

    for (int y = 0; y < h; y++) {
        if (gameplay->world->map[((int) position.y) + y][((int) position.x) - 1].type == KIND_ROUTE) {
            compteur++;
        }
        if (gameplay->world->map[((int) position.y) + y][((int) position.x) + w].type == KIND_ROUTE) {
            compteur++;
        }
    }

    for (int x = 0; x < w; x++) {
        if (gameplay->world->map[((int) position.y) - 1][((int) position.x) + x].type == KIND_ROUTE) {
            compteur++;
        }
        if (gameplay->world->map[((int) position.y) + h][((int) position.x) + x].type == KIND_ROUTE) {
            compteur++;
        }
    }

    return compteur;
}

void get_routes_adj_batiment(GameplayScreen_t *gameplay, Vector2 position, Orientation_t orientation, Vector2 *routes) {
    int compteur = 0;
    int w = 0;
    int h = 0;
    int nbRoutes = 0;

    if (orientation == ORIENTATION_4X6) {
        w = 4;
        h = 6;
    } else if (orientation == ORIENTATION_6X4) {
        w = 6;
        h = 4;
    } else if (orientation == ORIENTATION_NULL) {
        w = 3;
        h = 3;
    }

    for (int y = 0; y < h; y++) {
        if (gameplay->world->map[(int) position.y + y][(int) position.x - 1].type == KIND_ROUTE) {
            routes[nbRoutes] = (Vector2) {position.x - 1, position.y + y};
            nbRoutes++;
        }
        if (gameplay->world->map[(int) position.y + y][(int) position.x + w].type == KIND_ROUTE) {
            routes[nbRoutes] = (Vector2) {position.x + w, position.y + y};
            nbRoutes++;
        }
    }

    for (int x = 0; x < w; x++) {
        if (gameplay->world->map[(int) position.y - 1][(int) position.x + x].type == KIND_ROUTE) {
            routes[nbRoutes] = (Vector2) {position.x + x, position.y - 1};
            nbRoutes++;
        }
        if (gameplay->world->map[(int) position.y + h][(int) position.x + x].type == KIND_ROUTE) {
            routes[nbRoutes] = (Vector2) {position.x + x, position.y + h};
            nbRoutes++;
        }
    }
}


void bfs(GameplayScreen_t *gameplay) {

    struct Chateau {
        Vector2 position;
        Orientation_t orientation;
        int nb_routes_adjacentes;
        Vector2 routes_adjacentes[20];
    };

    struct Chateau *tab_chateaux = malloc(sizeof(struct Chateau) * gameplay->world->chateaux->taille);

    if (tab_chateaux != NULL) {
        printf("Chateaux alloc, taille = %d\n", gameplay->world->chateaux->taille);
    }

    struct Maillon_t *parcours = gameplay->world->chateaux->premier;
    int i = 0;

    while (parcours != NULL) {
        tab_chateaux[i].position = ((ChateauEau_t *) parcours->data)->position;
        //tab_chateaux[i].orientation = ((ChateauEau_t*) parcours->data)->orientation;
        tab_chateaux[i].orientation = 0;
        i++;
        parcours = parcours->next;
    }

    for (int j = 0; j < gameplay->world->chateaux->taille; ++j) {
        printf("(%2.f, %2.f) orientation : %d\n", tab_chateaux[j].position.x, tab_chateaux[j].position.y,
               tab_chateaux[j].orientation);
    }

    for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
        tab_chateaux[j].nb_routes_adjacentes = get_nb_routes_adj_batiment(gameplay, tab_chateaux[j].position,
                                                                          tab_chateaux[j].orientation);
        printf("chateau : %d, %d routes adj\n", j, tab_chateaux[j].nb_routes_adjacentes);
    }

    for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
        for (int k = 0; k < tab_chateaux[j].nb_routes_adjacentes; k++) {
            get_routes_adj_batiment(gameplay, tab_chateaux[j].position, tab_chateaux[j].orientation,
                                    tab_chateaux[j].routes_adjacentes);
            printf("Chateau %d \n route adj %d : (%f,%f)\n\n", j, k, tab_chateaux[j].routes_adjacentes[k].x,
                   tab_chateaux[j].routes_adjacentes[k].y);
        }
    }

    struct Habitation {
        Vector2 position;
        int nb_routes_adjacentes;
        Vector2 routes_adjacentes[20];
    };

    struct Habitation *tab_habitation = malloc(sizeof(struct Habitation) * gameplay->world->habitations->taille);
    printf("Habitation alloc, taille = %d\n", gameplay->world->habitations->taille);

    struct Maillon_t *parcours2 = gameplay->world->habitations->premier;
    int z = 0;

    while (parcours2 != NULL) {
        tab_habitation[z].position = ((Habitation_t *) parcours2->data)->position;
        z++;
        parcours2 = parcours2->next;
    }

    for (int j = 0; j < gameplay->world->habitations->taille; ++j) {
        printf("Habitation %d : (%2.f, %2.f)\n", j, tab_habitation[j].position.x, tab_habitation[j].position.y);
    }

    for (int j = 0; j < gameplay->world->habitations->taille; j++) {
        tab_habitation[j].nb_routes_adjacentes = get_nb_routes_adj_batiment(gameplay, tab_habitation[j].position,
                                                                            ORIENTATION_NULL);
        printf("Habitation : %d, %d routes adj\n", j, tab_habitation[j].nb_routes_adjacentes);

    }

    for (int j = 0; j < gameplay->world->habitations->taille; j++) {
        for (int k = 0; k < tab_habitation[j].nb_routes_adjacentes; k++) {
            get_routes_adj_batiment(gameplay, tab_habitation[j].position, ORIENTATION_NULL,
                                    tab_habitation[j].routes_adjacentes);
            printf("Habitation %d \n route adj %d : (%f,%f)\n\n", j, k, tab_habitation[j].routes_adjacentes[k].x,
                   tab_habitation[j].routes_adjacentes[k].y);
        }
    }


    typedef struct Matrice {
        int route;
        int decouverte;
        Vector2 predecesseur;
    } Matrice;

    Matrice matrice[SIM_MAP_HAUTEUR][SIM_MAP_LARGEUR];

    for (int j = 0; j < SIM_MAP_HAUTEUR; ++j) {
        for (int k = 0; k < SIM_MAP_LARGEUR; ++k) {
            if (gameplay->world->map[j][k].type == KIND_ROUTE) {
                matrice[j][k].route = 1;
            } else {
                matrice[j][k].route = 0;
            }
            matrice[j][k].decouverte = 0;
            matrice[j][k].predecesseur = (Vector2) {-1, -1};
        }
    }

    Vector2 depart = tab_habitation[0].routes_adjacentes[0];

    File file = fileVide();

    enfiler(file, depart);
    printf("Enfilement (%f, %f)\n", depart.x, depart.y);

    Vector2 m;

    Vector2 comparateur = {-1, -1};

    while (longueur(file)) {

        m = defilement(file);
        printf("Defilement (%f, %f)\n", m.x, m.y);

        if (matrice[(int) m.y][(int) m.x].decouverte == 0) {
            if (matrice[(int) m.y][(int) m.x + 1].route == 1 && matrice[(int) m.y][(int) m.x + 1].decouverte == 0) {
                printf("Route en x+1\n");
                Vector2 temp = m;
                temp.x = temp.x + 1;
                enfiler(file, temp);
                printf("Enfilement (%f, %f)\n", temp.x, temp.y);
                if (comparateur.x == matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                    comparateur.y == matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                    matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                }
            }
            if (matrice[(int) m.y][(int) m.x - 1].route == 1 && matrice[(int) m.y][(int) m.x - 1].decouverte == 0) {
                printf("Route en x-1\n");
                Vector2 temp = m;
                temp.x = temp.x - 1;
                enfiler(file, temp);
                printf("Enfilement (%f, %f)\n", temp.x, temp.y);
                if (comparateur.x == matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                    comparateur.y == matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                    matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                }
            }
            if (matrice[(int) m.y + 1][(int) m.x].route == 1 && matrice[(int) m.y + 1][(int) m.x].decouverte == 0) {
                printf("Route en y+1\n");
                Vector2 temp = m;
                temp.y = temp.y + 1;
                enfiler(file, temp);
                printf("Enfilement (%f, %f)\n", temp.x, temp.y);
                if (comparateur.x == matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                    comparateur.y == matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                    matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                }
            }
            if (matrice[(int) m.y - 1][(int) m.x + 1].route == 1 && matrice[(int) m.y - 1][(int) m.x].decouverte == 0) {
                printf("Route en y-1\n");
                Vector2 temp = m;
                temp.y = temp.y - 1;
                enfiler(file, temp);
                printf("Enfilement (%f, %f)\n", temp.x, temp.y);
                if (comparateur.x == matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                    comparateur.y == matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                    matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                }
            }

            matrice[(int) m.y][(int) m.x].decouverte = 1;

        }
    }


    Vector2 tabRoute[100];
    int distance = 0;

    Vector2 predecesseur = tab_chateaux[0].routes_adjacentes[0];
    tabRoute[distance] = predecesseur;
    distance++;
    printf("arrivee (%d,%d)\n", (int) predecesseur.x, (int) predecesseur.y);

    bool conditionFin = false;

    while ((predecesseur.x != depart.x || predecesseur.y != depart.y) && !conditionFin) {
        if (predecesseur.x == -1 && predecesseur.y == -1) {
            conditionFin = true;
        }
        predecesseur = matrice[(int) predecesseur.y][(int) predecesseur.x].predecesseur;
        tabRoute[distance] = predecesseur;
        distance++;
        printf("(%d,%d)\n", (int) predecesseur.x, (int) predecesseur.y);
    }

    if (conditionFin) {
        printf("Pas de chemin !\n");
    } else {
        printf("Distance : %d\n", distance);
    }


}