
#ifndef ECECITY_AFFICHAGE_H
#define ECECITY_AFFICHAGE_H

#include <raylib.h>
#include "sim/sim.h"
#include "spritesheet.h"
#include "screens/gameplay.h"

/// Enumère les composants du jeu à dessiner.
enum RenderLayer {
    LAYER_HABITATIONS = 1 << 0,
    LAYER_CENTRALES = 1 << 1,
    LAYER_CHATEAUX = 1 << 2,
    LAYER_ROUTES = 1 << 3,
    LAYER_RESEAU_ELECTRIQUE = LAYER_HABITATIONS | LAYER_CENTRALES,
    LAYER_CANALISATIONS_EAU = LAYER_HABITATIONS | LAYER_CHATEAUX,
    LAYER_ALL = LAYER_HABITATIONS | LAYER_CENTRALES | LAYER_CHATEAUX
};

/// Dessine le fond de la carte.
//void affichage_draw_terrain_background(SpriteSheet_t* sheet, SimWorld_t* world);
void affichage_draw_terrain_background(GameplayScreen_t *gameplay);


struct Buffer {
    Vector2 position;
    int typeBloc;
};


/// Dessine les tuiles de la carte.
//void affichage_draw_entities(SpriteSheet_t* sheet, SimWorld_t* world, enum RenderLayer layers);
void affichage_draw_entities(GameplayScreen_t* gameplay, struct Buffer *buffer, int nbBuffer);

void draw_hover(GameplayScreen_t* gameplay);

void draw_map(GameplayScreen_t *gameplay);

/// Dessine une habitation sur la carte.
void affichage_draw_habitation(SpriteSheet_t* sheet, Habitation_t* habitation, Color teinte);

/// Dessine l'apercu de construction d'un bâtiment sur la carte.
void affichage_draw_build_preview(SpriteSheet_t* sheet, SimWorld_t* world, Vector2I pos, CaseKind_t type);

/// Dessine l'apercu de construction d'un bâtiment sur la carte.
void affichage_draw_build_preview(SpriteSheet_t* sheet, SimWorld_t* world, Vector2I pos, CaseKind_t type);

#endif //ECECITY_AFFICHAGE_H
