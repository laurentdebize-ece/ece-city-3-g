#include "route.h"
#include "tuile.h"

void selectionNewRoad(SimWorld_t* eceCity){

    if(CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1012, 954, 40, 40})){
        //Actions Hoover New Road

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            //Actions Click New Road
            eceCity->informationsSouris.actionsMap.modeNewRoad = !eceCity->informationsSouris.actionsMap.modeNewRoad;
        }
    }

}

void affichageNewRoad(SimWorld_t* eceCity){

    if(eceCity->informationsSouris.actionsMap.constructionRoute){

    }

}

void checkChangementCelluleSurPlacementRoute(SimWorld_t* eceCity){
    if(eceCity->informationsSouris.actionsMap.modeNewRoad){
        if(eceCity->informationsSouris.boolChangementDeCelluleIso){
            actualiserCheminRoute(eceCity);
        }
    }
}
void affichageRouteSelection(SimWorld_t* eceCity){
    if(eceCity->informationsSouris.actionsMap.modeNewRoad && (bool) eceCity->informationsSouris.actionsMap.depart[0].typeBloc){
        for (int i = 0; i < eceCity->informationsSouris.actionsMap.nbChemins; i++) {
            DrawTextureRec(eceCity->loader.spriteSheetMapTexture,
                           eceCity->carte.spriteSheet[ROUTE_0].rectangle, (Vector2) celluleIsoToScreen(eceCity,
                                                                                                       (Vector2) {
                                                                                                               eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleX,
                                                                                                               eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleY}),
                           BLUE);
        }
    }
}

void actualiserCheminRoute(SimWorld_t* eceCity){
    if(eceCity->informationsSouris.actionsMap.modeNewRoad &&(bool) eceCity->informationsSouris.actionsMap.depart[0].typeBloc){
        int diffX = eceCity->informationsSouris.celluleIso.x - eceCity->informationsSouris.actionsMap.depart[0].position.x;
        int diffY = eceCity->informationsSouris.celluleIso.y - eceCity->informationsSouris.actionsMap.depart[0].position.y;

        eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleX = eceCity->informationsSouris.actionsMap.depart[0].position.x;
        eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleY = eceCity->informationsSouris.actionsMap.depart[0].position.y;
        eceCity->informationsSouris.actionsMap.nbChemins++;

        for (int i = 0; i < diffX; i++) {

            if(diffX < 0) {
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleX = eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins - 1].celluleX--;
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleY = eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins - 1].celluleY;
                eceCity->informationsSouris.actionsMap.nbChemins++;
            } else {
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleX = eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins - 1].celluleX++;
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleY = eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins - 1].celluleY;
                eceCity->informationsSouris.actionsMap.nbChemins++;
            }

        }

        for (int i = 0; i < diffY; i++) {

            if(diffY < 0) {
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleX = eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins - 1].celluleX;
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleY = eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins - 1].celluleY--;
                eceCity->informationsSouris.actionsMap.nbChemins++;
            } else {
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleX = eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins - 1].celluleX;
                eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins].celluleY = eceCity->informationsSouris.actionsMap.cheminRoute[eceCity->informationsSouris.actionsMap.nbChemins - 1].celluleY++;
                eceCity->informationsSouris.actionsMap.nbChemins++;
            }

        }
    }
}

void printChemin(SimWorld_t* eceCity){
    for (int i = 0; i < eceCity->informationsSouris.actionsMap.nbChemins; ++i) {

        printf("X : %d, Y : %d", eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleX, eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleY);

    }
}

void textDebugChemin(SimWorld_t* eceCity){
    for (int i = 0; i < eceCity->informationsSouris.actionsMap.nbChemins; i++){
        printf("(%d,%d)\n", eceCity->informationsSouris.actionsMap.cheminRoute[i].celluleX, eceCity->informationsSouris.actionsMap.cheminRoute->celluleY);
    }
}

void modeNewRoad(SimWorld_t* eceCity){


    if(eceCity->informationsSouris.actionsMap.modeNewRoad){

        if(!eceCity->informationsSouris.outOfMapBorders){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                eceCity->informationsSouris.actionsMap.depart[eceCity->informationsSouris.actionsMap.nbDepart].position.x = eceCity->informationsSouris.celluleIso.x;
                eceCity->informationsSouris.actionsMap.depart[eceCity->informationsSouris.actionsMap.nbDepart].position.y = eceCity->informationsSouris.celluleIso.y;
                eceCity->informationsSouris.actionsMap.depart[eceCity->informationsSouris.actionsMap.nbDepart].typeBloc = ROUTE_0;
                if (eceCity->informationsSouris.actionsMap.nbDepart < 1){
                    (eceCity->informationsSouris.actionsMap.nbDepart++);
                } else {
                    eceCity->informationsSouris.actionsMap.nbDepart = 0;
                    eceCity->informationsSouris.actionsMap.modeNewRoad = false;
                }
            }
        }

    }

    DrawText(TextFormat("Mode route : %d", eceCity->informationsSouris.actionsMap.modeNewRoad), 10, 100, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("Depart : %d %d", eceCity->informationsSouris.actionsMap.depart[0].position.x, eceCity->informationsSouris.actionsMap.depart[0].position.y), 10, 120, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("Arrivee : %d %d", eceCity->informationsSouris.actionsMap.depart[1].position.x, eceCity->informationsSouris.actionsMap.depart[1].position.y), 10, 140, 20, (Color) { 0, 0, 0, 255 });
}

void printDebug(SimWorld_t* eceCity){
    printf("Mode New Road : %d\n", eceCity->informationsSouris.actionsMap.modeNewRoad);
}

