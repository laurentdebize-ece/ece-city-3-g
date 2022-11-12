#ifndef ECECITY_SIM_H
#define ECECITY_SIM_H

#include <utils/liste.h>
#include <sim/habitation.h>
#include <sim/centrale.h>
#include <sim/chateau.h>
#include "spritesheet.h"
#include "raylib.h"

#define ROUTE_PRIX_CONSTRUCTION 10

/// Le type de case
typedef enum CaseKind_t {
    /// case vide
    KIND_VIDE = 0,
    /// KIND_HABITATION
    //KIND_HABITATION,
    KIND_TERRAIN_VAGUE,
    KIND_RUINE,
    KIND_CABANE,
    KIND_MAISON,
    KIND_IMMEUBLE,
    KIND_GRATTES_CIEL,
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
    /// Sa position sur l'écran en x,y
    Vector2 position;
    /// Un pointeur vers la structure de données correspondant de la case.
    void* donnees;
    /// Le type de la case.
    CaseKind_t type;
    /// Permet d'indiquer dans le cas d'une construction multi-case à quelle construction la case appartient.
    int discriminant;
    /// Détermine si la case est sélectionnée... (utile pour afficher les niveaux)
    Color tinte;
    /// Sprite à afficher
    CaseSprite_t sprite;
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
    Case_t map[35][45];
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

/// Détruit l'entitée séléctionnée.
void sim_destroy_entity(SimWorld_t* world, int x, int y);

/// Place une entité dans la carte de la simulation aux coordonnées données.
void sim_place_entity(SimWorld_t* world, CaseKind_t type, int x, int y);

/// Vérifie si un bâtiment de dimensions précisés peut être placé à une position donnée.
bool sim_check_can_place(SimWorld_t* world, bool isBat, int x, int y, int w, int h);

#endif //ECECITY_SIM_H
