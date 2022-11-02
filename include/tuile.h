#ifndef ECECITY_TILE_H
#define ECECITY_TILE_H

#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"

#define LARGEUR_FENETRE 1600
#define HAUTEUR_FENETRE 1024

#define NBCELLULEX 45
#define NBCELLULEY 35

#define ORIGINEX 17
#define ORIGINEY 3

#define SPRITELARGEUR 40
#define SPRITEHAUTEUR 20

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
    Rectangle rectangle;//Position de l'image dans le sprite
    int decalageXDecor, decalageYDecor; //Utile que pour les décors
} Sprite;

enum SPRITEMAP {CHEAT, HOOVER, CONTOUR, TERRAIN_0, TERRAIN_1, TERRAIN_2, TERRAIN_3, TERRAIN_4, TERRAIN_5,
    TERRAIN_6, ROUTE_0, ROUTE_1, ROUTE_2, ROUTE_3, ROUTE_4, ROUTE_5, ROUTE_6, ROUTE_7, ROUTE_8,
    ROUTE_9, ROUTE_10, ROUTE_11, ROUTE_12, ROUTE_13, ROUTE_14, TERRAIN_VAGUE_3X3, RUINE_3X3,
    CABANE_3X3, MAISON_3X3, IMMEUBLE_3X3, GRATTE_CIEL_3X3, ENERGY_4X6, ENERGY_6X4, EAU_4X6,
    EAU_6X4, VIDE, NB_SPRITES};


typedef struct {
    Tile mapTile[NBCELLULEY][NBCELLULEX];//Tableau à 2 dimensions de Tuiles qui permet de générer la map
    Cellules2D Origine;//La map n'est pas forcément dessinée en 0,0
    Sprite spriteSheet[NB_SPRITES];
    Image spriteCheat;
    Texture2D spritesheetTexture;
} Map;

typedef struct {
    Vector2D offsetCellule;
    Vector2D celluleXY;
    Vector2D celluleIso;
    bool outOfMapBorders;
    bool boolChangementDeCelluleIso;
} userInteraction;

typedef struct {
    Vector2D position;
    char typeBloc;
} Paire;

enum LOGO_TOOLBAR {HAMBURGER, SAVE, PEOPLE, ENERGY, WATER, BUILD, DESTROY, TIME, ROAD, HABITATION, CENTRALE, CHATEAU, DOLLAR, NB_LOGOS_TOOLBAR};

typedef struct ActionsMap {
    bool modeNewRoad;
} ActionsMap;

typedef struct {
    int modeDeJeu;
    int monnaie;
    int chrono;
    int nbHabitants;
    Map carte;
    userInteraction interactionExterieure;
    char matrice[NBCELLULEY][NBCELLULEX];
    FILE* fichier;


    //Toolbar temporaire risque de changer avec les prochaines versions de l'interface
    ActionsMap actionsMap;
    Texture2D logoToolbar[NB_LOGOS_TOOLBAR];
} ECECity;


void actualiserPositionSourisJoueur(ECECity* eceCity);

int isometricCoordsToScreenX(ECECity* eceCity);

int isometricCoordsToScreenY(ECECity* eceCity);

void calculPositionSourisEnCelluleXY(ECECity* eceCity);

void calculPositionSourisEnCelluleIso(ECECity* eceCity);

void calculPositionSoursiEnOffsetDansUneCelluleXY(ECECity* eceCity);

void calculPositionSourisEnCelluleIsoReactualiseeGraceSpriteCheat(ECECity* eceCity);

void razOutOfMapBorders(ECECity* eceCity);

void calculClicSurPersoPourTousChemin(ECECity* eceCity);

Vector2 isometricCoordsToScreen(ECECity *eceCity);




#endif
