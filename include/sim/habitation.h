
#ifndef ECECITY_HABITATION_H
#define ECECITY_HABITATION_H

#include <stdbool.h>
#include <stdlib.h>

#include "utils/grille.h"

typedef enum SimRules_t {
    Capitaliste_t,
    Communiste_t,
} SimRules_t;


#define HABITATION_PRIX_CONSTRUCTION 10000
#define N_TICKS_EVOLUTION 15
#define IMPOT_PAR_HABITANT 10

typedef enum NiveauHabitation_t {
    NIVEAU_RUINE,
    NIVEAU_TERRAIN_VAGUE,
    NIVEAU_CABANE,
    NIVEAU_MAISON,
    NIVEAU_IMMEUBLE,
    NIVEAU_GRATTE_CIEL,
} NiveauHabitation_t;


/// Représente une habitation simulée.
typedef struct Habitation_t {
    /// Niveau de l'habitation.
    NiveauHabitation_t niveau;
    /// Flot d'eau disponible pour l'habitation.
    int eau;
    /// Flot d'électricité disponible pour l'habitation.
    int electricite;
    /// Compteur de ticks avant prochaine évolution.
    int update_ticks;
    /// La position du bâtiment.
    Vector2I position;
    /// Distance a la centrale la plus proche
    /// L'habitation est-elle reliée au réseau d'eau?
    bool alimentee_en_eau;
    /// L'habitation est-elle reliée au réseau d'électrique?
    bool alimentee_en_electricite;
    bool relie_caserne;
} Habitation_t;

/// Crée une habitation.
Habitation_t* habitation_alloc(NiveauHabitation_t niveau);

/// Détruit une habitation.
void habitation_free(Habitation_t* habitation);

/// Incrémente d'un tick la simulation d'un bâtiment.
/// Retourne les impôts générés par l'habitation.
int habitation_step(Habitation_t* habitation, SimRules_t rules);

/// Fait évoluer un bâtiment en fonction des ticks d'évolution / régression.
void habitation_evolve(Habitation_t* habitation);

/// Retourne le nombre d'habitants dans l'habitation.
int habitation_get_nb_habitants(Habitation_t* habitation);

/// Retourne la qte d'eau nécessaire pour l'habitation pour qu'elle évolue.
int habitation_get_required_water(Habitation_t* habitation, SimRules_t rules);

/// Retourne la qte d'eau nécessaire pour l'habitation pour qu'elle évolue.
int habitation_get_required_energy(Habitation_t* habitation, SimRules_t rules);

/// Retourne la qte d'energie nécessaire pour l'habitation pour qu'elle évolue.
int habitation_get_remaining_required_energy(Habitation_t* habitation, SimRules_t rules);

int habitation_get_remaining_required_water(Habitation_t* habitation, SimRules_t rules);

int habitation_tri_par_distance(Habitation_t* a, Habitation_t* b);

#endif //ECECITY_HABITATION_H
