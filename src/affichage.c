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

    DrawTexture(eceCity->loader.logoToolBar[HAMBURGER], 26, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[SAVE], 109, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[PEOPLE], 211, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[ENERGY], 446, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[WATER], 668, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[BUILD], 892, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[DESTROY], 1376, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[TIME], 1466, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[ROAD], 1012, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[HABITATION], 1082, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[CENTRALE], 1159, 954, WHITE);
    DrawTexture(eceCity->loader.logoToolBar[CHATEAU], 1229, 954, WHITE);
}