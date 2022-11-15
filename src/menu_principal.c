#include "menu_principal.h"
#include <stdio.h>

MenuPrincipal_t* menu_principal_alloc() {
    MenuPrincipal_t* test = malloc(sizeof(MenuPrincipal_t));
    test->screenInfo.draw_callback = menu_principal_draw;
    test->screenInfo.update_callback = menu_principal_update;
    test->screenInfo.on_enter_callback = menu_principal_enter;
    test->screenInfo.on_exit_callback = menu_principal_exit;
    test->screenInfo.screen_name = "MENU PRINCIPAL";
    return test;
}

void menu_principal_draw(Jeu_t* jeu, MenuPrincipal_t* menu) {
    bool SourisSurTexte;
    Rectangle textBoxJouer = {50, 200, 280, 85};
    Rectangle textBoxRegles = {50, 380, 300, 85};
    Rectangle textBoxCredits = {50, 560, 325, 85};
    Rectangle textBoxRetour = {15, 710, 165, 50};
    Rectangle boxCommuniste = {100, 200, 300, 150};
    Rectangle boxCapitaliste = {650, 200, 300, 150};
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) menu->nbClique++;


    DrawTexture(menu->texture_fond, 0, 0, WHITE);


    switch (menu->nbClique) {
            case 0:
                if(CheckCollisionPointRec(GetMousePosition(), textBoxJouer) ||
                   CheckCollisionPointRec(GetMousePosition(), textBoxCredits) ||
                   CheckCollisionPointRec(GetMousePosition(), textBoxRegles)) {
                    SourisSurTexte = true;
                }
                else{
                    SourisSurTexte = false;
                    DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 206}, 88, 8, ORANGE);
                    DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 205}, 82, 10, WHITE);
                    DrawTextEx(menu->font_ttf, "REGLES", (Vector2 ) {50, 386}, 88, 8, ORANGE);
                    DrawTextEx(menu->font_ttf, "REGLES", (Vector2 ) {57, 385}, 82, 10, WHITE);
                    DrawTextEx(menu->font_ttf, "CREDITS",(Vector2) {51, 566}, 88,8, ORANGE);
                    DrawTextEx(menu->font_ttf, "CREDITS",(Vector2) {57, 565}, 82, 10, WHITE);
                    DrawRectangle(18, 597, 12, 12, ORANGE);
                    DrawRectangle(18, 237, 12, 12, ORANGE);
                    DrawRectangle(18, 417, 12, 12, ORANGE);
                    DrawRectangle(20, 235, 10, 10, WHITE);
                    DrawRectangle(20, 415, 10, 10, WHITE);
                    DrawRectangle(20, 595, 10, 10, WHITE);
                }

                if(SourisSurTexte) {

                    if (CheckCollisionPointRec(GetMousePosition(), textBoxJouer)) {
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {60, 208}, 110, 10, ORANGE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {70, 205}, 105, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {50, 386}, 88, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {57, 385}, 82, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {51, 566}, 88, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {57, 565}, 82, 10, WHITE);
                        DrawRectangle(18, 237, 12, 12, ORANGE);
                        DrawRectangle(20, 235, 10, 10, WHITE);
                        DrawRectangle(18, 417, 12, 12, ORANGE);
                        DrawRectangle(20, 415, 10, 10, WHITE);
                        DrawRectangle(18, 597, 12, 12, ORANGE);
                        DrawRectangle(20, 595, 10, 10, WHITE);
                    }
                    if (CheckCollisionPointRec(GetMousePosition(), textBoxRegles)) {
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {60, 388}, 92, 10, ORANGE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {70, 385}, 92, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 206}, 88, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 205}, 82, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {51, 566}, 88, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {57, 565}, 82, 10, WHITE);;
                        DrawRectangle(18, 417, 12, 12, ORANGE);
                        DrawRectangle(20, 415, 10, 10, WHITE);
                        DrawRectangle(18, 597, 12, 12, ORANGE);
                        DrawRectangle(20, 595, 10, 10, WHITE);
                        DrawRectangle(18, 237, 12, 12, ORANGE);
                        DrawRectangle(20, 235, 10, 10, WHITE);
                    }
                    if (CheckCollisionPointRec(GetMousePosition(), textBoxCredits)) {
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {60, 568}, 92, 10, ORANGE);
                        DrawTextEx(menu->font_ttf, "CREDITS", (Vector2) {70, 565}, 92, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 206}, 88, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 205}, 82, 10, WHITE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {50, 386}, 88, 8, ORANGE);
                        DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {57, 385}, 82, 10, WHITE);
                        DrawRectangle(18, 597, 12, 12, ORANGE);
                        DrawRectangle(20, 595, 10, 10, WHITE);
                        DrawRectangle(18, 237, 12, 12, ORANGE);
                        DrawRectangle(20, 235, 10, 10, WHITE);
                        DrawRectangle(18, 417, 12, 12, ORANGE);
                        DrawRectangle(20, 415, 10, 10, WHITE);
                    }
                }
                break;

            case 1:
                DrawTexture(menu->texture_fond, 0, 0, WHITE);
                DrawRectangle(15, 710, 165, 50, LIGHTGRAY);
                DrawTextEx(menu->font_ttf, "CHOISIR LE MODE", (Vector2) {210, 520}, 92, 10, ORANGE);
                DrawTextEx(menu->font_ttf, "CHOISIR LE MODE", (Vector2) {220, 520}, 92, 10, WHITE);
                DrawTextEx(menu->font_ttf, "Retour", (Vector2){30, 720}, 45, 5, GRAY);
                DrawRectangle(100, 200, 300, 150, SKYBLUE);
                DrawRectangle(650, 200, 300, 150, SKYBLUE);
                DrawTextEx(menu->font_ttf, "COMMUNISTE", (Vector2){120, 250}, 50, 5, WHITE);
                DrawTextEx(menu->font_ttf, "CAPITALISTE", (Vector2){670, 250}, 50, 5, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), textBoxRetour)){
                    DrawRectangle(10, 695, 185, 70, DARKGRAY);
                    DrawRectangle(15, 700 ,175, 60, LIGHTGRAY);
                    DrawTextEx(menu->font_ttf, "Retour", (Vector2){30, 712}, 50, 5, GRAY);
                }
            if (CheckCollisionPointRec(GetMousePosition(), boxCommuniste)){
                DrawRectangle(100, 200, 300, 150, BLUE);
                DrawTextEx(menu->font_ttf, "COMMUNISTE", (Vector2){120, 250}, 50, 5, WHITE);
            }
            if(CheckCollisionPointRec(GetMousePosition(), boxCapitaliste)){
                DrawRectangle(650, 200, 300, 150, BLUE);
                DrawTextEx(menu->font_ttf, "CAPITALISTE", (Vector2){670, 250}, 50, 5, WHITE);
            }
            break;

            case 2:
                DrawRectangle(30, 10, 964, 628, SKYBLUE);
                DrawTextEx(menu->font_ttf, "LES REGLES DU JEU :", (Vector2){275, 20}, 60, 5, WHITE);
            DrawTextEx(menu->font_ttf, "\tDans ce jeu vous etes le maire de la ville ECE-city en charge\ndu bien-etre de ses citoyens."
                                       " Vous avez le pouvoir de construire \ndes infrastructures (routes lignes electriques"
                                       " canalisation) et \ndes batiments (centrales electriques,\n"
                                       "caserne de pompiers...).\n\n"
                                       "\tToutes ces taches seront a realiser en gerant un budget serre \nqui doit equilibrer les"
                                       " depenses liees a ces constructions et\nles recettes liees aux impots et taxes.\n\n"
                                       "\tPour une partie deux modes sont disponibles : communiste\net capitaliste.", (Vector2){70, 100}, 30, 3, WHITE);
                DrawRectangle(15, 710, 165, 50, LIGHTGRAY);
                DrawTextEx(menu->font_ttf, "Retour", (Vector2){30, 720}, 45, 5, GRAY);
                if (CheckCollisionPointRec(GetMousePosition(), textBoxRetour)){
                    DrawRectangle(10, 695, 185, 70, DARKGRAY);
                    DrawRectangle(15, 700 ,175, 60, LIGHTGRAY);
                    DrawTextEx(menu->font_ttf, "Retour", (Vector2){30, 712}, 50, 5, GRAY);
                }
            break;

            case 3:
                DrawRectangle(30, 10, 964, 628, SKYBLUE);
                DrawTextEx(menu->font_ttf, "LUCAS ARRIESSE", (Vector2){60, 220}, 50, 5, WHITE);
                DrawTextEx(menu->font_ttf, "EMMA BATHEROSSE", (Vector2){570, 220}, 50, 5, WHITE);
                DrawTextEx(menu->font_ttf, "LUCA SOLER", (Vector2){110, 580}, 50, 5, WHITE);
                DrawTextEx(menu->font_ttf, "JULES FEDIT", (Vector2){640, 580}, 50, 5, WHITE);
                DrawRectangle(15, 710, 165, 50, LIGHTGRAY);
                DrawTextEx(menu->font_ttf, "Retour", (Vector2){30, 720}, 45, 5, GRAY);
                if (CheckCollisionPointRec(GetMousePosition(), textBoxRetour)){
                    DrawRectangle(10, 695, 185, 70, DARKGRAY);
                    DrawRectangle(15, 700 ,175, 60, LIGHTGRAY);
                    DrawTextEx(menu->font_ttf, "Retour", (Vector2){30, 712}, 50, 5, GRAY);
                }
            break;

            case 4:
                DrawRectangle(0, 0, 1024, 768, BLACK);
            break;
            case 5:
                DrawRectangle(0, 0, 1024, 768, BLACK);
            break;
            default:
                break;

        }
    }

void menu_principal_update(Jeu_t* jeu, MenuPrincipal_t* menu) {
}

// les trucs a charger au lancement du jeu vont la
void menu_principal_enter(Jeu_t* jeu, MenuPrincipal_t* menu) {
    menu->nbClique = 0;
    menu->font_ttf = LoadFontEx("../assets/font/daddy-day.ttf", 36, NULL, 0);
    menu->texture_fond = LoadTexture("../assets/texture/Mon projet.png");
    menu->texture_logo = LoadTexture("../assets/texture/logo_simcity (1).png");
    menu->texture_EA = LoadTexture("../assets/texture/Electronic-Arts-Logo.png");
    menu->texture_loading = LoadTexture("../assets/texture/fond_loading.png");
}

// les trucs a supprimer a la fermeture du jeu vont la
void menu_principal_exit(Jeu_t* jeu, MenuPrincipal_t* menu) {
    UnloadTexture(menu->texture_fond);
    UnloadTexture(menu->texture_loading);
    UnloadTexture(menu->texture_logo);
    UnloadTexture(menu->texture_EA);
    UnloadFont(menu->font_ttf);
}
