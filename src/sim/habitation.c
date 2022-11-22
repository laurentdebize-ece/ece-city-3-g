
#include <stdio.h>
#include "sim/habitation.h"

NiveauHabitation_t habitation_level_up(NiveauHabitation_t lvl, bool alimentee);
NiveauHabitation_t habitation_level_down(NiveauHabitation_t lvl, bool alimentee);

/// Crée une habitation.
Habitation_t *habitation_alloc(NiveauHabitation_t niveau) {
    Habitation_t *habitation = malloc(sizeof(Habitation_t));
    habitation->niveau = niveau;
    habitation->update_ticks = 0;
    habitation->alimentee_en_eau = false;
    habitation->alimentee_en_electricite = false;
    habitation->eau = 0;
    habitation->electricite = 0;
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
        habitation_evolve(habitation, rules);
        return habitation_get_nb_habitants(habitation) * IMPOT_PAR_HABITANT;
    }

    return 0;
}

int habitation_get_nb_habitants(Habitation_t* habitation) {
    switch (habitation->niveau) {
        case NIVEAU_CABANE:
        case NIVEAU_CABANE_CAP:
            return 10;
        case NIVEAU_MAISON:
        case NIVEAU_MAISON_CAP:
            return 50;
        case NIVEAU_IMMEUBLE:
        case NIVEAU_IMMEUBLE_CAP:
            return 100;
        case NIVEAU_GRATTE_CIEL:
            return 1000;
        default:
            return 0;
    }
}

int habitation_get_required_water(Habitation_t* habitation, SimRules_t rules) {
        return habitation_get_nb_habitants(habitation);
}

int habitation_get_remaining_required_water(Habitation_t* habitation, SimRules_t rules) {
    return habitation_get_required_water(habitation, rules) - habitation->eau;
}

int habitation_get_required_energy(Habitation_t* habitation, SimRules_t rules) {
    return habitation_get_nb_habitants(habitation);
}

int habitation_get_remaining_required_energy(Habitation_t* habitation, SimRules_t rules) {
    return habitation_get_required_energy(habitation, rules) - habitation->electricite;
}

void habitation_evolve(Habitation_t *habitation, SimRules_t rules) {
    bool alimentee = habitation->alimentee_en_eau && habitation->alimentee_en_electricite;
    if (rules == Capitaliste_t) {
        if (habitation->niveau >= NIVEAU_TERRAIN_VAGUE_CAP && habitation->niveau <= NIVEAU_IMMEUBLE_CAP)
        {
            if (alimentee)
                habitation->niveau = habitation_level_up(habitation->niveau, alimentee);
            else
                habitation->niveau = habitation_level_down(habitation->niveau, alimentee);
        } else {
            if (habitation->eau == habitation_get_required_water(habitation, rules) && habitation->electricite == habitation_get_required_energy(habitation, rules) && alimentee)
                habitation->niveau = habitation_level_up(habitation->niveau, alimentee);
            else
                habitation->niveau = habitation_level_down(habitation->niveau, alimentee);
        }
    } else {
        if (alimentee)
            habitation->niveau = habitation_level_up(habitation->niveau, alimentee);
        else
            habitation->niveau = habitation_level_down(habitation->niveau, alimentee);
    }
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

NiveauHabitation_t habitation_level_up(NiveauHabitation_t lvl, bool alimentee) {
    switch (lvl) {
        case NIVEAU_TERRAIN_VAGUE:
            return NIVEAU_CABANE;
        case NIVEAU_CABANE:
            return NIVEAU_MAISON;
        case NIVEAU_MAISON:
            return NIVEAU_IMMEUBLE;
        case NIVEAU_IMMEUBLE:
            return NIVEAU_GRATTE_CIEL;
        case NIVEAU_RUINE:
            return NIVEAU_CABANE;
        case NIVEAU_MAISON_CAP:
            return NIVEAU_IMMEUBLE_CAP;
        case NIVEAU_TERRAIN_VAGUE_CAP:
            return NIVEAU_CABANE_CAP;
        case NIVEAU_CABANE_CAP:
            return NIVEAU_MAISON_CAP;
        case NIVEAU_IMMEUBLE_CAP:
            return NIVEAU_GRATTE_CIEL; /// on repasse l'immeuble en mode de dev normal.
        default:
            return lvl;
    }
}

NiveauHabitation_t habitation_level_down(NiveauHabitation_t lvl, bool alimentee) {
    switch (lvl) {
        case NIVEAU_CABANE:
            return NIVEAU_RUINE;
        case NIVEAU_MAISON:
            return NIVEAU_CABANE;
        case NIVEAU_IMMEUBLE:
            return NIVEAU_MAISON;
        case NIVEAU_GRATTE_CIEL:
            return NIVEAU_IMMEUBLE;
        case NIVEAU_CABANE_CAP:
            return NIVEAU_RUINE;
        case NIVEAU_IMMEUBLE_CAP:
            return NIVEAU_MAISON;
        case NIVEAU_MAISON_CAP:
            return NIVEAU_CABANE;
        default:
            return lvl;
    }
}