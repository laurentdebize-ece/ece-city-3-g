#include <stdio.h>
#include "raylib.h"
#include "jeu.h"

const ScreenInfo_t EMPTY_SCREEN = {
        .draw_callback = NULL,
        .update_callback = NULL,
        .on_enter_callback = NULL,
        .on_exit_callback = NULL,
        .screen_name = "VIDE"
};

/*int main() {
    Jeu_t jeu = {
            .should_exit = false,
            .screen = NULL
    };
    jeu_run(&jeu, &EMPTY_SCREEN);
}*/

#include "tuile.h"
#include "fichier.h"
#include "affichage.h"
#include "carte.h"

int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = LARGEUR_FENETRE;
    const int screenHeight = HAUTEUR_FENETRE;

    InitWindow(screenWidth, screenHeight, "ECECity");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    ECECity eceCity = {0};

    initMap(&eceCity);

    ouvrirFichier(&eceCity);
    lireFichier(&eceCity);
    //afficherLectureFichier(&eceCity);

    transfertMatriceEnTypeBloc(&eceCity);

    //affichageTypeBloc(&eceCity);

    eceCity.carte.spritesheetTexture = LoadTexture("../resources/img/carte/spriteSheet.png");
    eceCity.carte.spriteCheat = LoadImage("../resources/img/carte/tileCheat.png");

    loadTextureLogoToolbar(&eceCity);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        actualiserPositionSourisJoueur(&eceCity);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        //Test dessin blocs3x3 ou 4x6/6x4
        //DrawTextureRec(eceCity.carte.spritesheetTexture, eceCity.carte.spriteSheet[TERRAIN_1].rectangle,(Vector2) {(float) eceCity.carte.spriteSheet[TERRAIN_1].decalageXDecor + (float) eceCity.carte.mapTile[0][0].position.x, (float) eceCity.carte.mapTile[0][0].position.y + (float) eceCity.carte.spriteSheet[TERRAIN_1].decalageYDecor}, WHITE);

        afficherFondMap(&eceCity);

        affichageHover(&eceCity);


        texteDebug(&eceCity);

        afficherToolBar(&eceCity);

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(eceCity.carte.spritesheetTexture);       // Texture unloading

    UnloadImage(eceCity.carte.spriteCheat);        // Unload image from CPU memory (RAM)

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}