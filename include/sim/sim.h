
#ifndef ECECITY_SIM_H
#define ECECITY_SIM_H

#include <utils/liste.h>
#include <sim/habitation.h>
#include <sim/centrale.h>
#include "raylib.h"
#include "stdio.h"

#define SIM_MAP_LARGEUR 45
#define SIM_MAP_HAUTEUR 35

enum LOGO_TOOLBAR {HAMBURGER, SAVE, PEOPLE, ENERGY, WATER, BUILD, DESTROY, TIME, ROAD, HABITATION, CENTRALE, CHATEAU, DOLLAR, NB_LOGOS_TOOLBAR};

enum SPRITE_MAP {CHEAT, HOOVER, CONTOUR, TERRAIN_0, TERRAIN_1, TERRAIN_2, TERRAIN_3, TERRAIN_4, TERRAIN_5,
    TERRAIN_6, ROUTE_0, ROUTE_1, ROUTE_2, ROUTE_3, ROUTE_4, ROUTE_5, ROUTE_6, ROUTE_7, ROUTE_8,
    ROUTE_9, ROUTE_10, ROUTE_11, ROUTE_12, ROUTE_13, ROUTE_14, TERRAIN_VAGUE_3X3, RUINE_3X3,
    CABANE_3X3, MAISON_3X3, IMMEUBLE_3X3, GRATTE_CIEL_3X3, ENERGY_4X6, ENERGY_6X4, EAU_4X6,
    EAU_6X4, VIDE, NB_SPRITES};

typedef struct {
    int x;
    int y;
} Vector2D;

typedef struct {
    int celluleX, celluleY;
} Cellules2D;

typedef struct {
    Vector2D position;
    Cellules2D cellulesXY;
    Cellules2D cellulesIso;
    int spriteLargeur, spriteHauteur;
    int spriteHalfLargeur, spriteHalfHauteur;
    int typeBloc;
} Tile;

typedef struct {
    Vector2D position;
    char typeBloc;
} RoadTest;

typedef struct ActionsMap {
    bool modeNewRoad;
    bool constructionRoute;
    bool actualiserCheminRoute;
    RoadTest depart[2];
    int nbDepart;
    Cellules2D cheminRoute[100];
    int nbChemins;
} ActionsMap;

typedef struct {
    Rectangle rectangle;//Position de l'image dans le sprite
    int decalageXDecor, decalageYDecor; //Utile que pour les décors
} Sprite_t;

typedef struct {
    Tile mapTile[SIM_MAP_HAUTEUR][SIM_MAP_LARGEUR];//Tableau à 2 dimensions de Tuiles qui permet de générer la map
    Cellules2D Origine;//La map n'est pas forcément dessinée en 0,0
    Sprite_t spriteSheet[NB_SPRITES];//Tableau de sprites pour permettre l'affichage
} Carte_t;

typedef struct Texture_t {
    Texture2D spriteSheetMapTexture;
    Texture2D logoToolBar[NB_LOGOS_TOOLBAR];
    Image spriteCheat;
    FILE* fichierTxt;
} Loader_t;

typedef struct {
    Vector2D offsetCellule;
    Vector2D celluleXY;
    Vector2D celluleIso;
    bool outOfMapBorders;
    bool boolChangementDeCelluleIso;
    ActionsMap actionsMap;
} informationsSouris_t;

/// Le type de case
typedef enum CaseKind_t {
    /// case vide
    Vide = 0,
    /// Habitation
    Habitation,
    /// Centrale électrique
    CentraleE,
    /// Château d'eau
    ChateauE,
    /// Route
    Route
} CaseKind_t;

/// Une case dans la carte de la simulation.
typedef struct Case_t {
    /// Un pointeur vers la structure de données correspondant de la case.
    void* donnees;
    /// Le type de la case.
    CaseKind_t type;
    /// Permet d'indiquer dans le cas d'une construction multi-case à quelle construction la case appartient.
    int discriminant;
    /// Chaque case a des infos pour l'affichage isométrique.
    Tile tuile;
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
    Case_t map[SIM_MAP_HAUTEUR][SIM_MAP_LARGEUR];
    /// Carte de la simulation (utilisé pour les parcours en largeur).
    Carte_t carte;
    /// Matrice pour charger le fichier de sauvegarde
    char matrice[SIM_MAP_HAUTEUR][SIM_MAP_LARGEUR];
    /// Informations utilisateurs
    informationsSouris_t informationsSouris;
    /// La qte de monnaie disponible.
    int monnaie;
    /// Les règles d'évolution pour la simulation. (Mode communiste/capitaliste)
    SimRules_t rules;
    /// Le temps écoulé depuis le début de la simulation (en ticks).
    int n_ticks;
    /// Load Textures
    Loader_t loader;
} SimWorld_t;

/// Crée un monde de simulation vide.
SimWorld_t* sim_world_create(SimRules_t rules, int monnaie);

/// Avance d'une étape la simulation.
void sim_world_step(SimWorld_t* world);

/// Détruit un monde de simulation.
void sim_world_destroy(SimWorld_t* world);

#endif //ECECITY_SIM_H
