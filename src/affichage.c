#include "affichage.h"

void loadTextureLogoToolbar(ECECity* eceCity) {
    eceCity->logoToolbar[HAMBURGER] = LoadTexture("../resources/img/logo/hamburger.png");
    eceCity->logoToolbar[SAVE] = LoadTexture("../resources/img/logo/save.png");
    eceCity->logoToolbar[PEOPLE] = LoadTexture("../resources/img/logo/people.png");
    eceCity->logoToolbar[ENERGY] = LoadTexture("../resources/img/logo/energy.png");
    eceCity->logoToolbar[WATER] = LoadTexture("../resources/img/logo/water.png");
    eceCity->logoToolbar[BUILD] = LoadTexture("../resources/img/logo/build.png");
    eceCity->logoToolbar[DESTROY] = LoadTexture("../resources/img/logo/destroy.png");
    eceCity->logoToolbar[TIME] = LoadTexture("../resources/img/logo/time.png");
    eceCity->logoToolbar[ROAD] = LoadTexture("../resources/img/logo/road.png");
    eceCity->logoToolbar[HABITATION] = LoadTexture("../resources/img/logo/house.png");
    eceCity->logoToolbar[CENTRALE] = LoadTexture("../resources/img/logo/industry.png");
    eceCity->logoToolbar[CHATEAU] = LoadTexture("../resources/img/logo/valve.png");
}

void afficherToolBar(ECECity* eceCity){
    DrawRectangle(0, 924, LARGEUR_FENETRE, 100, (Color) { 0, 194, 255, 191 });

    DrawRectangle(271, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(493, 954, 125, 40, (Color) { 238,238,238,200});
    DrawRectangle(717, 954, 125, 40, (Color) { 238,238,238,200});

    DrawText(TextFormat("%d", eceCity->nbHabitants), 271, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", eceCity->monnaie), 493, 954, 20, (Color) { 0, 0, 0, 255 });
    DrawText(TextFormat("%d", eceCity->chrono), 717, 954, 20, (Color) { 0, 0, 0, 255 });

    DrawTexture(eceCity->logoToolbar[HAMBURGER], 26, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[SAVE], 109, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[PEOPLE], 211, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[ENERGY], 446, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[WATER], 668, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[BUILD], 892, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[DESTROY], 1376, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[TIME], 1466, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[ROAD], 1012, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[HABITATION], 1082, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[CENTRALE], 1159, 954, WHITE);
    DrawTexture(eceCity->logoToolbar[CHATEAU], 1229, 954, WHITE);
}