
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
    ICON_GRID,
    ICON_WATER_GRID,
    ICON_ELECTRICITY_GRID,
    ICON_CHECK,
    ICON_CANCEL,
    ICON_ADD,
    ICON_DOLLAR,
    ICON_NB_LOGOS_TOOLBAR
};

typedef struct {
    bool hoverAdd;
    bool hoverSel;
    bool hoverCancel;
    bool hoverComponent;
    bool select_component;
    int num_component_hover;
    int num_component_select;
    bool clickAdd;
    bool modeAjout;
    bool clickSel;
    bool clickCancel;
    char nomFichier[10];
    char nomFichierOuverture[10];
    int indice;
    bool resetNbSauvegardes;
} StateMenuSave_t;

typedef struct StateToolbar_t {
    bool hoverNiveauEau;
    bool hoverNiveauElectricite;
    bool hoverNiveauNormal;
    bool niveauEau;
    bool niveauElectricite;
    bool niveauNormal;
    bool hoverChangementNiveau;
    bool modeChangementNiveau;
    bool hoverMenu;
    bool modeMenu;
    bool hoverSave;
    bool modeSave;
    StateMenuSave_t stateMenuSave;
    bool hoverRoute;
    bool modePlacementRoute;
    bool rotationRoute;
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
    /// Multiplicateur de vitesse de jeu
    float timeScale;
    /// Informations sur l'état de la toolbar.
    StateToolbar_t stateToolbar;
} UIState;

void ui_charger_textures(UIState* textures);

void ui_draw_toolbar(UIState* textures, SimWorld_t* sim);

void ui_update_toolbar(UIState* textures, SimWorld_t* sim);

CaseKind_t ui_buildmode_to_casekind(BuildMode mode);

#endif //ECECITY_UI_H
