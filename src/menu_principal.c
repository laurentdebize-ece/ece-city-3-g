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
    Rectangle textBoxJouer = {50, 200, 280, 85};
    Rectangle textBoxRegles = {50, 380, 340, 85};
    Rectangle textBoxCredits = {50, 560, 385, 85};

    BeginDrawing();

    ClearBackground(BLACK);
    bool SourisSurTexte;
    DrawTexture(menu->texture_fond, 0, 0, WHITE);

    if(CheckCollisionPointRec(GetMousePosition(), textBoxJouer) ||
       CheckCollisionPointRec(GetMousePosition(), textBoxCredits) ||
       CheckCollisionPointRec(GetMousePosition(), textBoxRegles)) {
        SourisSurTexte = true;
    } else{
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

    if(SourisSurTexte){

        if(CheckCollisionPointRec(GetMousePosition(), textBoxJouer)){
            DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {60, 208}, 110, 10, ORANGE);
            DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {70, 205}, 105, 10, WHITE);
            DrawTextEx(menu->font_ttf, "REGLES", (Vector2 ) {50, 386}, 88, 8, ORANGE);
            DrawTextEx(menu->font_ttf, "REGLES", (Vector2 ) {57, 385}, 82, 10, WHITE);
            DrawTextEx(menu->font_ttf, "CREDITS",(Vector2) {51, 566}, 88,8, ORANGE);
            DrawTextEx(menu->font_ttf, "CREDITS",(Vector2) {57, 565}, 82, 10, WHITE);
            DrawRectangle(18, 237, 12, 12, ORANGE);
            DrawRectangle(20, 235, 10, 10, WHITE);
            DrawRectangle(18, 417, 12, 12, ORANGE);
            DrawRectangle(20, 415, 10, 10, WHITE);
            DrawRectangle(18, 597, 12, 12, ORANGE);
            DrawRectangle(20, 595, 10, 10, WHITE);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), textBoxJouer)){
            ClearBackground(BLACK);
        }
        if(CheckCollisionPointRec(GetMousePosition(), textBoxRegles)){
            DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {60, 388}, 92, 10, ORANGE);
            DrawTextEx(menu->font_ttf, "REGLES", (Vector2) {70, 385}, 92, 10, WHITE);
            DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 206}, 88, 8, ORANGE);
            DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 205}, 82, 10, WHITE);
            DrawTextEx(menu->font_ttf, "CREDITS",(Vector2) {51, 566}, 88,8, ORANGE);
            DrawTextEx(menu->font_ttf, "CREDITS",(Vector2) {57, 565}, 82, 10, WHITE);;
            DrawRectangle(18, 417, 12, 12, ORANGE);
            DrawRectangle(20, 415, 10, 10, WHITE);
            DrawRectangle(18, 597, 12, 12, ORANGE);
            DrawRectangle(20, 595, 10, 10, WHITE);
            DrawRectangle(18, 237, 12, 12, ORANGE);
            DrawRectangle(20, 235, 10, 10, WHITE);
        }
        if (CheckCollisionPointRec(GetMousePosition(), textBoxCredits)){
            DrawTextEx(menu->font_ttf, "CREDITS", (Vector2 ){60, 568}, 92, 10, ORANGE);
            DrawTextEx(menu->font_ttf, "CREDITS", (Vector2 ){70, 565}, 92, 10, WHITE);
            DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {52, 206}, 88, 8, ORANGE);
            DrawTextEx(menu->font_ttf, "JOUER", (Vector2) {57, 205}, 82, 10, WHITE);
            DrawTextEx(menu->font_ttf, "REGLES", (Vector2 ) {50, 386}, 88, 8, ORANGE);
            DrawTextEx(menu->font_ttf, "REGLES", (Vector2 ) {57, 385}, 82, 10, WHITE);
            DrawRectangle(18, 597, 12, 12, ORANGE);
            DrawRectangle(20, 595, 10, 10, WHITE);
            DrawRectangle(18, 237, 12, 12, ORANGE);
            DrawRectangle(20, 235, 10, 10, WHITE);
            DrawRectangle(18, 417, 12, 12, ORANGE);
            DrawRectangle(20, 415, 10, 10, WHITE);
        }
    }
}

void menu_principal_update(Jeu_t* jeu, MenuPrincipal_t* menu) {
}

// les trucs a charger au lancement du jeu vont la
void menu_principal_enter(Jeu_t* jeu, MenuPrincipal_t* menu) {
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
