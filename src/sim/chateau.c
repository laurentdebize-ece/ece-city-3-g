#include "sim/chateau.h"
#include "bfs.h"

ChateauEau_t* chateau_alloc() {
    ChateauEau_t* chateau = malloc(sizeof(ChateauEau_t));
    chateau->capacite = CAPACITE_CHATEAU_EAU;
    chateau->habitations = vector_alloc(10);
    return chateau;
}

void chateau_free(ChateauEau_t* chateau) {
    free(chateau);
}

int chateau_dispense(ChateauEau_t* chateau, int quantite) {
    int dispensed = MIN(chateau->capacite, quantite);
    chateau->capacite -= dispensed;
    return dispensed;
}

void chateau_step(ChateauEau_t* chateau, SimRules_t rules) {
    chateau->capacite = CAPACITE_CHATEAU_EAU;

    // prépasse pour déterminer le mode de distribution (plus proche vs minimisation des pertes d'habitants)
    int demande = 0;
    vector_sort(chateau->habitations, trier_noeux_habitations_par_distance);
    for (int i = 0; i < chateau->habitations->taille; ++i)
        demande += habitation_get_remaining_required_water(((HabitationNode_t*)chateau->habitations->data[i])->habitation, rules);

    if (demande > CAPACITE_CHATEAU_EAU)
        vector_sort(chateau->habitations, trier_noeux_habitations_par_niveau);

    /// distribution de l'eau.
    for (int i = 0; i < chateau->habitations->taille; ++i) {
        HabitationNode_t* habitation = chateau->habitations->data[i];
        habitation->habitation->eau += chateau_dispense(chateau, habitation_get_remaining_required_water(habitation->habitation, rules));
    }
}
