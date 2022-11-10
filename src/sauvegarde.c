#include "sauvegarde.h"
#include "screens/gameplay.h"
#include "stdio.h"
#include "stdlib.h"


void ouvrirFichier(GameplayScreen_t* gameplayScreen) {
    gameplayScreen->loader.fichierTxt = fopen("../resources/file/txt/carte.txt", "r+");
}

void ouvrirFichierEcriture(GameplayScreen_t* gameplayScreen) {
    gameplayScreen->loader.fichierTxtWrite = fopen("../resources/file/txt/carte.txt", "w+");
}

void lireFichier(GameplayScreen_t* gameplayScreen){

    if (gameplayScreen->loader.fichierTxt != NULL) {

        char matrice[SIM_MAP_HAUTEUR][SIM_MAP_LARGEUR];

        for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
            for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
                fscanf(gameplayScreen->loader.fichierTxt, "%c ", &matrice[y][x]);
            }
        }

        for (int i = 0; i < SIM_MAP_HAUTEUR; i++) {
            for (int j = 0; j < SIM_MAP_LARGEUR; j++) {

                switch (matrice[i][j]) {
                    case '0':
                        gameplayScreen->world->map[i][j].type = KIND_VIDE;
                        break;
                    case 'T':
                        gameplayScreen->world->map[i][j].type = KIND_TERRAIN_VAGUE;
                        break;
                    case 'Y':
                        gameplayScreen->world->map[i][j].type = KIND_RUINE;
                        break;
                    case 'C':
                        gameplayScreen->world->map[i][j].type = KIND_CABANE;
                        break;
                    case 'M':
                        gameplayScreen->world->map[i][j].type = KIND_MAISON;
                        break;
                    case 'I':
                        gameplayScreen->world->map[i][j].type = KIND_IMMEUBLE;
                        break;
                    case 'S':
                        gameplayScreen->world->map[i][j].type = KIND_GRATTES_CIEL;
                        break;
                    case 'Z':
                        gameplayScreen->world->map[i][j].type = KIND_CENTRALE;
                        break;
                    case 'E':
                        gameplayScreen->world->map[i][j].type = KIND_CHATEAU;
                        break;
                    case 'R':
                        gameplayScreen->world->map[i][j].type = KIND_ROUTE;
                        break;
                    default:
                        break;
                }
            }
        }

        fscanf(gameplayScreen->loader.fichierTxt, "%d", &gameplayScreen->world->rules);

        fscanf(gameplayScreen->loader.fichierTxt, "%d", &gameplayScreen->world->monnaie);

        fscanf(gameplayScreen->loader.fichierTxt, "%d", &gameplayScreen->world->n_ticks);

    }
}

void ecrireFichier(GameplayScreen_t* gameplayScreen){

    ouvrirFichierEcriture(gameplayScreen);

    char matrice[SIM_MAP_HAUTEUR][SIM_MAP_LARGEUR];

    for (int i = 0; i < SIM_MAP_HAUTEUR; i++) {
        for (int j = 0; j < SIM_MAP_LARGEUR; j++) {

            switch (gameplayScreen->world->map[i][j].type) {
                case KIND_VIDE:
                    matrice[i][j] = '0';
                    break;
                case KIND_TERRAIN_VAGUE:
                    matrice[i][j] = 'T';
                    break;
                case KIND_RUINE:
                    matrice[i][j] = 'Y';
                    break;
                case KIND_CABANE:
                    matrice[i][j] = 'C';
                    break;
                case KIND_MAISON:
                    matrice[i][j] = 'M';
                    break;
                case KIND_IMMEUBLE:
                    matrice[i][j] = 'I';
                    break;
                case KIND_GRATTES_CIEL:
                    matrice[i][j] = 'S';
                    break;
                case KIND_CENTRALE:
                    matrice[i][j] = 'Z';
                    break;
                case KIND_CHATEAU:
                    matrice[i][j] = 'E';
                    break;
                case KIND_ROUTE:
                    matrice[i][j] = 'R';
                    break;
                default:
                    break;
            }
        }
    }

    if (gameplayScreen->loader.fichierTxt != NULL) {

        for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
            for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
                fprintf(gameplayScreen->loader.fichierTxt, "%c ", matrice[y][x]);
            }
            fprintf(gameplayScreen->loader.fichierTxt, "\n");
        }

        fprintf(gameplayScreen->loader.fichierTxt, "\n%d\n", gameplayScreen->world->rules);

        fprintf(gameplayScreen->loader.fichierTxt, "%d\n", gameplayScreen->world->monnaie);

        fprintf(gameplayScreen->loader.fichierTxt, "%d\n", gameplayScreen->world->n_ticks);

    }

    fclose(gameplayScreen->loader.fichierTxt);

}