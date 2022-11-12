#include "sauvegarde.h"
#include "screens/gameplay.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <dirent.h>

int nombredeSauvegardes() {
    int nbSauvegarde = 0, compteur = 0;
    DIR *d;
    struct dirent *dir;
    d = opendir("../assets/txt");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            compteur++;
            if(compteur > 2){
                printf("\t%s\n", dir->d_name);
                nbSauvegarde++;
            }
            //printf("%s\n", dir->d_name);
            //nbSauvegarde++;
        }
        closedir(d);
    }
    return (nbSauvegarde);
}

char* creationFichierParUtilisateur(char *nomSauvegarde) {
    printf("Comment souhaitez vous appeler la sauvegarde ?\n");
    fflush(stdin);
    fgets(nomSauvegarde, 50, stdin);
    if (nomSauvegarde[strlen(nomSauvegarde) - 1] == '\n') {
        nomSauvegarde[strlen(nomSauvegarde) - 1] = '\0';
    }
    return nomSauvegarde;
}

char* recuperationFichierParUtilisateur(char *nomSauvegarde) {
    printf("Il y a %d sauvegardes. Avec quelle sauvegarde voulez-vous jouer ?\n\t", nombredeSauvegardes());
    scanf("%s", nomSauvegarde);
    if (nomSauvegarde[strlen(nomSauvegarde) - 1] == '\n') {
        nomSauvegarde[strlen(nomSauvegarde) - 1] = '\0';
    }
    return nomSauvegarde;
}

FILE* ouvrirFicherLecture(char* nomSauvegarde) {
    FILE* pMonFichier = NULL;
    char chemin[100];
    char extension[7] = ".txt";
    sprintf(chemin, "../assets/txt/%s%s", nomSauvegarde, extension);
    if ((pMonFichier = fopen(chemin, "r+")) == NULL) {
        printf("Erreur ouverture fichier lecture\n");
    }
    return pMonFichier;
}

FILE* ouvrirFicherEcriture(char* nomSauvegarde) {
    FILE* pMonFichier = NULL;
    char chemin[100];
    char extension[7] = ".txt";
    sprintf(chemin, "../assets/txt/%s%s", nomSauvegarde, extension);
    if ((pMonFichier = fopen(chemin, "w+")) == NULL) {
        printf("Erreur ouverture fichier lecture\n");
    }
    return pMonFichier;
}

void lireFichier(GameplayScreen_t* gameplayScreen, FILE* fichier){

    if (fichier != NULL) {

        char matrice[SIM_MAP_HAUTEUR][SIM_MAP_LARGEUR];

        for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
            for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
                fscanf(fichier, "%c ", &matrice[y][x]);
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

        fscanf(fichier, "%d", &gameplayScreen->world->rules);

        fscanf(fichier, "%d", &gameplayScreen->world->monnaie);

        fscanf(fichier, "%d", &gameplayScreen->world->n_ticks);

    }
}

void ecrireFichier(GameplayScreen_t* gameplayScreen, char* filename){

    FILE* fichier = ouvrirFicherEcriture(filename);

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

    if (fichier != NULL) {

        for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
            for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
                fprintf(fichier, "%c ", matrice[y][x]);
            }
            fprintf(fichier, "\n");
        }

        fprintf(fichier, "\n%d\n", gameplayScreen->world->rules);

        fprintf(fichier, "%d\n", gameplayScreen->world->monnaie);

        fprintf(fichier, "%d\n", gameplayScreen->world->n_ticks);

    }

    fclose(fichier);

}