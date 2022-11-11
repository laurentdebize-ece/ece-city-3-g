
#include "sim/habitation.h"

/// Crée une habitation.
Habitation_t* habitation_alloc(NiveauHabitation_t niveau) {
    Habitation_t* habitation = malloc(sizeof (Habitation_t));
    habitation->niveau = niveau;
    habitation->update_ticks = 0;
}

/// Détruit une habitation.
void habitation_free(Habitation_t* habitation) {
    free(habitation);
}

/// Incrémente d'un tick la simulation d'un bâtiment.
/// Renvoie si le bâtiment a évolué / régréssé.
void habitation_step(Habitation_t* habitation, SimRules_t rules) {
    habitation->update_ticks++;
    habitation_evolve(habitation);
}

void habitation_evolve(Habitation_t* habitation) {
    if (habitation->update_ticks >= N_TICKS_EVOLUTION) {
        habitation->update_ticks = 0;
        switch (habitation->niveau) {
            case NIVEAU_TERRAIN_VAGUE:
                habitation->niveau = NIVEAU_CABANE;
                break;
            case NIVEAU_CABANE:
                habitation->niveau = NIVEAU_MAISON;
                break;
            case NIVEAU_MAISON:
                habitation->niveau = NIVEAU_IMMEUBLE;
                break;
            case NIVEAU_IMMEUBLE:
                habitation->niveau = NIVEAU_GRATTE_CIEL;
                break;
            default:
                break;
        }
    }
}

int habitation_cmp(Habitation_t* habitation1, Habitation_t* habitation2) {
    return habitation1->niveau - habitation2->niveau;
}

int habitation_tri_par_distance(Habitation_t* a, Habitation_t* b)
{
    Habitation_t *hab_a = (Habitation_t *) a;
    Habitation_t *hab_b = (Habitation_t *) b;
    if (hab_a->position.x < hab_b->position.x) {
        return -1;
    } else if (hab_a->position.x > hab_b->position.x) {
        return 1;
    } else {
        if (hab_a->position.y < hab_b->position.y) {
            return -1;
        } else if (hab_a->position.y > hab_b->position.y) {
            return 1;
        } else {
            return 0;
        }
    }
}