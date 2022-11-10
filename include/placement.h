#ifndef ECECITY_PLACEMENT_H
#define ECECITY_PLACEMENT_H

#include "screens/gameplay.h"


bool check_collision_batiment(GameplayScreen_t *gameplay);

CaseSprite_t update_type_route(Vector2I *chemin, int cheminActuel);

void draw_route_selectionee(GameplayScreen_t *gameplay);

void update_chemin_route(GameplayScreen_t *gameplay);

void update_placement_route(GameplayScreen_t *gameplay);

void check_changement_cellule_placement_route(GameplayScreen_t *gameplay);

void update_type_bloc_route(GameplayScreen_t *gameplay);

void update_type_bloc_general(GameplayScreen_t *gameplay);

bool check_collision_placement(GameplayScreen_t *gameplay, int x, int y, int w, int h);

bool check_route_near_placement(GameplayScreen_t *gameplay, int x, int y, int w, int h);

void draw_placement_batiment(GameplayScreen_t *gameplay);

void update_word_placement_batiment(GameplayScreen_t *gameplay, int x, int y, int w, int h, CaseKind_t type);

void update_placement_batiment(GameplayScreen_t *gameplay);

void check_upadate_carte(GameplayScreen_t *gameplay);

void printMatrice(GameplayScreen_t* gameplay);

#endif
