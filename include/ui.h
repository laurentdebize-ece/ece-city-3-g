#ifndef ECECITY_UI_H
#define ECECITY_UI_H

#include <raylib.h>
#include "sim/sim.h"

typedef struct Vector2I {
    int x;
    int y;
} Vector2I;


typedef enum BuildMode {
    BUILD_MODE_NONE,
    BUILD_MODE_ROUTE,
    BUILD_MODE_CENTRALE,
    BUILD_MODE_CHATEAU,
    BUILD_MODE_HABITATION
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
    ICON_DOLLAR,
    ICON_NB_LOGOS_TOOLBAR
};

typedef struct StateMouse_t {
    Vector2I offsetCellule;
    Vector2I celluleXY;
    Vector2I celluleIso;
    bool outOfMapBorders;
    bool boolChangementDeCelluleIso;
} StateMouse_t;

typedef struct StateBuildRoad_t {
    Vector2I depart[2];
    int nbDepart;
    Vector2I cheminRoute[100];
    int nbChemins;
} StateBuildRoad_t;

typedef struct StateToolbar_t {
    bool hoverMenu;
    bool modeMenu;
    bool hoverSave;
    bool modeSave;
    bool hoverRoute;
    bool modePlacementRoute;
    bool rotationRoute;
    StateBuildRoad_t stateBuildRoad;
    bool hoverHabitation;
    bool modePlacementHabitation;
    bool hoverCentrale;
    bool modePlacementCentrale;
    bool rotationCentraleElec;
    bool hoverChateau;
    bool modePlacementChateau;
    bool rotationChateau;
    bool hoverDestruction;
    bool modeDestruction;
} StateToolbar_t;


/// Contient l'état de l'interface utilisateur.
typedef struct UIState {
    Texture2D toolbarIcons[ICON_NB_LOGOS_TOOLBAR];
    /// Mode de construction actuel
    enum BuildMode currentBuildMode;
    /// Informations sur la position actuelle de la souris.
    StateMouse_t stateMouse;
    /// Informations sur l'état de la toolbar.
    StateToolbar_t stateToolbar;
} UIState;

void ui_charger_textures(UIState* textures);

void ui_draw_toolbar(UIState* textures, SimWorld_t* sim);

void ui_update_toolbar(UIState* textures, SimWorld_t* sim);

#endif //ECECITY_UI_H
