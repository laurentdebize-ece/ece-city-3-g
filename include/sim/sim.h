
#ifndef ECECITY_SIM_H
#define ECECITY_SIM_H

#include <utils/liste.h>
#include <sim/habitation.h>
#include <sim/centrale.h>
#include <sim/chateau.h>

#define SIM_MAP_LARGEUR 45
#define SIM_MAP_HAUTEUR 35

/// Le type de case
typedef enum CaseKind_t {
    /// case vide
    KIND_VIDE = 0,
    /// KIND_HABITATION
    KIND_HABITATION,
    /// Centrale électrique
    KIND_CENTRALE,
    /// Château d'eau
    KIND_CHATEAU,
    /// KIND_ROUTE
    KIND_ROUTE,
    NB_CASE_KIND,
} CaseKind_t;

/// Une case dans la carte de la simulation.
typedef struct Case_t {
    /// Un pointeur vers la structure de données correspondant de la case.
    void* donnees;
    /// Le type de la case.
    CaseKind_t type;
    /// Permet d'indiquer dans le cas d'une construction multi-case à quelle construction la case appartient.
    int discriminant;
} Case_t;

/// Le monde de simulation du jeu.
typedef struct SimWorld_t {
    /// Liste chaînée des habitations du monde, pour un accès "linéaire".
    Liste_t* habitations;
    /// Liste chaînée des centrales électriques du monde, pour un accès "linéaire".
    Liste_t* centrales;
    /// Liste chaînée des châteaux d'eau du monde, pour un accès "linéaire".
    Liste_t* chateaux;
    /// Liste chaînée des routes du monde, pour un accès "linéaire".
    Liste_t* routes;
    /// Carte de la simulation (utilisé pour les parcours en largeur).
    Case_t map[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR];
    /// La qte de monnaie disponible.
    int monnaie;
    /// Les règles d'évolution pour la simulation.
    SimRules_t rules;
    /// Le temps écoulé depuis le début de la simulation (en ticks).
    int n_ticks;
} SimWorld_t;

/// Crée un monde de simulation vide.
SimWorld_t* sim_world_create(SimRules_t rules, int monnaie);

/// Avance d'une étape la simulation.
void sim_world_step(SimWorld_t* world);

/// Détruit un monde de simulation.
void sim_world_destroy(SimWorld_t* world);

/// Place une entité dans la carte de la simulation aux coordonnées données.
void sim_place_entity(SimWorld_t* world, CaseKind_t type, int x, int y);

/// Vérifie si un bâtiment de dimensions précisés peut être placé à une position donnée.
bool sim_check_can_place(SimWorld_t* world, bool isBat, int x, int y, int w, int h);

#endif //ECECITY_SIM_H
