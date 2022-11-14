#include "placement.h"
#include "utils/grille.h"
#include "bfs.h"

bool check_collision_batiment(GameplayScreen_t *gameplay) {
    for (int i = 0; i < gameplay->state.stateToolbar.stateBuildRoad.nbChemins; i++) {
        for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
            for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
                if (gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[i].x == x &&
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[i].y == y) {
                    if (gameplay->world->map[y][x].type != KIND_VIDE) {
                        return true; //Collision
                    }
                }
            }
        }
    }
    return false; //Pas de collision
}

CaseSprite_t update_type_route(Vector2I *chemin, int cheminActuel, int nbChemins, bool modeRotation) {

    ///TODO: update le dernier chemin pour qu'il soit en fonction de la rotation (tjrs vers le haut pour le moment ?)

    if (cheminActuel == nbChemins) {
        if (chemin[cheminActuel - 1].x + 1 == chemin[cheminActuel].x) {
            return SPRITE_ROUTE_1;
        } else if (chemin[cheminActuel - 1].x - 1 == chemin[cheminActuel].x) {
            return SPRITE_ROUTE_3;
        } else if (chemin[cheminActuel - 1].y + 1 == chemin[cheminActuel].y) {
            return SPRITE_ROUTE_2;
        } else if (chemin[cheminActuel - 1].y - 1 == chemin[cheminActuel].y) {
            return SPRITE_ROUTE_0;
        }
    } else if (cheminActuel != 0) {
        int diffX = chemin[cheminActuel - 1].x - chemin[cheminActuel + 1].x;
        int diffY = chemin[cheminActuel - 1].y - chemin[cheminActuel + 1].y;

        if (!modeRotation) {
            if ((diffX == 2 || diffX == -2) && diffY == 0) {
                return SPRITE_ROUTE_4;
            } else if ((diffY == 2 || diffY == -2) && diffX == 0) {
                return SPRITE_ROUTE_5;
            } else if ((diffX == -1) && (diffY == -1)) {
                return SPRITE_ROUTE_6;
            } else if ((diffX == 1) && (diffY == -1)) {
                return SPRITE_ROUTE_9;
            } else if ((diffX == 1) && (diffY == 1)) {
                return SPRITE_ROUTE_7;
            } else if ((diffX == -1) && (diffY == 1)) {
                return SPRITE_ROUTE_8;
            } else {
                return SPRITE_ROUTE_0;
            }
        } else {
            if ((diffX == 2 || diffX == -2) && diffY == 0) {
                return SPRITE_ROUTE_4;
            } else if ((diffY == 2 || diffY == -2) && diffX == 0) {
                return SPRITE_ROUTE_5;
            } else if ((diffX == -1) && (diffY == -1)) {
                return SPRITE_ROUTE_7;
            } else if ((diffX == 1) && (diffY == -1)) {
                return SPRITE_ROUTE_8;
            } else if ((diffX == 1) && (diffY == 1)) {
                return SPRITE_ROUTE_6;
            } else if ((diffX == -1) && (diffY == 1)) {
                return SPRITE_ROUTE_9;
            } else {
                return SPRITE_ROUTE_0;
            }
        }
    } else {
        if (chemin[cheminActuel + 1].x == chemin[cheminActuel].x + 1) {
            return SPRITE_ROUTE_1;
        } else if (chemin[cheminActuel + 1].x == chemin[cheminActuel].x - 1) {
            return SPRITE_ROUTE_3;
        } else if (chemin[cheminActuel + 1].y == chemin[cheminActuel].y + 1) {
            return SPRITE_ROUTE_2;
        } else if (chemin[cheminActuel + 1].y == chemin[cheminActuel].y - 1) {
            return SPRITE_ROUTE_0;
        }
    }
}

int get_nb_routes_adj_batiment(GameplayScreen_t *gameplay, Vector2 position, Orientation_t orientation) {

    int compteur = 0;
    int w = 0;
    int h = 0;

    if (orientation == ORIENTATION_4X6) {
        w = 4;
        h = 6;
    } else if (orientation == ORIENTATION_6X4) {
        w = 6;
        h = 4;
    } else if (orientation == ORIENTATION_NULL) {
        w = 3;
        h = 3;
    }

    for (int y = 0; y < h; y++) {
        if (gameplay->world->map[((int) position.y) + y][((int) position.x) - 1].type == KIND_ROUTE) {
            compteur++;
        }
        if (gameplay->world->map[((int) position.y) + y][((int) position.x) + w].type == KIND_ROUTE) {
            compteur++;
        }
    }

    for (int x = 0; x < w; x++) {
        if (gameplay->world->map[((int) position.y) - 1][((int) position.x) + x].type == KIND_ROUTE) {
            compteur++;
        }
        if (gameplay->world->map[((int) position.y) + h][((int) position.x) + x].type == KIND_ROUTE) {
            compteur++;
        }
    }

    return compteur;
}

void get_routes_adj_batiment(GameplayScreen_t *gameplay, Vector2 position, Orientation_t orientation, Vector2 *routes) {
    int compteur = 0;
    int w = 0;
    int h = 0;
    int nbRoutes = 0;

    if (orientation == ORIENTATION_4X6) {
        w = 4;
        h = 6;
    } else if (orientation == ORIENTATION_6X4) {
        w = 6;
        h = 4;
    } else if (orientation == ORIENTATION_NULL) {
        w = 3;
        h = 3;
    }

    for (int y = 0; y < h; y++) {
        if (gameplay->world->map[(int) position.y + y][(int) position.x - 1].type == KIND_ROUTE) {
            routes[nbRoutes] = (Vector2) {position.x - 1, position.y + y};
            nbRoutes++;
        }
        if (gameplay->world->map[(int) position.y + y][(int) position.x + w].type == KIND_ROUTE) {
            routes[nbRoutes] = (Vector2) {position.x + w, position.y + y};
            nbRoutes++;
        }
    }

    for (int x = 0; x < w; x++) {
        if (gameplay->world->map[(int) position.y - 1][(int) position.x + x].type == KIND_ROUTE) {
            routes[nbRoutes] = (Vector2) {position.x + x, position.y - 1};
            nbRoutes++;
        }
        if (gameplay->world->map[(int) position.y + h][(int) position.x + x].type == KIND_ROUTE) {
            routes[nbRoutes] = (Vector2) {position.x + x, position.y + h};
            nbRoutes++;
        }
    }
}

void draw_route_selectionee(GameplayScreen_t *gameplay) {
    if (gameplay->state.stateToolbar.stateBuildRoad.nbChemins > 0 &&
        gameplay->state.stateToolbar.stateBuildRoad.depart[0].x != -1) {
        for (int i = 0; i < gameplay->state.stateToolbar.stateBuildRoad.nbChemins; i++) {
            DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture, gameplay->spriteSheet.sprites[update_type_route(
                                   gameplay->state.stateToolbar.stateBuildRoad.cheminRoute, i,
                                   gameplay->state.stateToolbar.stateBuildRoad.nbChemins,
                                   gameplay->state.stateToolbar.rotationRoute)].rectangle,
                           iso_to_screen(gameplay,
                                         (Vector2I) {gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[i].x,
                                                     gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[i].y}),
                           check_collision_batiment(gameplay) ? RED : GREEN);
        }
    }
}

void update_chemin_route(GameplayScreen_t *gameplay) {

    if (gameplay->state.stateToolbar.modePlacementRoute &&
        !gameplay->state.stateMouse.outOfMapBorders &&
        gameplay->state.stateToolbar.stateBuildRoad.depart[0].x != -1) {
        Vector2I depart = {gameplay->state.stateToolbar.stateBuildRoad.depart[0].x,
                           gameplay->state.stateToolbar.stateBuildRoad.depart[0].y};
        Vector2I arrivee = {gameplay->state.stateMouse.celluleIso.x, gameplay->state.stateMouse.celluleIso.y};

        gameplay->state.stateToolbar.stateBuildRoad.nbChemins = 0;

        int diffX = arrivee.x - depart.x;
        int diffY = arrivee.y - depart.y;

        gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[0] = depart;
        gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;

        if (gameplay->state.stateToolbar.rotationRoute) {
            if (diffX > 0) {
                for (int i = 1; i <= diffX; i++) {
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = (Vector2I) {
                            depart.x + i, depart.y};
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
                }
            } else {
                for (int i = 1; i <= -diffX; i++) {
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = (Vector2I) {
                            depart.x - i, depart.y};
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
                }
            }

            if (diffY > 0) {
                for (int i = 1; i <= diffY; i++) {
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = (Vector2I) {
                            arrivee.x, depart.y + i};
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
                }
            } else {
                for (int i = 1; i <= -diffY; i++) {
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = (Vector2I) {
                            arrivee.x, depart.y - i};
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
                }
            }
        } else {
            if (diffY > 0) {
                for (int i = 1; i <= diffY; i++) {
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = (Vector2I) {
                            depart.x, depart.y + i};
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
                }
            } else {
                for (int i = 1; i <= -diffY; i++) {
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = (Vector2I) {
                            depart.x, depart.y - i};
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
                }
            }
            if (diffX > 0) {
                for (int i = 1; i <= diffX; i++) {
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = (Vector2I) {
                            depart.x + i, arrivee.y};
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
                }
            } else {
                for (int i = 1; i <= -diffX; i++) {
                    gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = (Vector2I) {
                            depart.x - i, arrivee.y};
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
                }
            }
        }
        gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[gameplay->state.stateToolbar.stateBuildRoad.nbChemins] = arrivee;
        gameplay->state.stateToolbar.stateBuildRoad.nbChemins++;
    }

}

void update_placement_route(GameplayScreen_t *gameplay) {

    if (gameplay->state.stateToolbar.modePlacementRoute) {
        if (!gameplay->state.stateMouse.outOfMapBorders) {

            if (IsKeyPressed(KEY_R)) {
                gameplay->state.stateToolbar.rotationRoute = !gameplay->state.stateToolbar.rotationRoute;
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                gameplay->state.stateToolbar.stateBuildRoad.depart[gameplay->state.stateToolbar.stateBuildRoad.nbDepart].x = gameplay->state.stateMouse.celluleIso.x;
                gameplay->state.stateToolbar.stateBuildRoad.depart[gameplay->state.stateToolbar.stateBuildRoad.nbDepart].y = gameplay->state.stateMouse.celluleIso.y;

                if (gameplay->state.stateToolbar.stateBuildRoad.nbDepart < 1) {
                    gameplay->state.stateToolbar.stateBuildRoad.nbDepart++;
                } else {
                    if (!check_collision_batiment(gameplay) && gameplay->world->monnaie > ROUTE_PRIX_CONSTRUCTION) {

                        for (int i = 0; i < gameplay->state.stateToolbar.stateBuildRoad.nbChemins; ++i) {
                            gameplay->world->map[(int) gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[i].y][(int) gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[i].x].type = KIND_ROUTE;
                        }

                        /// La carte a été mise à jour, on peut donc réinitialiser le chemin

                    }

                    gameplay->state.stateToolbar.stateBuildRoad.nbDepart = 0;
                    gameplay->state.stateToolbar.stateBuildRoad.nbChemins = 0;
                    for (int i = 0; i < 100; i++) {
                        gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[i].x = 0;
                        gameplay->state.stateToolbar.stateBuildRoad.cheminRoute[i].y = 0;
                    }
                    gameplay->state.stateToolbar.stateBuildRoad.depart[0].x = -1;
                    gameplay->state.stateToolbar.stateBuildRoad.depart[0].y = -1;
                    gameplay->state.stateToolbar.stateBuildRoad.depart[1].x = -1;
                    gameplay->state.stateToolbar.stateBuildRoad.depart[1].y = -1;

                    gameplay->world->monnaie -= ROUTE_PRIX_CONSTRUCTION;
                    gameplay->reloadCarte = true;
                }
            }
        }
    }
}

void check_changement_cellule_placement_route(GameplayScreen_t *gameplay) {
    if (gameplay->state.stateToolbar.modePlacementRoute) {
        if (gameplay->state.stateMouse.boolChangementDeCelluleIso) {
            update_chemin_route(gameplay);
        }
    }
}

void update_type_bloc_route(GameplayScreen_t *gameplay) {
    for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
        for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
            if (gameplay->world->map[y][x].type == KIND_ROUTE) {
                if (gameplay->world->map[y + 1][x].type == KIND_ROUTE &&
                    gameplay->world->map[y - 1][x].type == KIND_ROUTE &&
                    gameplay->world->map[y][x + 1].type == KIND_ROUTE &&
                    gameplay->world->map[y][x - 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_14;
                } else if (gameplay->world->map[y][x - 1].type == KIND_ROUTE &&
                           gameplay->world->map[y - 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y][x + 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_13;
                } else if (gameplay->world->map[y + 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y - 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y][x - 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_12;
                } else if (gameplay->world->map[y + 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y][x - 1].type == KIND_ROUTE &&
                           gameplay->world->map[y][x + 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_11;
                } else if (gameplay->world->map[y + 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y - 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y][x + 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_10;
                } else if (gameplay->world->map[y - 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y][x - 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_9;
                } else if (gameplay->world->map[y + 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y][x + 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_8;
                } else if (gameplay->world->map[y + 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y][x - 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_7;
                } else if (gameplay->world->map[y - 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y][x + 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_6;
                } else if (gameplay->world->map[y + 1][x].type == KIND_ROUTE &&
                           gameplay->world->map[y - 1][x].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_5;
                } else if (gameplay->world->map[y][x + 1].type == KIND_ROUTE &&
                           gameplay->world->map[y][x - 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_4;
                } else if (gameplay->world->map[y][x - 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_3;
                } else if (gameplay->world->map[y + 1][x].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_2;
                } else if (gameplay->world->map[y][x + 1].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_1;
                } else if (gameplay->world->map[y - 1][x].type == KIND_ROUTE) {
                    gameplay->world->map[y][x].sprite = SPRITE_ROUTE_0;
                }
            }
        }
    }
}

void update_type_bloc_general(GameplayScreen_t *gameplay) {

    struct Maillon_t* parcours = gameplay->world->habitations->premier;

    while (parcours != NULL){
        Vector2 position = ((Habitation_t*)parcours->data)->position;

        switch (((Habitation_t*)parcours->data)->niveau) {
            case NIVEAU_RUINE:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        gameplay->world->map[(int) position.y + i][(int) position.x + j].type = KIND_RUINE;
                    }
                }
                break;
            case NIVEAU_TERRAIN_VAGUE:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        gameplay->world->map[(int) position.y + i][(int) position.x + j].type = KIND_TERRAIN_VAGUE;
                    }
                }
                break;
            case NIVEAU_CABANE:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        gameplay->world->map[(int) position.y + i][(int) position.x + j].type = KIND_CABANE;
                    }
                }
                break;
            case NIVEAU_MAISON:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        gameplay->world->map[(int) position.y + i][(int) position.x + j].type = KIND_MAISON;
                    }
                }
                break;
            case NIVEAU_IMMEUBLE:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        gameplay->world->map[(int) position.y + i][(int) position.x + j].type = KIND_IMMEUBLE;
                    }
                }
                break;
            case NIVEAU_GRATTE_CIEL:
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        gameplay->world->map[(int) position.y + i][(int) position.x + j].type = KIND_GRATTES_CIEL;
                    }
                }
                break;
        }

        parcours = parcours->next;
    }

    for (int y = 0; y < SIM_MAP_HAUTEUR; y++) {
        for (int x = 0; x < SIM_MAP_LARGEUR; x++) {
            if (gameplay->world->map[y][x].type == KIND_VIDE) {
                gameplay->world->map[y][x].sprite = SPRITE_TERRAIN_0;
                //(rand() % (TERRAIN_6 - TERRAIN_0 + 1) + TERRAIN_0);
            }

            if (gameplay->world->map[y][x].type == KIND_ROUTE) {
                gameplay->world->map[y][x].sprite = SPRITE_ROUTE_0;
            }

            if (gameplay->world->map[y][x].type == KIND_TERRAIN_VAGUE) {
                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_TERRAIN_VAGUE_3X3) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_TERRAIN_VAGUE_3X3) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_TERRAIN_VAGUE_3X3) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_TERRAIN_VAGUE_3X3) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_TERRAIN_VAGUE_3X3) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_TERRAIN_VAGUE_3X3) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_TERRAIN_VAGUE_3X3) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_TERRAIN_VAGUE_3X3)) {
                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;
                } else {
                    gameplay->world->map[y][x].sprite = SPRITE_TERRAIN_VAGUE_3X3;
                }
            }

            if (gameplay->world->map[y][x].type == KIND_RUINE) {
                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_RUINE_3X3) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_RUINE_3X3) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_RUINE_3X3) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_RUINE_3X3) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_RUINE_3X3) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_RUINE_3X3) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_RUINE_3X3) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_RUINE_3X3)) {
                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;
                } else {
                    gameplay->world->map[y][x].sprite = SPRITE_RUINE_3X3;
                }
            }

            if (gameplay->world->map[y][x].type == KIND_CABANE) {
                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_CABANE_3X3) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_CABANE_3X3) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_CABANE_3X3) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_CABANE_3X3) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_CABANE_3X3) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_CABANE_3X3) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_CABANE_3X3) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_CABANE_3X3)) {
                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;
                } else {
                    gameplay->world->map[y][x].sprite = SPRITE_CABANE_3X3;
                }
            }

            if (gameplay->world->map[y][x].type == KIND_MAISON) {
                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_MAISON_3X3) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_MAISON_3X3) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_MAISON_3X3) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_MAISON_3X3) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_MAISON_3X3) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_MAISON_3X3) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_MAISON_3X3) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_MAISON_3X3)) {
                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;
                } else {
                    gameplay->world->map[y][x].sprite = SPRITE_MAISON_3X3;
                }
            }

            if (gameplay->world->map[y][x].type == KIND_IMMEUBLE) {
                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_IMMEUBLE_3X3) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_IMMEUBLE_3X3) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_IMMEUBLE_3X3) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_IMMEUBLE_3X3) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_IMMEUBLE_3X3) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_IMMEUBLE_3X3) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_IMMEUBLE_3X3) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_IMMEUBLE_3X3)) {
                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;
                } else {
                    gameplay->world->map[y][x].sprite = SPRITE_IMMEUBLE_3X3;
                }
            }

            if (gameplay->world->map[y][x].type == KIND_GRATTES_CIEL) {
                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_GRATTE_CIEL_3X3) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_GRATTE_CIEL_3X3) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_GRATTE_CIEL_3X3) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_GRATTE_CIEL_3X3) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_GRATTE_CIEL_3X3) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_GRATTE_CIEL_3X3) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_GRATTE_CIEL_3X3) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_GRATTE_CIEL_3X3)) {
                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;
                } else {
                    gameplay->world->map[y][x].sprite = SPRITE_GRATTE_CIEL_3X3;
                }
            }

            if (gameplay->world->map[y][x].type == KIND_CENTRALE) {

                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y][x - 3].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 3][x].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 4][x].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 5][x].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 1][x - 3].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 2][x - 3].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 3][x - 1].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 3][x - 2].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 3][x - 3].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 4][x - 1].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 4][x - 2].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 4][x - 3].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 5][x - 1].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 5][x - 2].sprite == SPRITE_ENERGY_4X6) ||
                    (gameplay->world->map[y - 5][x - 3].sprite == SPRITE_ENERGY_4X6)) {

                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;

                } else {
                    if (gameplay->world->map[y + 1][x].type == KIND_CENTRALE &&
                        gameplay->world->map[y + 2][x].type == KIND_CENTRALE
                        && gameplay->world->map[y + 3][x].type == KIND_CENTRALE &&
                        gameplay->world->map[y + 4][x].type == KIND_CENTRALE
                        && gameplay->world->map[y + 5][x].type == KIND_CENTRALE &&
                        gameplay->world->map[y][x + 1].type == KIND_CENTRALE
                        && gameplay->world->map[y][x + 2].type == KIND_CENTRALE &&
                        gameplay->world->map[y][x + 3].type == KIND_CENTRALE) {

                        gameplay->world->map[y][x].sprite = SPRITE_ENERGY_4X6;
                    }
                }


                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y][x - 3].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y][x - 4].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y][x - 5].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 3][x].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 1][x - 3].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 1][x - 4].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 1][x - 5].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 2][x - 3].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 2][x - 4].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 2][x - 5].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 3][x - 1].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 3][x - 2].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 3][x - 3].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 3][x - 4].sprite == SPRITE_ENERGY_6X4) ||
                    (gameplay->world->map[y - 3][x - 5].sprite == SPRITE_ENERGY_6X4)) {

                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;

                } else {
                    if (gameplay->world->map[y + 1][x].type == KIND_CENTRALE &&
                        gameplay->world->map[y + 2][x].type == KIND_CENTRALE
                        && gameplay->world->map[y + 3][x].type == KIND_CENTRALE &&
                        gameplay->world->map[y][x + 1].type == KIND_CENTRALE
                        && gameplay->world->map[y][x + 2].type == KIND_CENTRALE &&
                        gameplay->world->map[y][x + 3].type == KIND_CENTRALE
                        && gameplay->world->map[y][x + 4].type == KIND_CENTRALE &&
                        gameplay->world->map[y][x + 5].type == KIND_CENTRALE) {

                        gameplay->world->map[y][x].sprite = SPRITE_ENERGY_6X4;
                    }
                }

            }

            if (gameplay->world->map[y][x].type == KIND_CHATEAU) {

                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y][x - 3].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 3][x].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 4][x].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 5][x].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 1][x - 3].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 2][x - 3].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 3][x - 1].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 3][x - 2].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 3][x - 3].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 4][x - 1].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 4][x - 2].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 4][x - 3].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 5][x - 1].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 5][x - 2].sprite == SPRITE_EAU_4X6) ||
                    (gameplay->world->map[y - 5][x - 3].sprite == SPRITE_EAU_4X6)) {

                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;

                } else {
                    if (gameplay->world->map[y + 1][x].type == KIND_CHATEAU &&
                        gameplay->world->map[y + 2][x].type == KIND_CHATEAU
                        && gameplay->world->map[y + 3][x].type == KIND_CHATEAU &&
                        gameplay->world->map[y + 4][x].type == KIND_CHATEAU
                        && gameplay->world->map[y + 5][x].type == KIND_CHATEAU &&
                        gameplay->world->map[y][x + 1].type == KIND_CHATEAU
                        && gameplay->world->map[y][x + 2].type == KIND_CHATEAU &&
                        gameplay->world->map[y][x + 3].type == KIND_CHATEAU) {

                        gameplay->world->map[y][x].sprite = SPRITE_EAU_4X6;
                    }
                }


                if ((gameplay->world->map[y][x - 1].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y][x - 2].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y][x - 3].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y][x - 4].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y][x - 5].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 1][x].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 2][x].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 3][x].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 1][x - 1].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 1][x - 2].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 1][x - 3].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 1][x - 4].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 1][x - 5].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 2][x - 1].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 2][x - 2].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 2][x - 3].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 2][x - 4].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 2][x - 5].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 3][x - 1].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 3][x - 2].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 3][x - 3].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 3][x - 4].sprite == SPRITE_EAU_6X4) ||
                    (gameplay->world->map[y - 3][x - 5].sprite == SPRITE_EAU_6X4)) {
                    gameplay->world->map[y][x].sprite = SPRITE_VIDE;
                } else {
                    if (gameplay->world->map[y + 1][x].type == KIND_CHATEAU &&
                        gameplay->world->map[y + 2][x].type == KIND_CHATEAU
                        && gameplay->world->map[y + 3][x].type == KIND_CHATEAU &&
                        gameplay->world->map[y][x + 1].type == KIND_CHATEAU
                        && gameplay->world->map[y][x + 2].type == KIND_CHATEAU &&
                        gameplay->world->map[y][x + 3].type == KIND_CHATEAU
                        && gameplay->world->map[y][x + 4].type == KIND_CHATEAU &&
                        gameplay->world->map[y][x + 5].type == KIND_CHATEAU) {
                        gameplay->world->map[y][x].sprite = SPRITE_EAU_6X4;
                    }
                }
            }

        }
    }

    update_type_bloc_route(gameplay);

}

bool check_collision_placement(GameplayScreen_t *gameplay, int x, int y, int w, int h) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (y + j > SIM_MAP_HAUTEUR || x + i > SIM_MAP_LARGEUR) {
                return true; //Collision
            }
        }
    }

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (gameplay->world->map[y + j][x + i].type != KIND_VIDE) {
                return true; //Collision
            }
        }
    }
    return false; //absence de collision
}

bool check_route_near_placement(GameplayScreen_t *gameplay, int x, int y, int w, int h) {
    if (!gameplay->state.stateMouse.outOfMapBorders) {
        for (int i = 0; i < h; i++) {
            if (gameplay->world->map[y + i][x - 1].type == KIND_ROUTE ||
                gameplay->world->map[y + i][x + w].type == KIND_ROUTE) {
                return true;
            }
        }
        for (int i = 0; i < w; i++) {
            if (gameplay->world->map[y - 1][x + i].type == KIND_ROUTE ||
                gameplay->world->map[y + h][x + i].type == KIND_ROUTE) {
                return true; //on peut placer
            }
        }
    }
    return false; //on peut pas placer
}

void draw_placement_batiment(GameplayScreen_t *gameplay) {
    if (gameplay->state.stateToolbar.modePlacementHabitation) {
        DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                       gameplay->spriteSheet.sprites[SPRITE_TERRAIN_VAGUE_3X3].rectangle,
                       (Vector2) {iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                      gameplay->state.stateMouse.celluleIso.y}).x +
                                  gameplay->spriteSheet.sprites[SPRITE_TERRAIN_VAGUE_3X3].decalageXDecor,
                                  iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                      gameplay->state.stateMouse.celluleIso.y}).y +
                                  gameplay->spriteSheet.sprites[SPRITE_TERRAIN_VAGUE_3X3].decalageYDecor},
                       !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                  gameplay->state.stateMouse.celluleIso.y, 3, 3) &&
                       check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                  gameplay->state.stateMouse.celluleIso.y, 3, 3) ? GREEN : RED);

    }
    if (gameplay->state.stateToolbar.modePlacementChateau) {
        if (gameplay->state.stateToolbar.rotationChateau) {
            DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                           gameplay->spriteSheet.sprites[SPRITE_EAU_4X6].rectangle,
                           (Vector2) {iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                          gameplay->state.stateMouse.celluleIso.y}).x +
                                      gameplay->spriteSheet.sprites[SPRITE_EAU_4X6].decalageXDecor,
                                      iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                          gameplay->state.stateMouse.celluleIso.y}).y +
                                      gameplay->spriteSheet.sprites[SPRITE_EAU_4X6].decalageYDecor},
                           !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                      gameplay->state.stateMouse.celluleIso.y, 4, 6) &&
                           check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                      gameplay->state.stateMouse.celluleIso.y, 4, 6) ? GREEN : RED);


        } else {
            DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                           gameplay->spriteSheet.sprites[SPRITE_EAU_6X4].rectangle,
                           (Vector2) {iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                          gameplay->state.stateMouse.celluleIso.y}).x +
                                      gameplay->spriteSheet.sprites[SPRITE_EAU_6X4].decalageXDecor,
                                      iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                          gameplay->state.stateMouse.celluleIso.y}).y +
                                      gameplay->spriteSheet.sprites[SPRITE_EAU_6X4].decalageYDecor},
                           !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                      gameplay->state.stateMouse.celluleIso.y, 6, 4) &&
                           check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                      gameplay->state.stateMouse.celluleIso.y, 6, 4) ? GREEN : RED);
        }
    }

    if (gameplay->state.stateToolbar.modePlacementCentrale) {
        if (gameplay->state.stateToolbar.rotationCentraleElec) {
            DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                           gameplay->spriteSheet.sprites[SPRITE_ENERGY_4X6].rectangle,
                           (Vector2) {iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                          gameplay->state.stateMouse.celluleIso.y}).x +
                                      gameplay->spriteSheet.sprites[SPRITE_ENERGY_4X6].decalageXDecor,
                                      iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                          gameplay->state.stateMouse.celluleIso.y}).y +
                                      gameplay->spriteSheet.sprites[SPRITE_ENERGY_4X6].decalageYDecor},
                           !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                      gameplay->state.stateMouse.celluleIso.y, 4, 6) &&
                           check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                      gameplay->state.stateMouse.celluleIso.y, 4, 6) ? GREEN : RED);


        } else {
            DrawTextureRec(gameplay->spriteSheet.spriteSheetTexture,
                           gameplay->spriteSheet.sprites[SPRITE_ENERGY_6X4].rectangle,
                           (Vector2) {iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                          gameplay->state.stateMouse.celluleIso.y}).x +
                                      gameplay->spriteSheet.sprites[SPRITE_ENERGY_6X4].decalageXDecor,
                                      iso_to_screen(gameplay, (Vector2I) {gameplay->state.stateMouse.celluleIso.x,
                                                                          gameplay->state.stateMouse.celluleIso.y}).y +
                                      gameplay->spriteSheet.sprites[SPRITE_ENERGY_6X4].decalageYDecor},
                           !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                      gameplay->state.stateMouse.celluleIso.y, 6, 4) &&
                           check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                                      gameplay->state.stateMouse.celluleIso.y, 6, 4) ? GREEN : RED);
        }
    }
}

void update_word_placement_batiment(GameplayScreen_t *gameplay, int x, int y, int w, int h, CaseKind_t type, void* data) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            gameplay->world->map[y + i][x + j].type = type;
            gameplay->world->map[y + i][x + j].donnees = data;
        }
    }
}

void update_placement_batiment(GameplayScreen_t *gameplay) {
    if (gameplay->state.stateToolbar.modePlacementHabitation) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                       gameplay->state.stateMouse.celluleIso.y, 3, 3) &&
            check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                       gameplay->state.stateMouse.celluleIso.y, 3, 3) && gameplay->world->monnaie >= HABITATION_PRIX_CONSTRUCTION) {

            Habitation_t *habitation = habitation_alloc(NIVEAU_TERRAIN_VAGUE);
            habitation->position.x = gameplay->state.stateMouse.celluleIso.x;
            habitation->position.y = gameplay->state.stateMouse.celluleIso.y;
            habitation->orientation = ORIENTATION_NULL;
            update_word_placement_batiment(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 3, 3, KIND_TERRAIN_VAGUE, habitation);
            //liste_ajout_tri(gameplay->world->habitations, habitation, habitation_tri_par_distance);
            liste_ajouter_fin(gameplay->world->habitations, habitation);

            gameplay->world->monnaie -= HABITATION_PRIX_CONSTRUCTION;
            gameplay->reloadCarte = true;
            gameplay->state.stateToolbar.modePlacementHabitation = false;
        }
    }

    if (gameplay->state.stateToolbar.modePlacementCentrale) {
        if (IsKeyPressed(KEY_R)) {
            gameplay->state.stateToolbar.rotationCentraleElec = !gameplay->state.stateToolbar.rotationCentraleElec;
        }

        if (gameplay->state.stateToolbar.rotationCentraleElec) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 4, 6) &&
                check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 4, 6) && gameplay->world->monnaie >= CENTRALE_PRIX_CONSTRUCTION) {

                CentraleElectrique_t *centraleElectrique = centrale_alloc();
                centraleElectrique->position.x = gameplay->state.stateMouse.celluleIso.x;
                centraleElectrique->position.y = gameplay->state.stateMouse.celluleIso.y;
                centraleElectrique->orientation = ORIENTATION_4X6;

                update_word_placement_batiment(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                               gameplay->state.stateMouse.celluleIso.y, 4, 6, KIND_CENTRALE, centraleElectrique);
                liste_ajouter_fin(gameplay->world->centrales, centraleElectrique);

                gameplay->world->monnaie -= CENTRALE_PRIX_CONSTRUCTION;
                gameplay->reloadCarte = true;
                gameplay->state.stateToolbar.modePlacementCentrale = false;
            }
        } else {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 6, 4) &&
                check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 6, 4) && gameplay->world->monnaie >= CENTRALE_PRIX_CONSTRUCTION) {

                CentraleElectrique_t *centraleElectrique = centrale_alloc();
                centraleElectrique->position.x = gameplay->state.stateMouse.celluleIso.x;
                centraleElectrique->position.y = gameplay->state.stateMouse.celluleIso.y;
                centraleElectrique->orientation = ORIENTATION_6X4;
                update_word_placement_batiment(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                               gameplay->state.stateMouse.celluleIso.y, 6, 4, KIND_CENTRALE, centraleElectrique);
                liste_ajouter_fin(gameplay->world->centrales, centraleElectrique);
                gameplay->world->monnaie -= CENTRALE_PRIX_CONSTRUCTION;
                gameplay->reloadCarte = true;
                gameplay->state.stateToolbar.modePlacementCentrale = false;
            }
        }
    }

    if (gameplay->state.stateToolbar.modePlacementChateau) {
        if (IsKeyPressed(KEY_R)) {
            gameplay->state.stateToolbar.rotationChateau = !gameplay->state.stateToolbar.rotationChateau;
        }

        if (gameplay->state.stateToolbar.rotationChateau) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 4, 6) &&
                check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 4, 6) && gameplay->world->monnaie >= CHATEAU_PRIX_CONSTRUCTION) {

                ChateauEau_t *chateauEau = chateau_alloc();
                chateauEau->position.x = gameplay->state.stateMouse.celluleIso.x;
                chateauEau->position.y = gameplay->state.stateMouse.celluleIso.y;
                chateauEau->orientation = ORIENTATION_4X6;
                update_word_placement_batiment(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                               gameplay->state.stateMouse.celluleIso.y, 4, 6, KIND_CHATEAU, chateauEau);
                liste_ajouter_fin(gameplay->world->chateaux, chateauEau);
                ((ChateauEau_t*) gameplay->world->chateaux->dernier->data)->habitations = liste_alloc();
                gameplay->world->monnaie -= CHATEAU_PRIX_CONSTRUCTION;
                gameplay->reloadCarte = true;
                gameplay->state.stateToolbar.modePlacementChateau = false;
            }
        } else {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                !check_collision_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 6, 4) &&
                check_route_near_placement(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                           gameplay->state.stateMouse.celluleIso.y, 6, 4) && gameplay->world->monnaie >= CHATEAU_PRIX_CONSTRUCTION) {
                ChateauEau_t *chateauEau = chateau_alloc();
                chateauEau->position.x = gameplay->state.stateMouse.celluleIso.x;
                chateauEau->position.y = gameplay->state.stateMouse.celluleIso.y;
                chateauEau->orientation = ORIENTATION_6X4;
                update_word_placement_batiment(gameplay, gameplay->state.stateMouse.celluleIso.x,
                                               gameplay->state.stateMouse.celluleIso.y, 6, 4, KIND_CHATEAU, chateauEau);
                liste_ajouter_fin(gameplay->world->chateaux, chateauEau);
                ((ChateauEau_t*) gameplay->world->chateaux->dernier->data)->habitations = liste_alloc();
                gameplay->world->monnaie -= CHATEAU_PRIX_CONSTRUCTION;
                gameplay->reloadCarte = true;
                gameplay->state.stateToolbar.modePlacementChateau = false;
            }
        }
    }

    update_placement_route(gameplay);

}

void check_upadate_carte(GameplayScreen_t *gameplay) {
    if (gameplay->reloadCarte) {
        update_type_bloc_general(gameplay);
        bfs(gameplay);
        update_liste_bfs(gameplay);
        update_liste_habitation_triee_par_chateau(gameplay);
        gameplay->reloadCarte = false;
    }
}