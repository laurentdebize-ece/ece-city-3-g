#include "utils/grille.h"

Vector2I mouse_to_iso(Vector2I mouse) {
    return cartesien_to_iso((Vector2I) {
            mouse.x / LARGUEUR_TUILE_ISO,
            mouse.y / HAUTEUR_TUILE_ISO
    });
}

Vector2I cartesien_to_iso(Vector2I cartesien) {
    return (Vector2I) {
        .x = (cartesien.y - ISO_ORIGINE_Y) + (cartesien.x - ISO_ORIGINE_X),
        .y = (cartesien.y - ISO_ORIGINE_Y) - (cartesien.x - ISO_ORIGINE_X)
    };
}