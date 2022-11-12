#include "bfs.h"
#include "placement.h"

void bfs_debug_struct_dans_fonction(GameplayScreen_t *gameplay) {

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

void bfs_debug_struct_gameplay(GameplayScreen_t *gameplay) {

    gameplay->bfs.tab_chateaux = malloc(sizeof(ChateauEau_t) * gameplay->world->chateaux->taille);

    struct Maillon_t *parcours = gameplay->world->chateaux->premier;
    int i = 0;

    while (parcours != NULL) {
        gameplay->bfs.tab_chateaux[i].position = ((ChateauEau_t *) parcours->data)->position;
        gameplay->bfs.tab_chateaux[i].orientation = ((ChateauEau_t *) parcours->data)->orientation;
        i++;
        parcours = parcours->next;
    }


    for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
        gameplay->bfs.tab_chateaux[j].nb_routes_adjacentes = get_nb_routes_adj_batiment(gameplay,
                                                                                        gameplay->bfs.tab_chateaux[j].position,
                                                                                        gameplay->bfs.tab_chateaux[j].orientation);
    }

    for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
        for (int k = 0; k < gameplay->bfs.tab_chateaux[j].nb_routes_adjacentes; k++) {
            get_routes_adj_batiment(gameplay, gameplay->bfs.tab_chateaux[j].position,
                                    gameplay->bfs.tab_chateaux[j].orientation,
                                    gameplay->bfs.tab_chateaux[j].routes_adjacentes);
        }
    }

    gameplay->bfs.tab_habitations = malloc(sizeof(Habitation_t) * gameplay->world->habitations->taille);

    struct Maillon_t *parcours2 = gameplay->world->habitations->premier;
    int z = 0;

    while (parcours2 != NULL) {
        gameplay->bfs.tab_habitations[z].position = ((Habitation_t *) parcours2->data)->position;
        gameplay->bfs.tab_habitations[z].orientation = ((Habitation_t *) parcours2->data)->orientation;
        gameplay->bfs.tab_habitations[z].distance_chateau_eau = malloc(sizeof(int) * gameplay->world->chateaux->taille);
        gameplay->bfs.tab_habitations[z].position_chateau_eau = malloc(
                sizeof(Vector2) * gameplay->world->chateaux->taille);
        for (int u = 0; u < gameplay->world->chateaux->taille; u++) {
            gameplay->bfs.tab_habitations[z].distance_chateau_eau[u] = 1000;
        }
        z++;
        parcours2 = parcours2->next;
    }

    for (int j = 0; j < gameplay->world->habitations->taille; j++) {
        gameplay->bfs.tab_habitations[j].nb_routes_adjacentes = get_nb_routes_adj_batiment(gameplay,
                                                                                           gameplay->bfs.tab_habitations[j].position,
                                                                                           gameplay->bfs.tab_habitations[j].orientation);

    }

    for (int j = 0; j < gameplay->world->habitations->taille; j++) {
        for (int k = 0; k < gameplay->bfs.tab_habitations[j].nb_routes_adjacentes; k++) {
            get_routes_adj_batiment(gameplay, gameplay->bfs.tab_habitations[j].position,
                                    gameplay->bfs.tab_habitations[j].orientation,
                                    gameplay->bfs.tab_habitations[j].routes_adjacentes);
        }
    }

    for (int j = 0; j < SIM_MAP_HAUTEUR; ++j) {
        for (int k = 0; k < SIM_MAP_LARGEUR; ++k) {
            if (gameplay->world->map[j][k].type == KIND_ROUTE) {
                gameplay->bfs.matrice[j][k].route = 1;
            } else {
                gameplay->bfs.matrice[j][k].route = 0;
            }
            gameplay->bfs.matrice[j][k].decouverte = 0;
            gameplay->bfs.matrice[j][k].predecesseur = (Vector2) {-1, -1};
        }
    }

    for (int l = 0; l < gameplay->world->chateaux->taille; l++) {
        for (int n = 0; n < gameplay->bfs.tab_chateaux[l].nb_routes_adjacentes; n++) {
            for (int j = 0; j < gameplay->world->habitations->taille; j++) {
                for (int k = 0; k < gameplay->bfs.tab_habitations[j].nb_routes_adjacentes; k++) {
                    /// Route sur laquelle on fait le parcours en largeur
                    Vector2 depart = gameplay->bfs.tab_habitations[j].routes_adjacentes[k];

                    /// On créé une file vide
                    File file = fileVide();

                    /// On enfile la première route
                    enfiler(file, depart);

                    /// Variable qui sert à défiler
                    Vector2 m;

                    /// Variable qui sert à savoir si une route a déjà un prédecesseur ou non
                    Vector2 comparateur = {-1, -1};

                    /// Tant que la file n'est pas vide
                    while (longueur(file)) {

                        /// On défile la dernière route enfilée
                        m = defilement(file);

                        /// Si cette route n'a pas été découverte
                        if (gameplay->bfs.matrice[(int) m.y][(int) m.x].decouverte == 0) {
                            /// Si il y a une route non découverte à l'est
                            if (gameplay->bfs.matrice[(int) m.y][(int) m.x + 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y][(int) m.x + 1].decouverte == 0) {
                                Vector2 temp = m;
                                temp.x = temp.x + 1;
                                /// On enfile la route à l'est
                                enfiler(file, temp);
                                /// Si cette route n'a pas de prédécesseur
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    /// Son prédecesseur est la route défilée
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte à l'ouest
                            if (gameplay->bfs.matrice[(int) m.y][(int) m.x - 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y][(int) m.x - 1].decouverte == 0) {
                                Vector2 temp = m;
                                temp.x = temp.x - 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte au sud
                            if (gameplay->bfs.matrice[(int) m.y + 1][(int) m.x].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y + 1][(int) m.x].decouverte == 0) {
                                Vector2 temp = m;
                                temp.y = temp.y + 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte au nord
                            if (gameplay->bfs.matrice[(int) m.y - 1][(int) m.x + 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y - 1][(int) m.x].decouverte == 0) {
                                Vector2 temp = m;
                                temp.y = temp.y - 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }

                            /// La route défilée est désormais découverte
                            gameplay->bfs.matrice[(int) m.y][(int) m.x].decouverte = 1;

                        }
                    }


                    /// On vient de parcourir tout le réseau de route depuis une route adjacente à une habitation
                    /// On va désormais calculer la distance qu'il faut pour aller depuis cette route vers les centrales.

                    Vector2 tabRoute[100];
                    int distance = 0;


                    Vector2 predecesseur = gameplay->bfs.tab_chateaux[l].routes_adjacentes[n];
                    printf("arrivee : (%d,%d)\n", (int) predecesseur.x, (int) predecesseur.y);
                    tabRoute[distance] = predecesseur;
                    distance++;

                    bool conditionFin = false;

                    while ((predecesseur.x != depart.x || predecesseur.y != depart.y) && !conditionFin) {
                        if (predecesseur.x == -1 && predecesseur.y == -1) {
                            /// Il n'existe pas de chemin qui relient ces deux routes
                            conditionFin = true;
                        }
                        /// On passe au prédecesseur suivant
                        predecesseur = gameplay->bfs.matrice[(int) predecesseur.y][(int) predecesseur.x].predecesseur;
                        tabRoute[distance] = predecesseur;
                        /// On augmente la distance de 1
                        distance++;
                        printf("(%d,%d)\n", (int) predecesseur.x, (int) predecesseur.y);

                    }

                    printf("Distance : %d VS %d\n", distance, gameplay->bfs.tab_habitations[j].distance_chateau_eau[l]);

                    /// Si un chemin existe
                    if (!conditionFin) {
                        /// Si distance est intéressante cad qu'elle est inférieure à la distance déjà enregistrée
                        if (distance < gameplay->bfs.tab_habitations[j].distance_chateau_eau[l]) {
                            gameplay->bfs.tab_habitations[j].distance_chateau_eau[l] = distance;
                            gameplay->bfs.tab_habitations[j].position_chateau_eau[l] = gameplay->bfs.tab_chateaux[l].position;
                        }


                    }

                    for (int b = 0; b < SIM_MAP_HAUTEUR; ++b) {
                        for (int a = 0; a < SIM_MAP_LARGEUR; ++a) {
                            if (gameplay->world->map[b][a].type == KIND_ROUTE) {
                                gameplay->bfs.matrice[b][a].route = 1;
                            } else {
                                gameplay->bfs.matrice[b][a].route = 0;
                            }
                            gameplay->bfs.matrice[b][a].decouverte = 0;
                            gameplay->bfs.matrice[b][a].predecesseur = (Vector2) {-1, -1};
                        }
                    }
                }
            }
        }
    }


    for (int k = 0; k < gameplay->world->chateaux->taille; k++) {
        for (int j = 0; j < gameplay->world->habitations->taille; j++) {
            printf("Habitation %d (%f,%f) distance vers Chateau (%f, %f) = %d\n", j,
                   gameplay->bfs.tab_habitations[j].position.x, gameplay->bfs.tab_habitations[j].position.y,
                   gameplay->bfs.tab_habitations[j].position_chateau_eau[k].x,
                   gameplay->bfs.tab_habitations[j].position_chateau_eau[k].y,
                   gameplay->bfs.tab_habitations[j].distance_chateau_eau[k]);
        }
    }
}

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

void bfs(GameplayScreen_t *gameplay) {

    gameplay->bfs.tab_chateaux = malloc(sizeof(ChateauEau_t) * gameplay->world->chateaux->taille);

    struct Maillon_t *parcours = gameplay->world->chateaux->premier;
    int i = 0;

    while (parcours != NULL) {
        gameplay->bfs.tab_chateaux[i].position = ((ChateauEau_t *) parcours->data)->position;
        gameplay->bfs.tab_chateaux[i].orientation = ((ChateauEau_t *) parcours->data)->orientation;
        i++;
        parcours = parcours->next;
    }


    for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
        gameplay->bfs.tab_chateaux[j].nb_routes_adjacentes = get_nb_routes_adj_batiment(gameplay,
                                                                                        gameplay->bfs.tab_chateaux[j].position,
                                                                                        gameplay->bfs.tab_chateaux[j].orientation);
    }

    for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
        for (int k = 0; k < gameplay->bfs.tab_chateaux[j].nb_routes_adjacentes; k++) {
            get_routes_adj_batiment(gameplay, gameplay->bfs.tab_chateaux[j].position,
                                    gameplay->bfs.tab_chateaux[j].orientation,
                                    gameplay->bfs.tab_chateaux[j].routes_adjacentes);
        }
    }

    gameplay->bfs.tab_centrales = malloc(sizeof(CentraleElectrique_t) * gameplay->world->chateaux->taille);

    struct Maillon_t *parcours3 = gameplay->world->chateaux->premier;
    int y = 0;

    while (parcours3 != NULL) {
        gameplay->bfs.tab_centrales[y].position = ((ChateauEau_t *) parcours3->data)->position;
        gameplay->bfs.tab_centrales[y].orientation = ((ChateauEau_t *) parcours3->data)->orientation;
        y++;
        parcours3 = parcours3->next;
    }


    for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
        gameplay->bfs.tab_centrales[j].nb_routes_adjacentes = get_nb_routes_adj_batiment(gameplay,
                                                                                        gameplay->bfs.tab_centrales[j].position,
                                                                                        gameplay->bfs.tab_centrales[j].orientation);
    }

    for (int j = 0; j < gameplay->world->chateaux->taille; j++) {
        for (int k = 0; k < gameplay->bfs.tab_centrales[j].nb_routes_adjacentes; k++) {
            get_routes_adj_batiment(gameplay, gameplay->bfs.tab_centrales[j].position,
                                    gameplay->bfs.tab_centrales[j].orientation,
                                    gameplay->bfs.tab_centrales[j].routes_adjacentes);
        }
    }

    gameplay->bfs.tab_habitations = malloc(sizeof(Habitation_t) * gameplay->world->habitations->taille);

    struct Maillon_t *parcours2 = gameplay->world->habitations->premier;
    int z = 0;

    while (parcours2 != NULL) {
        gameplay->bfs.tab_habitations[z].position = ((Habitation_t *) parcours2->data)->position;
        gameplay->bfs.tab_habitations[z].orientation = ((Habitation_t *) parcours2->data)->orientation;
        gameplay->bfs.tab_habitations[z].connexion_reseau_electrique = false;
        gameplay->bfs.tab_habitations[z].distance_chateau_eau = malloc(sizeof(int) * gameplay->world->chateaux->taille);
        gameplay->bfs.tab_habitations[z].position_chateau_eau = malloc(
                sizeof(Vector2) * gameplay->world->chateaux->taille);
        for (int u = 0; u < gameplay->world->chateaux->taille; u++) {
            gameplay->bfs.tab_habitations[z].distance_chateau_eau[u] = 1000;
        }
        z++;
        parcours2 = parcours2->next;
    }

    for (int j = 0; j < gameplay->world->habitations->taille; j++) {
        gameplay->bfs.tab_habitations[j].nb_routes_adjacentes = get_nb_routes_adj_batiment(gameplay,
                                                                                           gameplay->bfs.tab_habitations[j].position,
                                                                                           gameplay->bfs.tab_habitations[j].orientation);

    }

    for (int j = 0; j < gameplay->world->habitations->taille; j++) {
        for (int k = 0; k < gameplay->bfs.tab_habitations[j].nb_routes_adjacentes; k++) {
            get_routes_adj_batiment(gameplay, gameplay->bfs.tab_habitations[j].position,
                                    gameplay->bfs.tab_habitations[j].orientation,
                                    gameplay->bfs.tab_habitations[j].routes_adjacentes);
        }
    }

    for (int j = 0; j < SIM_MAP_HAUTEUR; ++j) {
        for (int k = 0; k < SIM_MAP_LARGEUR; ++k) {
            if (gameplay->world->map[j][k].type == KIND_ROUTE) {
                gameplay->bfs.matrice[j][k].route = 1;
            } else {
                gameplay->bfs.matrice[j][k].route = 0;
            }
            gameplay->bfs.matrice[j][k].decouverte = 0;
            gameplay->bfs.matrice[j][k].predecesseur = (Vector2) {-1, -1};
        }
    }

    for (int l = 0; l < gameplay->world->chateaux->taille; l++) {
        for (int n = 0; n < gameplay->bfs.tab_chateaux[l].nb_routes_adjacentes; n++) {
            for (int j = 0; j < gameplay->world->habitations->taille; j++) {
                for (int k = 0; k < gameplay->bfs.tab_habitations[j].nb_routes_adjacentes; k++) {
                    /// Route sur laquelle on fait le parcours en largeur
                    Vector2 depart = gameplay->bfs.tab_habitations[j].routes_adjacentes[k];

                    /// On créé une file vide
                    File file = fileVide();

                    /// On enfile la première route
                    enfiler(file, depart);

                    /// Variable qui sert à défiler
                    Vector2 m;

                    /// Variable qui sert à savoir si une route a déjà un prédecesseur ou non
                    Vector2 comparateur = {-1, -1};

                    /// Tant que la file n'est pas vide
                    while (longueur(file)) {

                        /// On défile la dernière route enfilée
                        m = defilement(file);

                        /// Si cette route n'a pas été découverte
                        if (gameplay->bfs.matrice[(int) m.y][(int) m.x].decouverte == 0) {
                            /// Si il y a une route non découverte à l'est
                            if (gameplay->bfs.matrice[(int) m.y][(int) m.x + 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y][(int) m.x + 1].decouverte == 0) {
                                Vector2 temp = m;
                                temp.x = temp.x + 1;
                                /// On enfile la route à l'est
                                enfiler(file, temp);
                                /// Si cette route n'a pas de prédécesseur
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    /// Son prédecesseur est la route défilée
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte à l'ouest
                            if (gameplay->bfs.matrice[(int) m.y][(int) m.x - 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y][(int) m.x - 1].decouverte == 0) {
                                Vector2 temp = m;
                                temp.x = temp.x - 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte au sud
                            if (gameplay->bfs.matrice[(int) m.y + 1][(int) m.x].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y + 1][(int) m.x].decouverte == 0) {
                                Vector2 temp = m;
                                temp.y = temp.y + 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte au nord
                            if (gameplay->bfs.matrice[(int) m.y - 1][(int) m.x + 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y - 1][(int) m.x].decouverte == 0) {
                                Vector2 temp = m;
                                temp.y = temp.y - 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }

                            /// La route défilée est désormais découverte
                            gameplay->bfs.matrice[(int) m.y][(int) m.x].decouverte = 1;

                        }
                    }


                    /// On vient de parcourir tout le réseau de route depuis une route adjacente à une habitation
                    /// On va désormais calculer la distance qu'il faut pour aller depuis cette route vers les centrales.

                    Vector2 tabRoute[100];
                    int distance = 0;


                    Vector2 predecesseur = gameplay->bfs.tab_chateaux[l].routes_adjacentes[n];
                    tabRoute[distance] = predecesseur;
                    distance++;

                    bool conditionFin = false;

                    while ((predecesseur.x != depart.x || predecesseur.y != depart.y) && !conditionFin) {
                        if (predecesseur.x == -1 && predecesseur.y == -1) {
                            /// Il n'existe pas de chemin qui relient ces deux routes
                            conditionFin = true;
                        }
                        /// On passe au prédecesseur suivant
                        predecesseur = gameplay->bfs.matrice[(int) predecesseur.y][(int) predecesseur.x].predecesseur;
                        tabRoute[distance] = predecesseur;
                        /// On augmente la distance de 1
                        distance++;
                    }


                    /// Si un chemin existe
                    if (!conditionFin) {
                        /// Si distance est intéressante cad qu'elle est inférieure à la distance déjà enregistrée
                        if (distance < gameplay->bfs.tab_habitations[j].distance_chateau_eau[l]) {
                            gameplay->bfs.tab_habitations[j].distance_chateau_eau[l] = distance;
                            gameplay->bfs.tab_habitations[j].position_chateau_eau[l] = gameplay->bfs.tab_chateaux[l].position;
                        }


                    }

                    for (int b = 0; b < SIM_MAP_HAUTEUR; ++b) {
                        for (int a = 0; a < SIM_MAP_LARGEUR; ++a) {
                            if (gameplay->world->map[b][a].type == KIND_ROUTE) {
                                gameplay->bfs.matrice[b][a].route = 1;
                            } else {
                                gameplay->bfs.matrice[b][a].route = 0;
                            }
                            gameplay->bfs.matrice[b][a].decouverte = 0;
                            gameplay->bfs.matrice[b][a].predecesseur = (Vector2) {-1, -1};
                        }
                    }
                }
            }
        }
    }

    for (int l = 0; l < gameplay->world->centrales->taille; l++) {
        for (int n = 0; n < gameplay->bfs.tab_centrales->nb_routes_adjacentes; n++) {
            for (int j = 0; j < gameplay->world->habitations->taille; j++) {
                for (int k = 0; k < gameplay->bfs.tab_habitations[j].nb_routes_adjacentes; k++) {
                    /// Route sur laquelle on fait le parcours en largeur
                    Vector2 depart = gameplay->bfs.tab_habitations[j].routes_adjacentes[k];

                    /// On créé une file vide
                    File file = fileVide();

                    /// On enfile la première route
                    enfiler(file, depart);

                    /// Variable qui sert à défiler
                    Vector2 m;

                    /// Variable qui sert à savoir si une route a déjà un prédecesseur ou non
                    Vector2 comparateur = {-1, -1};

                    /// Tant que la file n'est pas vide
                    while (longueur(file)) {

                        /// On défile la dernière route enfilée
                        m = defilement(file);

                        /// Si cette route n'a pas été découverte
                        if (gameplay->bfs.matrice[(int) m.y][(int) m.x].decouverte == 0) {
                            /// Si il y a une route non découverte à l'est
                            if (gameplay->bfs.matrice[(int) m.y][(int) m.x + 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y][(int) m.x + 1].decouverte == 0) {
                                Vector2 temp = m;
                                temp.x = temp.x + 1;
                                /// On enfile la route à l'est
                                enfiler(file, temp);
                                /// Si cette route n'a pas de prédécesseur
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    /// Son prédecesseur est la route défilée
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte à l'ouest
                            if (gameplay->bfs.matrice[(int) m.y][(int) m.x - 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y][(int) m.x - 1].decouverte == 0) {
                                Vector2 temp = m;
                                temp.x = temp.x - 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte au sud
                            if (gameplay->bfs.matrice[(int) m.y + 1][(int) m.x].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y + 1][(int) m.x].decouverte == 0) {
                                Vector2 temp = m;
                                temp.y = temp.y + 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }
                            /// Si il y a une route non découverte au nord
                            if (gameplay->bfs.matrice[(int) m.y - 1][(int) m.x + 1].route == 1 &&
                                gameplay->bfs.matrice[(int) m.y - 1][(int) m.x].decouverte == 0) {
                                Vector2 temp = m;
                                temp.y = temp.y - 1;
                                enfiler(file, temp);
                                if (comparateur.x == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.x &&
                                    comparateur.y == gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur.y) {
                                    gameplay->bfs.matrice[(int) temp.y][(int) temp.x].predecesseur = m;
                                }
                            }

                            /// La route défilée est désormais découverte
                            gameplay->bfs.matrice[(int) m.y][(int) m.x].decouverte = 1;

                        }
                    }


                    /// On vient de parcourir tout le réseau de route depuis une route adjacente à une habitation
                    /// On va désormais calculer la distance qu'il faut pour aller depuis cette route vers les centrales.

                    Vector2 tabRoute[100];
                    int distance = 0;


                    Vector2 predecesseur = gameplay->bfs.tab_chateaux[l].routes_adjacentes[n];
                    tabRoute[distance] = predecesseur;
                    distance++;

                    bool conditionFin = false;

                    while ((predecesseur.x != depart.x || predecesseur.y != depart.y) && !conditionFin) {
                        if (predecesseur.x == -1 && predecesseur.y == -1) {
                            /// Il n'existe pas de chemin qui relient ces deux routes
                            conditionFin = true;
                        }
                        /// On passe au prédecesseur suivant
                        predecesseur = gameplay->bfs.matrice[(int) predecesseur.y][(int) predecesseur.x].predecesseur;
                        tabRoute[distance] = predecesseur;
                        /// On augmente la distance de 1
                        distance++;
                    }


                    /// Si un chemin existe
                    if (!conditionFin) {
                        gameplay->bfs.tab_habitations[j].connexion_reseau_electrique = true;
                    }

                    for (int b = 0; b < SIM_MAP_HAUTEUR; ++b) {
                        for (int a = 0; a < SIM_MAP_LARGEUR; ++a) {
                            if (gameplay->world->map[b][a].type == KIND_ROUTE) {
                                gameplay->bfs.matrice[b][a].route = 1;
                            } else {
                                gameplay->bfs.matrice[b][a].route = 0;
                            }
                            gameplay->bfs.matrice[b][a].decouverte = 0;
                            gameplay->bfs.matrice[b][a].predecesseur = (Vector2) {-1, -1};
                        }
                    }
                }
            }
        }
    }
}

void update_liste_bfs(GameplayScreen_t* gameplay){
    struct Maillon_t* parcours = gameplay->world->habitations->premier;

    while (parcours != NULL){
        for (int i = 0; i < gameplay->world->habitations->taille; i++) {
            if(gameplay->bfs.tab_habitations[i].position.x == ((Habitation_t*) parcours->data)->position.x && gameplay->bfs.tab_habitations[i].position.y == ((Habitation_t*) parcours->data)->position.y){
                ((Habitation_t *) parcours->data)->distance_chateau_eau = gameplay->bfs.tab_habitations[i].distance_chateau_eau;
                ((Habitation_t *) parcours->data)->position_chateau_eau = gameplay->bfs.tab_habitations[i].position_chateau_eau;
                ((Habitation_t *) parcours->data)->connexion_reseau_electrique = gameplay->bfs.tab_habitations[i].connexion_reseau_electrique;
            }
        }

        parcours = parcours->next;
    }
}