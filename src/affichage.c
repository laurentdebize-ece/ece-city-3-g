#include "affichage.h"

void loadTextureLogoToolbar(SimWorld_t* eceCity) {
    eceCity->loader.logoToolBar[HAMBURGER] = LoadTexture("../resources/img/logo/hamburger.png");
    eceCity->loader.logoToolBar[SAVE] = LoadTexture("../resources/img/logo/save.png");
    eceCity->loader.logoToolBar[PEOPLE] = LoadTexture("../resources/img/logo/people.png");
    eceCity->loader.logoToolBar[ENERGY] = LoadTexture("../resources/img/logo/energy.png");
    eceCity->loader.logoToolBar[WATER] = LoadTexture("../resources/img/logo/water.png");
    eceCity->loader.logoToolBar[BUILD] = LoadTexture("../resources/img/logo/build.png");
    eceCity->loader.logoToolBar[DESTROY] = LoadTexture("../resources/img/logo/destroy.png");
    eceCity->loader.logoToolBar[TIME] = LoadTexture("../resources/img/logo/time.png");
    eceCity->loader.logoToolBar[ROAD] = LoadTexture("../resources/img/logo/road.png");
    eceCity->loader.logoToolBar[HABITATION] = LoadTexture("../resources/img/logo/house.png");
    eceCity->loader.logoToolBar[CENTRALE] = LoadTexture("../resources/img/logo/industry.png");
    eceCity->loader.logoToolBar[CHATEAU] = LoadTexture("../resources/img/logo/valve.png");
}

void afficherToolBar(SimWorld_t* eceCity){
    DrawRectangle(0, 924, LARGEUR_FENETRE, 100, (Color) { 0, 194, 255, 191 });

    DrawRectangle(271, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(493, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(717, 954, 125, 40, (Color) { 238,238,238,200});

    DrawText(TextFormat("%d", eceCity->rules), 271, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", eceCity->monnaie), 493, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", eceCity->n_ticks), 717, 954, 20, (Color) { 0, 0, 0, 255 });


    if (eceCity->informationsSouris.effetsGraphiques.hoverMenu) {
        DrawCircle(53, 980, 35 , (Color) { 0, 0, 0, 20 });
    }
    DrawTexture(eceCity->loader.logoToolBar[HAMBURGER], 26, 954, WHITE);


    if (eceCity->informationsSouris.effetsGraphiques.hoverSave) {
        DrawCircle(120, 980, 35 , (Color) { 0, 0, 0, 20 });
    }
    DrawTexture(eceCity->loader.logoToolBar[SAVE], 109, 954, WHITE);

    DrawTexture(eceCity->loader.logoToolBar[PEOPLE], 211, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[ENERGY], 446, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[WATER], 668, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[BUILD], 892, 954, WHITE);



    if (eceCity->informationsSouris.effetsGraphiques.hoverDestruction) {
        DrawCircle(1394, 980, 30 , (Color) { 0, 0, 0, 20 });
    }
    DrawTexture(eceCity->loader.logoToolBar[DESTROY], 1376, 954, WHITE);

    DrawTexture(eceCity->loader.logoToolBar[TIME], 1466, 954, WHITE);


    if (eceCity->informationsSouris.effetsGraphiques.hoverRoute) {
        DrawCircle(1030, 970, 30 , (Color) { 0, 0, 0, 20 });
    } else if (eceCity->informationsSouris.actionsMap.modeNewRoad) {
        DrawCircle(1030, 970, 30 , (Color) { 0, 0, 0, 45 });
    }
    DrawTexture(eceCity->loader.logoToolBar[ROAD], 1012, 954, WHITE);


    if (eceCity->informationsSouris.effetsGraphiques.hoverHabitation) {
        DrawCircle(1100, 980, 30 , (Color) { 0, 0, 0, 20 });
    }
    DrawTexture(eceCity->loader.logoToolBar[HABITATION], 1082, 954, WHITE);
    if (eceCity->informationsSouris.effetsGraphiques.hoverCentrale) {
        DrawCircle(1177, 980, 30 , (Color) { 0, 0, 0, 20 });
    }
    DrawTexture(eceCity->loader.logoToolBar[CENTRALE], 1159, 954, WHITE);
    if (eceCity->informationsSouris.effetsGraphiques.hoverChateau) {
        DrawCircle(1247, 980, 30 , (Color) { 0, 0, 0, 20 });
    }
    DrawTexture(eceCity->loader.logoToolBar[CHATEAU], 1229, 954, WHITE);
}



void checkHoverToolbar(SimWorld_t* eceCity){

     if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {26, 954, 40, 40})) {
        //Actions Hoover New Road
        eceCity->informationsSouris.effetsGraphiques.hoverMenu = true;
    } else {
        eceCity->informationsSouris.effetsGraphiques.hoverMenu = false;
    }

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {109, 954, 40, 40})) {
        //Actions Hoover New Road
        eceCity->informationsSouris.effetsGraphiques.hoverSave = true;
    } else {
        eceCity->informationsSouris.effetsGraphiques.hoverSave = false;
    }


    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1012, 954, 40, 40})) {
        //Actions Hoover New Road
        eceCity->informationsSouris.effetsGraphiques.hoverRoute = true;
    } else {
            eceCity->informationsSouris.effetsGraphiques.hoverRoute = false;
    }

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1082, 954, 40, 40})) {
        //Actions Hoover New Road
        eceCity->informationsSouris.effetsGraphiques.hoverHabitation = true;
    } else {
        eceCity->informationsSouris.effetsGraphiques.hoverHabitation = false;
    }

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1159, 954, 40, 40})) {
        //Actions Hoover New Road
        eceCity->informationsSouris.effetsGraphiques.hoverCentrale = true;
    } else {
        eceCity->informationsSouris.effetsGraphiques.hoverCentrale = false;
    }

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1229, 954, 40, 40})) {
        //Actions Hoover New Road
        eceCity->informationsSouris.effetsGraphiques.hoverChateau = true;
    } else {
        eceCity->informationsSouris.effetsGraphiques.hoverChateau = false;
    }

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) {1376, 954, 40, 40})) {
        //Actions Hoover New Road
        eceCity->informationsSouris.effetsGraphiques.hoverDestruction = true;
    } else {
        eceCity->informationsSouris.effetsGraphiques.hoverDestruction = false;
    }


}