#include "sauvegarde.h"
#include "screens/gameplay.h"
#include "stdio.h"
#include "stdlib.h"
#include <dirent.h>
#include "time.h"
#include "assert.h"

void get_time_sauvegarde(GameplayScreen_t* gameplay){
    time_t t;
    time(&t);

    gameplay->loader.sauvegardes_time[gameplay->loader.nb_sauvegardes] = ctime(&t);
}

int nombredeSauvegardes(GameplayScreen_t* gameplay) {
    int nbSauvegarde = 0, compteur = 0, i;
    gameplay->loader.directory = opendir("../assets/txt");

    struct dirent *dir;
    // opendir() renvoie un pointeur de type DIR.
    DIR *d = opendir("../assets/txt");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (compteur > 1) {
                strcpy(gameplay->loader.nom_sauvegardes[nbSauvegarde], dir->d_name);
                nbSauvegarde++;
            }
            compteur++;
        }
        closedir(d);
    }

    return (nbSauvegarde);
}

void update_nom_nb_sauvegardes(GameplayScreen_t* gameplay){
    if (gameplay->state.stateToolbar.stateMenuSave.resetNbSauvegardes) {
        gameplay->loader.nb_sauvegardes = nombredeSauvegardes(gameplay);
        gameplay->state.stateToolbar.stateMenuSave.resetNbSauvegardes = false;
    }
}

void ouvrirFichier(GameplayScreen_t* gameplayScreen) {
    char chemin[100];
    char extension[7] = ".txt";
    sprintf(chemin, "../assets/txt/%s", gameplayScreen->state.stateToolbar.stateMenuSave.nomFichierOuverture, extension);
    gameplayScreen->loader.fichierTxt = fopen(chemin, "r+");
}

void ouvrirFichierEcriture(GameplayScreen_t* gameplayScreen) {
    char chemin[100];
    char extension[7] = ".txt";
    sprintf(chemin, "../assets/txt/%s%s", gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier, extension);
    gameplayScreen->loader.fichierTxtWrite = fopen(chemin, "w+");
}


char hab2char(Habitation_t *hab) {
    switch (hab->niveau) {
        case NIVEAU_RUINE:
            return 'R';
        case NIVEAU_TERRAIN_VAGUE:
            return 'V';
        case NIVEAU_CABANE:
            return 'C';
        case NIVEAU_GRATTE_CIEL:
            return 'G';
        case NIVEAU_MAISON:
            return 'M';
        case NIVEAU_IMMEUBLE:
            return 'I';
    }
}

NiveauHabitation_t char2hab(char c) {
    switch (c) {
        case 'R':
            return NIVEAU_RUINE;
        case 'V':
            return NIVEAU_TERRAIN_VAGUE;
        case 'C':
            return NIVEAU_CABANE;
        case 'G':
            return NIVEAU_GRATTE_CIEL;
        case 'M':
            return NIVEAU_MAISON;
        case 'I':
            return NIVEAU_IMMEUBLE;
        default:
            break;
    }
}

struct bat_data {
    CaseKind_t type;
    int extra; // données supplémentaires
};

void sim_sauvegarder(SimWorld_t *world, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "w");
    assert(fichier != NULL && "Impossible d'ouvrir le fichier de sauvegarde pour écriture.");
    for (int i = 0; i < SIM_MAP_HAUTEUR; ++i) {
        for (int j = 0; j < SIM_MAP_LARGEUR; ++j) {
            switch (world->map[j][i].type) {
                case KIND_VIDE:
                    fprintf(fichier, "0");
                    break;
                case KIND_ROUTE:
                    fprintf(fichier, "r");
                    break;
                case KIND_HABITATION: {
                    Habitation_t *hab = world->map[j][i].donnees;
                    fprintf(fichier, "%c", hab2char(hab));
                }
                    break;
                case KIND_CENTRALE:
                    fprintf(fichier, "J");
                    break;
                case KIND_CHATEAU:
                    fprintf(fichier, "W");
                    break;
                default:
                    break;
            }
        }
        fprintf(fichier, "\n");
    }
    /// monnaie
    fprintf(fichier, "%d\n", world->monnaie);
    /// temps ecoule
    fprintf(fichier, "%d\n", world->n_ticks);
    /// mode de jeu
    fprintf(fichier, "%d\n", world->rules);

    fflush(fichier);
    fclose(fichier);
}


/// Load depuis un fichier une partie
void lireFichier(GameplayScreen_t* gameplayScreen){

    ouvrirFichier(gameplayScreen);

    //sim_world_destroy(gameplayScreen->world);
    //gameplayScreen->world = sim_world_create(Capitaliste_t, 500000);

    struct bat_data data[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR] = {0};

    /// on charge depuis le fichier texte les positions des batiments dans une matrice
    /// on écrit directement dans le monde les routes.
    for (int i = 0; i < SIM_MAP_HAUTEUR;) {
        for (int j = 0; j < SIM_MAP_LARGEUR;) {
            char cs = fgetc(gameplayScreen->loader.fichierTxt);
            switch (cs) {
                case '0':
                    gameplayScreen->world->map[j][i].type = KIND_VIDE;
                    ++j;
                    break;

                case 'r':
                    gameplayScreen->world->map[j][i].type = KIND_ROUTE;
                    ++j;
                    break;

                case 'J':
                    data[j][i].type = KIND_CENTRALE;
                    ++j;
                    break;

                case 'W':
                    data[j][i].type = KIND_CHATEAU;
                    ++j;
                    break;

                case 'R':
                case 'V':
                case 'C':
                case 'G':
                case 'M':
                case 'I': {
                    data[j][i].type = KIND_HABITATION;
                    data[j][i].extra = char2hab(cs);
                    ++j;
                }
                    break;

                default:
                    break;
            }
        }
        i++;
    }

    fscanf(gameplayScreen->loader.fichierTxt, "%d", &gameplayScreen->world->monnaie);
    fscanf(gameplayScreen->loader.fichierTxt, "%d", &gameplayScreen->world->n_ticks);
    fscanf(gameplayScreen->loader.fichierTxt, "%d", &gameplayScreen->world->rules);

    bool visited[SIM_MAP_LARGEUR][SIM_MAP_HAUTEUR] = {false};

    for (int i = 0; i < SIM_MAP_HAUTEUR; ++i) {
        for (int j = 0; j < SIM_MAP_LARGEUR; ++j) {
            if (!visited[j][i]) {
                switch (data[j][i].type) {
                    case KIND_HABITATION: {
                        for (int k = 0; k < 3; ++k) {
                            for (int l = 0; l < 3; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(gameplayScreen->world, KIND_HABITATION, j, i, false);
                        ((Habitation_t*)gameplayScreen->world->map[j][i].donnees)->niveau = data[j][i].extra;
                    }
                        break;
                    case KIND_CENTRALE: {
                        for (int k = 0; k < 6; ++k) {
                            for (int l = 0; l < 4; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(gameplayScreen->world, KIND_CENTRALE, j, i, false);
                    }
                        break;
                    case KIND_CHATEAU: {
                        for (int k = 0; k < 4; ++k) {
                            for (int l = 0; l < 6; ++l) {
                                visited[j + k][i + l] = true;
                            }
                        }
                        sim_place_entity(gameplayScreen->world, KIND_CHATEAU, j, i, false);
                    }
                        break;

                    default:
                        break;
                }
            }
        }
    }

    sim_update_voisins(gameplayScreen->world);

}

/// Sauvegarder la partie actuelle
void ecrireFichier(GameplayScreen_t* gameplayScreen){

    ouvrirFichierEcriture(gameplayScreen);

    for (int i = 0; i < SIM_MAP_HAUTEUR; ++i) {
        for (int j = 0; j < SIM_MAP_LARGEUR; ++j) {
            switch (gameplayScreen->world->map[j][i].type) {
                case KIND_VIDE:
                    fprintf(gameplayScreen->loader.fichierTxtWrite, "0");
                    break;
                case KIND_ROUTE:
                    fprintf(gameplayScreen->loader.fichierTxtWrite, "r");
                    break;
                case KIND_HABITATION: {
                    Habitation_t *hab = gameplayScreen->world->map[j][i].donnees;
                    fprintf(gameplayScreen->loader.fichierTxtWrite, "%c", hab2char(hab));
                }
                    break;
                case KIND_CENTRALE:
                    fprintf(gameplayScreen->loader.fichierTxtWrite, "J");
                    break;
                case KIND_CHATEAU:
                    fprintf(gameplayScreen->loader.fichierTxtWrite, "W");
                    break;
                default:
                    break;
            }
        }
        fprintf(gameplayScreen->loader.fichierTxtWrite, "\n");
    }
    /// monnaie
    fprintf(gameplayScreen->loader.fichierTxtWrite, "%d\n", gameplayScreen->world->monnaie);
    /// temps ecoule
    fprintf(gameplayScreen->loader.fichierTxtWrite, "%d\n", gameplayScreen->world->n_ticks);
    /// mode de jeu
    fprintf(gameplayScreen->loader.fichierTxtWrite, "%d\n", gameplayScreen->world->rules);

    fclose(gameplayScreen->loader.fichierTxtWrite);

}

char switchCaseToucheClavier() {
    if(IsKeyPressed(KEY_A)){
        return 'Q';
    } else if (IsKeyPressed(KEY_B)){
        return 'B';
    } else if (IsKeyPressed(KEY_C)){
        return 'C';
    } else if (IsKeyPressed(KEY_D)){
        return 'D';
    } else if (IsKeyPressed(KEY_E)){
        return 'E';
    } else if (IsKeyPressed(KEY_F)){
        return 'F';
    } else if (IsKeyPressed(KEY_G)){
        return 'G';
    } else if (IsKeyPressed(KEY_H)){
        return 'H';
    } else if (IsKeyPressed(KEY_I)){
        return 'I';
    } else if (IsKeyPressed(KEY_J)){
        return 'J';
    } else if (IsKeyPressed(KEY_K)){
        return 'K';
    } else if (IsKeyPressed(KEY_L)){
        return 'L';
    } else if (IsKeyPressed(KEY_M)){
        return 'M';
    } else if (IsKeyPressed(KEY_N)){
        return 'N';
    } else if (IsKeyPressed(KEY_O)){
        return 'O';
    } else if (IsKeyPressed(KEY_P)){
        return 'P';
    } else if (IsKeyPressed(KEY_Q)){
        return 'A';
    } else if (IsKeyPressed(KEY_R)){
        return 'R';
    } else if (IsKeyPressed(KEY_S)){
        return 'S';
    } else if (IsKeyPressed(KEY_T)){
        return 'T';
    } else if (IsKeyPressed(KEY_U)){
        return 'U';
    } else if (IsKeyPressed(KEY_V)){
        return 'V';
    } else if (IsKeyPressed(KEY_W)){
        return 'Z';
    } else if (IsKeyPressed(KEY_X)){
        return 'X';
    } else if (IsKeyPressed(KEY_Y)){
        return 'Y';
    } else if (IsKeyPressed(KEY_Z)){
        return 'W';
    } else if (IsKeyPressed(KEY_SPACE)){
        return ' ';
    } else if (IsKeyPressed(KEY_ENTER)){
        return '\0';
    } else if (IsKeyPressed(KEY_ESCAPE)){
        return '9';
    } else if (IsKeyPressed(KEY_BACKSPACE)) {
        return '1';
    }
    else {
            return '0';
    }
}

void afficher_saisie_nom_fichier(GameplayScreen_t* gameplay){
    if (gameplay->state.stateToolbar.stateMenuSave.modeAjout) {
        DrawRectangleRounded((Rectangle) {200, 300, 1200, 300}, 0.1f, 8, (Color) {0, 194, 255, 255});
        DrawText("Saisir le nom de la sauvegarde :", 420, 315, 48, WHITE);
        DrawRectangleRounded((Rectangle) {350, 400, 900, 150}, 0.1f, 8, WHITE);
        DrawText(TextFormat("%s.txt", gameplay->state.stateToolbar.stateMenuSave.nomFichier), 475, 430, 30, BLACK);
    }
}

void saisir_nom_fichier_sauvegarde(GameplayScreen_t* gameplayScreen) {
    if(gameplayScreen->state.stateToolbar.stateMenuSave.modeAjout){
        char touche = switchCaseToucheClavier();
        if (touche != '0') {
            if(touche == '9'){
                gameplayScreen->state.stateToolbar.stateMenuSave.modeAjout = false;
            }else if (touche == '\0') {
                /// Sauvegarde
                get_time_sauvegarde(gameplayScreen);
                ecrireFichier(gameplayScreen);
                gameplayScreen->state.stateToolbar.stateMenuSave.modeAjout = false;
            } else if (touche == '1'){
                gameplayScreen->state.stateToolbar.stateMenuSave.indice--;
                gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier[gameplayScreen->state.stateToolbar.stateMenuSave.indice] = '\0';
            } else {
                if (gameplayScreen->state.stateToolbar.stateMenuSave.indice < 10) {
                    gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier[gameplayScreen->state.stateToolbar.stateMenuSave.indice] = touche;
                    gameplayScreen->state.stateToolbar.stateMenuSave.nomFichier[gameplayScreen->state.stateToolbar.stateMenuSave.indice + 1] = '\0';
                    gameplayScreen->state.stateToolbar.stateMenuSave.indice++;
                } else {
                    /// Sauvegarde
                    get_time_sauvegarde(gameplayScreen);
                    ecrireFichier(gameplayScreen);
                    gameplayScreen->state.stateToolbar.stateMenuSave.modeAjout = false;
                }
            }
        }
    }
}

void update_composant_sauvegarde(GameplayScreen_t* gameplay, Vector2 pos, int i){
    if(CheckCollisionPointRec(pos, (Rectangle) {150, 186 + 100 * (float) i, 1300, 80})){
        /// On sélectionne une sauvegarde
        gameplay->state.stateToolbar.stateMenuSave.num_component_hover = i;
        gameplay->state.stateToolbar.stateMenuSave.hoverComponent = true;
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(pos, (Rectangle) {150, 186 + 100 * (float) i, 1300, 80})){
            /// On sélectionne une sauvegarde
            gameplay->state.stateToolbar.stateMenuSave.num_component_select = i;
            gameplay->state.stateToolbar.stateMenuSave.select_component = true;
        }
    }
}

void update_menu_sauvegarde(GameplayScreen_t* gameplay){

    update_nom_nb_sauvegardes(gameplay);

    if(gameplay->state.stateToolbar.modeSave){
        gameplay->state.stateToolbar.stateMenuSave.hoverComponent = false;
        gameplay->state.stateToolbar.stateMenuSave.hoverAdd = false;
        gameplay->state.stateToolbar.stateMenuSave.hoverCancel = false;
        gameplay->state.stateToolbar.stateMenuSave.hoverSel = false;
        gameplay->state.stateToolbar.stateMenuSave.clickAdd = false;
        gameplay->state.stateToolbar.stateMenuSave.clickSel = false;
        gameplay->state.stateToolbar.stateMenuSave.clickCancel = false;

        saisir_nom_fichier_sauvegarde(gameplay);

        Vector2 pos = (Vector2) {GetMouseX(), GetMouseY()};
        if(CheckCollisionPointRec(pos, (Rectangle) {1393, 108, 40, 40})){
            /// On sauvegarde la partie actuelle
            gameplay->state.stateToolbar.stateMenuSave.hoverAdd = true;
        }

        if(CheckCollisionPointRec(pos, (Rectangle) {820, 803, 40, 40})){
            /// On charge la partie sélectionnée
            gameplay->state.stateToolbar.stateMenuSave.hoverSel = true;
        }

        if(CheckCollisionPointRec(pos, (Rectangle) {740, 803, 40, 40})){
            /// On désélectionne la partie sélectionnée
            gameplay->state.stateToolbar.stateMenuSave.hoverCancel = true;
        }

        for (int i = 0; i < gameplay->loader.nb_sauvegardes; i++) {
            update_composant_sauvegarde(gameplay, pos, i);
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            if(CheckCollisionPointRec(pos, (Rectangle) {1393, 108, 40, 40})){
                /// On sauvegarde la partie actuelle
                gameplay->state.stateToolbar.stateMenuSave.clickAdd = true;
                gameplay->state.stateToolbar.stateMenuSave.modeAjout = true;
                gameplay->state.stateToolbar.stateMenuSave.indice = 0;
                strcpy(gameplay->state.stateToolbar.stateMenuSave.nomFichier, "");

            }

            if(CheckCollisionPointRec(pos, (Rectangle) {820, 803, 40, 40})){
                /// On charge la partie sélectionnée
                gameplay->state.stateToolbar.stateMenuSave.clickSel = true;
                if(gameplay->state.stateToolbar.stateMenuSave.num_component_select != -1 && gameplay->state.stateToolbar.stateMenuSave.select_component){
                    strcpy(gameplay->state.stateToolbar.stateMenuSave.nomFichierOuverture,gameplay->loader.nom_sauvegardes[gameplay->state.stateToolbar.stateMenuSave.num_component_select]);
                    lireFichier(gameplay);
                    gameplay->state.stateToolbar.modeSave = false;
                }

            }

            if(CheckCollisionPointRec(pos, (Rectangle) {740, 803, 40, 40})){
                /// On désélectionne la partie sélectionnée et on sort du menu sauvegarde
                gameplay->state.stateToolbar.stateMenuSave.clickCancel = true;
                gameplay->state.stateToolbar.modeSave = false;


            }
        }
    }
}

void affichage_composant_sauvegarde(GameplayScreen_t* gameplay, int i){
    Color color = (gameplay->state.stateToolbar.stateMenuSave.num_component_hover == i) && gameplay->state.stateToolbar.stateMenuSave.hoverComponent ? (Color) {98, 98, 98, 200} : (Color) {237, 225, 225, 240};
    if ((gameplay->state.stateToolbar.stateMenuSave.num_component_select == i) && gameplay->state.stateToolbar.stateMenuSave.select_component){
        color = (Color) {60, 60, 60, 200};
    }
    DrawRectangleRounded((Rectangle) {150,  186 + 100 * (float) i, 1300, 80}, 0.1f, 8, color);
    DrawText(TextFormat("%#d - %s -",i, gameplay->loader.nom_sauvegardes[i]), 160, 196 + 100 * i, 48, BLACK);
}

void affichage_menu_sauvegarde(GameplayScreen_t* gameplay){
    if(gameplay->state.stateToolbar.modeSave){

        DrawRectangleRounded((Rectangle) {100, 68, 1400, 800}, 0.1f, 8, (Color) { 0, 194, 255, 220 });
        DrawText("Menu Sauvegarde :", 575, 108, 48, WHITE);

        for (int i = 0; i < gameplay->loader.nb_sauvegardes; i++) {
            affichage_composant_sauvegarde(gameplay, i);
        }

        if(gameplay->state.stateToolbar.stateMenuSave.hoverCancel){
                DrawCircle(761, 824, 30 , (Color) { 0, 0, 0, 20 });
        } else if (gameplay->state.stateToolbar.stateMenuSave.clickCancel) {
                DrawCircle(761, 824, 30 , (Color) { 0, 0, 0, 45 });
        }
        DrawTexture(gameplay->state.toolbarIcons[ICON_CANCEL], 740, 803, gameplay->state.stateToolbar.stateMenuSave.clickCancel ? YELLOW : WHITE);
        if(gameplay->state.stateToolbar.stateMenuSave.hoverSel){
            DrawCircle(841, 824, 30 , (Color) { 0, 0, 0, 20 });
        } else if (gameplay->state.stateToolbar.stateMenuSave.clickSel) {
            DrawCircle(841, 824, 30 , (Color) { 0, 0, 0, 45 });
        }
        DrawTexture(gameplay->state.toolbarIcons[ICON_CHECK], 820, 803, gameplay->state.stateToolbar.stateMenuSave.clickSel ? YELLOW : WHITE);
        if(gameplay->state.stateToolbar.stateMenuSave.hoverAdd){
            DrawCircle(1414, 129, 30 , (Color) { 0, 0, 0, 20 });
        } else if (gameplay->state.stateToolbar.stateMenuSave.clickAdd) {
            DrawCircle(1414, 129, 30 , (Color) { 0, 0, 0, 45 });
        }
        DrawTexture(gameplay->state.toolbarIcons[ICON_ADD], 1393, 108, gameplay->state.stateToolbar.stateMenuSave.clickAdd ? YELLOW : WHITE);

        afficher_saisie_nom_fichier(gameplay);

    }
}