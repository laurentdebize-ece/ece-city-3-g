#include "route.h"
#include "tuile.h"

void selectionNewRoad(SimWorld_t *eceCity) {

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1012, 954, 40, 40})) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            //Actions Click New Road
            eceCity->informationsSouris.actionsMap.modeNewRoad = !eceCity->informationsSouris.actionsMap.modeNewRoad;
            eceCity->informationsSouris.actionsMap.depart[0].position.x = 0;
            eceCity->informationsSouris.actionsMap.depart[0].position.y = 0;
        }
    }
}

void checkChangementCelluleSurPlacementRoute(SimWorld_t *eceCity) {
    if (eceCity->informationsSouris.actionsMap.modeNewRoad) {
        if (eceCity->informationsSouris.boolChangementDeCelluleIso) {
            actualiserCheminRoute(eceCity);
        }
    }
}

void affichageRouteSelection(SimWorld_t *eceCity) {
    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            eceCity->carte.mapTile[y][x].tinte = WHITE;
        }
    }


    if (eceCity->informationsSouris.actionsMap.modeNewRoad) {
        for (int i = 0; i < eceCity->informationsSouris.actionsMap.nbChemins; i++) {

            if (!checkCollisionBatiment(eceCity)) {
                eceCity->carte.mapTile[eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleY][eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleX].tinte = BLUE;
            } else {
                eceCity->carte.mapTile[eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleY][eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleX].tinte = RED;

            }
        }
    }
}

bool checkCollisionBatiment(SimWorld_t *eceCity) {
    for (int i = 0; i < eceCity->informationsSouris.actionsMap.nbChemins; i++) {
        for (int y = 0; y < NBCELLULEY; y++) {
            for (int x = 0; x < NBCELLULEX; x++) {
                if (eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleX == x &&
                    eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleY == y) {
                    if (eceCity->carte.mapTile[y][x].typeBloc != TERRAIN_0) {
                        return true; //Collision
                    }
                }
            }
        }
    }
    return false; //Pas de collision
}

void actualiserCheminRoute(SimWorld_t *eceCity) {

    if (eceCity->informationsSouris.actionsMap.modeNewRoad &&
        (bool) eceCity->informationsSouris.actionsMap.depart[0].typeBloc &&
        !eceCity->informationsSouris.outOfMapBorders) {
        Cellules2D depart = {eceCity->informationsSouris.actionsMap.depart[0].position.x,
                             eceCity->informationsSouris.actionsMap.depart[0].position.y};
        Cellules2D arrivee = {eceCity->informationsSouris.celluleIso.x, eceCity->informationsSouris.celluleIso.y};

        eceCity->informationsSouris.actionsMap.nbChemins = 0;

        int diffX = arrivee.celluleX - depart.celluleX;
        int diffY = arrivee.celluleY - depart.celluleY;

        eceCity->informationsSouris.actionsMap.cheminRoute[0] = depart;
        eceCity->informationsSouris.actionsMap.nbChemins++;

        if (diffX > 0) {
            for (int i = 1; i <= diffX; i++) {
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins] = (Cellules2D) {
                        depart.celluleX + i, depart.celluleY};
                eceCity->informationsSouris.actionsMap.nbChemins++;
            }
        } else {
            for (int i = 1; i <= -diffX; i++) {
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins] = (Cellules2D) {
                        depart.celluleX - i, depart.celluleY};
                eceCity->informationsSouris.actionsMap.nbChemins++;
            }
        }

        if (diffY > 0) {
            for (int i = 1; i <= diffY; i++) {
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins] = (Cellules2D) {
                        arrivee.celluleX, depart.celluleY + i};
                eceCity->informationsSouris.actionsMap.nbChemins++;
            }
        } else {
            for (int i = 1; i <= -diffY; i++) {
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins] = (Cellules2D) {
                        arrivee.celluleX, depart.celluleY - i};
                eceCity->informationsSouris.actionsMap.nbChemins++;
            }
        }
        eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins] = arrivee;
        eceCity->informationsSouris.actionsMap.nbChemins++;
    }

}

void razCheminRoute(SimWorld_t* eceCity){
    eceCity->informationsSouris.actionsMap.nbChemins = 0;

    for (int i = 0; i < 100; i++) {
        eceCity->informationsSouris.actionsMap.cheminRoute[i] = (Cellules2D) {0, 0};
    }

}

void modeNewRoad(SimWorld_t *eceCity) {

    if (eceCity->informationsSouris.actionsMap.modeNewRoad) {
        if (!eceCity->informationsSouris.outOfMapBorders) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

                eceCity->informationsSouris.actionsMap.depart[eceCity->informationsSouris.actionsMap.nbDepart].position.x = eceCity->informationsSouris.celluleIso.x;
                eceCity->informationsSouris.actionsMap.depart[eceCity->informationsSouris.actionsMap.nbDepart].position.y = eceCity->informationsSouris.celluleIso.y;
                eceCity->informationsSouris.actionsMap.depart[eceCity->informationsSouris.actionsMap.nbDepart].typeBloc = ROUTE_0;

                if (eceCity->informationsSouris.actionsMap.nbDepart < 1) {
                    eceCity->informationsSouris.actionsMap.nbDepart++;
                } else {

                    if(!checkCollisionBatiment(eceCity)){
                        /// Actions pour placer la route

                        for (int i = 0; i < eceCity->informationsSouris.actionsMap.nbChemins; i++) {
                            eceCity->matrice[eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleY][eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleX] = 'R';
                        }

                        eceCity->carte.reloadMatrice = true;
                    }

                    eceCity->informationsSouris.actionsMap.nbDepart = 0;
                    eceCity->informationsSouris.actionsMap.depart[0].typeBloc = 0;
                    eceCity->informationsSouris.actionsMap.depart[0].position.x = 0;
                    eceCity->informationsSouris.actionsMap.depart[0].position.y = 0;
                    eceCity->informationsSouris.actionsMap.depart[1].typeBloc = 0;
                    eceCity->informationsSouris.actionsMap.depart[1].position.x = 0;
                    eceCity->informationsSouris.actionsMap.depart[1].position.y = 0;

                    razCheminRoute(eceCity);
                    
                }

            }
        }

    }

    DrawText(TextFormat("Mode route : %d", eceCity->informationsSouris.actionsMap.modeNewRoad), 10, 100, 20,
             (Color) {0, 0, 0, 255});
    DrawText(TextFormat("Depart : %d %d", eceCity->informationsSouris.actionsMap.depart[0].position.x,
                        eceCity->informationsSouris.actionsMap.depart[0].position.y), 10, 120, 20,
             (Color) {0, 0, 0, 255});
    DrawText(TextFormat("Arrivee : %d %d", eceCity->informationsSouris.actionsMap.depart[1].position.x,
                        eceCity->informationsSouris.actionsMap.depart[1].position.y), 10, 140, 20,
             (Color) {0, 0, 0, 255});
}

