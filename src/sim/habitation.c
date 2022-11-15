
#include "sim/habitation.h"

/// Crée une habitation.
Habitation_t *habitation_alloc(NiveauHabitation_t niveau) {
    Habitation_t *habitation = malloc(sizeof(Habitation_t));
    habitation->niveau = niveau;
    habitation->update_ticks = 0;
    habitation->dst = 0;
}

/// Détruit une habitation.
void habitation_free(Habitation_t *habitation) {
    free(habitation);
}

/// Incrémente d'un tick la simulation d'un bâtiment.
int habitation_step(Habitation_t *habitation, SimRules_t rules) {
    habitation->update_ticks++;

    if (habitation->update_ticks >= N_TICKS_EVOLUTION) {
        habitation->update_ticks = 0;
        habitation_evolve(habitation);
        return habitation_get_nb_habitants(habitation) * IMPOT_PAR_HABITANT;
    }

    return 0;
}

int habitation_get_nb_habitants(Habitation_t* habitation) {
    switch (habitation->niveau) {
        case NIVEAU_CABANE:
            return 10;
        case NIVEAU_MAISON:
            return 50;
        case NIVEAU_IMMEUBLE:
            return 100;
        case NIVEAU_GRATTE_CIEL:
            return 1000;
        default:
            return 0;
    }
}

void habitation_evolve(Habitation_t *habitation) {
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

int habitation_cmp(Habitation_t *habitation1, Habitation_t *habitation2) {
    return habitation1->niveau - habitation2->niveau;
}

int habitation_tri_par_distance(Habitation_t *a, Habitation_t *b) {
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