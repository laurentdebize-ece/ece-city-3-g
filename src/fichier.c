#include "fichier.h"

void ouvrirFichier(ECECity* eceCity) {
    eceCity->fichier = fopen("../resources/file/txt/carte.txt", "r+");

}

void lireFichier(ECECity* eceCity){

    if (eceCity->fichier != NULL) {


        for (int y = 0; y < NBCELLULEY; y++) {
            for (int x = 0; x < NBCELLULEX; x++) {
                fscanf(eceCity->fichier, "%c ", &eceCity->matrice[y][x]);
            }
        }

        fscanf(eceCity->fichier, "%d", &eceCity->modeDeJeu);

        fscanf(eceCity->fichier, "%d", &eceCity->monnaie);

        fscanf(eceCity->fichier, "%d", &eceCity->chrono);

    }
}

void ecrireFichier(ECECity* eceCity){

    if (eceCity->fichier != NULL) {

        for (int y = 0; y < NBCELLULEY; y++) {
            for (int x = 0; x < NBCELLULEX; x++) {
                fprintf(eceCity->fichier, "%c ", eceCity->matrice[y][x]);
            }
            fprintf(eceCity->fichier, "\n");
        }

        fprintf(eceCity->fichier, "\n%d\n", eceCity->modeDeJeu);

        fprintf(eceCity->fichier, "%d\n", eceCity->monnaie);

        fprintf(eceCity->fichier, "%d\n", eceCity->chrono);

    }

}

void afficherLectureFichier(ECECity* eceCity){

    printf("Mode de jeu : %d\n", eceCity->modeDeJeu);
    printf("Matrice : \n");

    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            printf("%c ", eceCity->matrice[y][x]);
        }
        printf("\n");
    }

    printf("Monnaie : %d\n", eceCity->monnaie);
    printf("Chrono : %d\n", eceCity->chrono);

}


