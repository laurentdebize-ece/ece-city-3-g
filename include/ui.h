
#ifndef ECECITY_UI_H
#define ECECITY_UI_H

#include <raylib.h>
#include "sim/sim.h"


typedef enum BuildMode {
    BUILD_MODE_NONE,
    BUILD_MODE_ROUTE,
    BUILD_MODE_CENTRALE,
    BUILD_MODE_CHATEAU,
    BUILD_MODE_HABITATION,
    BUILD_MODE_CASERNE,
    BUILD_MODE_DESTROY,
} BuildMode;

/// Le mode de construction actuel.

enum TOOLBAR_ICON {
    ICON_HAMBURGER,
    ICON_SAVE,
    ICON_PEOPLE,
    ICON_ENERGY,
    ICON_WATER,
    ICON_BUILD,
    ICON_DESTROY,
    ICON_TIME,
    ICON_ROAD,
    ICON_HABITATION,
    ICON_CENTRALE,
    ICON_CHATEAU,
    ICON_CASERNE,
    ICON_DOLLAR,
    ICON_NB_LOGOS_TOOLBAR,
};


/// Contient l'état de l'interface utilisateur.
typedef struct UIState {
    Texture2D toolbarIcons[ICON_NB_LOGOS_TOOLBAR];
    /// Mode de construction actuel
    enum BuildMode currentBuildMode;
    /// Multiplicateur de vitesse de jeu
    float timeScale;
} UIState;

void ui_charger_textures(UIState* textures);

void ui_draw_toolbar(UIState* textures, SimWorld_t* sim);

void ui_update_toolbar(UIState* textures, SimWorld_t* sim);

CaseKind_t ui_buildmode_to_casekind(BuildMode mode);

#endif //ECECITY_UI_H
