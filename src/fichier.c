#include "fichier.h"

void ouvrirFichier(SimWorld_t * eceCity) {
    eceCity->loader.fichierTxt = fopen("../resources/file/txt/carte.txt", "r+");

}

void lireFichier(SimWorld_t * eceCity){

    if (eceCity->loader.fichierTxt != NULL) {


        for (int y = 0; y < NBCELLULEY; y++) {
            for (int x = 0; x < NBCELLULEX; x++) {
                fscanf(eceCity->loader.fichierTxt, "%c ", &eceCity->matrice[y][x]);
            }
        }

        fscanf(eceCity->loader.fichierTxt, "%d", &eceCity->rules);

        fscanf(eceCity->loader.fichierTxt, "%d", &eceCity->monnaie);

        fscanf(eceCity->loader.fichierTxt, "%d", &eceCity->n_ticks);

    }
}

void ecrireFichier(SimWorld_t* eceCity){

    if (eceCity->loader.fichierTxt != NULL) {

        for (int y = 0; y < NBCELLULEY; y++) {
            for (int x = 0; x < NBCELLULEX; x++) {
                fprintf(eceCity->loader.fichierTxt, "%c ", eceCity->matrice[y][x]);
            }
            fprintf(eceCity->loader.fichierTxt, "\n");
        }

        fprintf(eceCity->loader.fichierTxt, "\n%d\n", eceCity->rules);

        fprintf(eceCity->loader.fichierTxt, "%d\n", eceCity->monnaie);

        fprintf(eceCity->loader.fichierTxt, "%d\n", eceCity->n_ticks);

    }

}

void afficherLectureFichier(SimWorld_t* eceCity){

    printf("Mode de jeu : %d\n", eceCity->rules);
    printf("Matrice : \n");

    for (int y = 0; y < NBCELLULEY; y++) {
        for (int x = 0; x < NBCELLULEX; x++) {
            printf("%c ", eceCity->matrice[y][x]);
        }
        printf("\n");
    }

    printf("Monnaie : %d\n", eceCity->monnaie);
    printf("Chrono : %d\n", eceCity->n_ticks);

}


