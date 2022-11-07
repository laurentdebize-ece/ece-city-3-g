#ifndef ECECITY_TILE_H
#define ECECITY_TILE_H

#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"
#include "sim/sim.h"

#define LARGEUR_FENETRE 1600
#define HAUTEUR_FENETRE 1024

#define NBCELLULEX 45
#define NBCELLULEY 35

#define ORIGINEX 17
#define ORIGINEY 3

#define SPRITELARGEUR 40
#define SPRITEHAUTEUR 20



typedef struct {
    Vector2D position;
    char typeBloc;
} Paire;



typedef struct {
    //Toolbar temporaire risque de changer avec les prochaines versions de l'interface
    ActionsMap actionsMap;
} ECECity;


void actualiserPositionSourisJoueur(SimWorld_t* eceCity);

int isometricCoordsToScreenX(SimWorld_t* eceCity);

int isometricCoordsToScreenY(SimWorld_t* eceCity);

void calculPositionSourisEnCelluleXY(SimWorld_t* eceCity);

void calculPositionSourisEnCelluleIso(SimWorld_t* eceCity);

void calculPositionSoursiEnOffsetDansUneCelluleXY(SimWorld_t* eceCity);

void calculPositionSourisEnCelluleIsoReactualiseeGraceSpriteCheat(SimWorld_t* eceCity);

void razOutOfMapBorders(SimWorld_t* eceCity);

void calculClicSurPersoPourTousChemin(SimWorld_t* eceCity);

Vector2 isometricCoordsToScreen(SimWorld_t *eceCity);

Vector2 celluleIsoToScreen(SimWorld_t* eceCity, Vector2 vector2D);




#endif
