
#ifndef ECECITY_SIM_H
#define ECECITY_SIM_H

#include <utils/liste.h>
#include <sim/habitation.h>
#include <sim/centrale.h>
#include <sim/chateau.h>
#include <utils/vector.h>

#define SIM_MAP_LARGEUR 45
#define SIM_MAP_HAUTEUR 35

#define ROUTE_PRIX_CONSTRUCTION 10

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

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
    /// Casernes
    KIND_CASERNE,
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
    /// Permet d'indiquer si la case est connexe au réseau d'eau.
    bool connexe_eau;
    /// Permet d'indiquer si la case est connexe au réseau électrique.
    bool connexe_elec;
    /// Permet d'indiquer si la case est connexe aux casernes de pompier.
    bool connexe_caserne;
} Case_t;

/// Le monde de simulation du jeu.
typedef struct SimWorld_t {
    /// Liste chaînée des habitations du monde, pour un accès "linéaire".
    Liste_t* habitations;
    /// Liste chaînée des centrales électriques du monde, pour un accès "linéaire".
    Liste_t* centrales;
    /// Liste chaînée des châteaux d'eau du monde, pour un accès "linéaire".
    Liste_t* chateaux;
    /// Liste chaînée des casernes du monde, pour un accès "linéaire".
    Liste_t* casernes;
    /// Carte de la simulation (utilisé pour les parcours en largeur).
    Case_t map[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR];
    /// La qte de monnaie disponible.
    int monnaie;
    /// Nombre d'habitants dans le monde.
    int nb_total_habitants;
    /// Quantité totale d'eau disponible (mìse à dispo par les châteaux d'eau).
    int qte_totale_eau;
    /// Quantité totale d'électricité disponible (mise à dispo par les centrales électriques).
    int qte_totale_electricite;
    /// Les règles d'évolution pour la simulation.
    SimRules_t rules;
    /// Le temps écoulé depuis le début de la simulation (en ticks).
    int n_ticks;
    /// La simulation tourne-t-elle ?
    bool sim_running;
} SimWorld_t;

/// Crée un monde de simulation vide.
SimWorld_t* sim_world_create(SimRules_t rules, int monnaie);

/// Avance d'une étape la simulation.
void sim_world_step(SimWorld_t* world);

/// Détruit un monde de simulation.
void sim_world_destroy(SimWorld_t* world);

/// Détruit l'entitée séléctionnée.
void sim_destroy_entity(SimWorld_t* world, int x, int y);

/// Place une entité dans la carte de la simulation aux coordonnées données.
void sim_place_entity(SimWorld_t* world, CaseKind_t type, int x, int y, bool reload);

/// Vérifie si un bâtiment de dimensions précisés peut être placé à une position donnée.
bool sim_check_can_place(SimWorld_t* world, bool isBat, int x, int y, int w, int h);

/// Recalcule les voisins de chacunes des centrales & châteaux.
void sim_update_voisins(SimWorld_t* world);

#endif //ECECITY_SIM_H
