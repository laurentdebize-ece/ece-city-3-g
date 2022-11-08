
#include "sim/habitation.h"

/// Crée une habitation.
Habitation_t* habitation_alloc(NiveauHabitation_t niveau) {
    Habitation_t* habitation = malloc(sizeof (Habitation_t));
    habitation->niveau = niveau;
    habitation->ticks_evolution = 0;
    habitation->ticks_regression = 0;
}

/// Détruit une habitation.
void habitation_free(Habitation_t* habitation) {
    free(habitation);
}

/// Incrémente d'un tick la simulation d'un bâtiment.
/// Renvoie si le bâtiment a évolué / régréssé.
void habitation_step(Habitation_t* habitation, SimRules_t rules) {

    // règles
    if (rules == Communiste_t) {
        // l'habitation remplit les conditions d'évolution en eau et en électricité.
        if (habitation->eau >= habitation_get_nb_habitants(habitation)
            && habitation->electricite >= habitation_get_nb_habitants(habitation)) {
            habitation->ticks_evolution++;
            habitation->ticks_regression = 0;
        } else {
            habitation->ticks_evolution = 0;
            habitation->ticks_regression++;
        }
    }
    else
    {
        //TODO: règles d'évolution capitalistes.
        habitation->ticks_evolution++;
    }

    // on reset les flots d'eau et d'électricité.
    habitation->eau = -1;
    habitation->electricite = -1;

    habitation_evolve(habitation);
}

void habitation_evolve(Habitation_t* habitation) {
    if (habitation->ticks_evolution >= N_TICKS_EVOLUTION) {
        habitation->ticks_evolution = 0;
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
    } else if (habitation->ticks_regression >= N_TICKS_REGRESSION) {
        habitation->ticks_regression = 0;
        switch (habitation->niveau) {
            case NIVEAU_CABANE:
                habitation->niveau = NIVEAU_RUINE;
                break;
            case NIVEAU_MAISON:
                habitation->niveau = NIVEAU_CABANE;
                break;
            case NIVEAU_IMMEUBLE:
                habitation->niveau = NIVEAU_MAISON;
                break;
            case NIVEAU_GRATTE_CIEL:
                habitation->niveau = NIVEAU_IMMEUBLE;
                break;
                //case NIVEAU_RUINE:
                //case NIVEAU_TERRAIN_VAGUE:
            default:
                break;
        }
    }
}

/// Renvoie le nombre d'habitants dans l'habitation.
int habitation_get_nb_habitants(Habitation_t* habitation) {
    return (int)habitation->niveau;
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