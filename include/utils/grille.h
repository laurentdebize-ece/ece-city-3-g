#ifndef ECECITY_GRILLE_H
#define ECECITY_GRILLE_H

#define LARGUEUR_TUILE_ISO 40
#define HAUTEUR_TUILE_ISO 20

#define ISO_ORIGINE_X 17
#define ISO_ORIGINE_Y 3

#include "raylib.h"
#include "screens/gameplay.h"

Vector2 iso_to_screen(GameplayScreen_t *gameplay, Vector2I position);

void update_state_mouse(GameplayScreen_t *gameplay);


/// Convertit les coordonnées de la souris en coordonnées isométriques à l'aide d'une image de référence.
Vector2I mouse_to_iso(Vector2I mouse, Image refImg);

/// Convertit les coordonnées cartésiennes en coordonnées isométriques.
Vector2I cartesien_to_iso(Vector2I cartesien);

#endif //ECECITY_GRILLE_H
