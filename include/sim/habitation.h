
#ifndef ECECITY_HABITATION_H
#define ECECITY_HABITATION_H

#include <stdbool.h>
#include <stdlib.h>
#include "raylib.h"
#include "sim/chateau.h"

//#include "utils/grille.h"

typedef enum SimRules_t {
    Capitaliste_t,
    Communiste_t,
} SimRules_t;

#define N_TICKS_EVOLUTION 15
#define N_TICKS_REGRESSION 15
#define IMPOT_PAR_HABITANT 10

typedef enum NiveauHabitation_t {
    NIVEAU_TERRAIN_VAGUE = 0,
    NIVEAU_RUINE = NIVEAU_TERRAIN_VAGUE,
    NIVEAU_CABANE = 10,
    NIVEAU_MAISON = 50,
    NIVEAU_IMMEUBLE = 100,
    NIVEAU_GRATTE_CIEL = 1000
} NiveauHabitation_t;


/// Représente une habitation simulée.
typedef struct Habitation_t {
    /// Niveau de l'habitation.
    NiveauHabitation_t niveau;
    /// Flot d'eau disponible pour l'habitation (-1 si pas relié au réseau).
    int eau;
    /// Flot d'électricité disponible pour l'habitation (-1 si pas relié au réseau).
    int electricite;
    /// Compteur de ticks avant prochaine évolution.
    int ticks_evolution;
    /// Compteur de ticks avant prochaine régression.
    int ticks_regression;
    /// La position du bâtiment.
    Vector2 position;
    /// Orientation ici NULL car une habitation n'a pas d'orientation (3X3).
    Orientation_t orientation;
    /// Le nombre de routes adjacentes à l'habitation.
    int nb_routes_adjacentes;
    /// Positions des routes adjacentes à l'habitation.
    Vector2 routes_adjacentes[20];
    /// La distance vers le chateau d'eau le plus proche
    int* distance_chateau_eau;
    /// La position du chateau d'eau le plus proche
    Vector2* position_chateau_eau;
} Habitation_t;

/// Crée une habitation.
Habitation_t* habitation_alloc(NiveauHabitation_t niveau);

/// Détruit une habitation.
void habitation_free(Habitation_t* habitation);

/// Incrémente d'un tick la simulation d'un bâtiment.
void habitation_step(Habitation_t* habitation, SimRules_t rules);

/// Fait évoluer un bâtiment en fonction des ticks d'évolution / régression.
void habitation_evolve(Habitation_t* habitation);

/// Renvoie le nombre d'habitants dans l'habitation.
int habitation_get_nb_habitants(Habitation_t* habitation);

/// Renvoie la position sur la carte de l'habitation.
Vector2 get_habitation_position_cellule_iso_x_y(Habitation_t* habitation);


/// Compare deux habitations.
int habitation_cmp(Habitation_t* habitation1, Habitation_t* habitation2);

int habitation_tri_par_distance(Habitation_t* a, Habitation_t* b);

#endif //ECECITY_HABITATION_H
