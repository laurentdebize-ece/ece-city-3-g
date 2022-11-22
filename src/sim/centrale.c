
#include "sim/centrale.h"
#include "bfs.h"

/// Crée une centrale électrique.
CentraleElectrique_t* centrale_alloc() {
    CentraleElectrique_t* centrale = malloc(sizeof(CentraleElectrique_t));
    centrale->capacite = CAPACITE_CENTRALE_ELECTRIQUE;
    centrale->habitations = vector_alloc(10);
    return centrale;
}

/// Détruit une centrale électrique.
void centrale_free(CentraleElectrique_t* centrale) {
    free(centrale);
}

/// Incrémente d'un tick la simulation d'une centrale électrique.
void centrale_step(CentraleElectrique_t* centrale, SimRules_t rules) {
    centrale->capacite = CAPACITE_CENTRALE_ELECTRIQUE;

    // prépasse pour déterminer le mode de distribution (plus proche vs minimisation des pertes d'habitants)
    int demande = 0;
    vector_sort(centrale->habitations, trier_noeux_habitations_par_distance);
    for (int i = 0; i < centrale->habitations->taille; ++i)
        demande += habitation_get_remaining_required_water(((HabitationNode_t*)centrale->habitations->data[i])->habitation, rules);

    if (demande > CAPACITE_CENTRALE_ELECTRIQUE)
        vector_sort(centrale->habitations, trier_noeux_habitations_par_niveau);

    /// distribution de l'elec
    for (int i = 0; i < centrale->habitations->taille; ++i) {
        HabitationNode_t* habitation = centrale->habitations->data[i];
        habitation->habitation->electricite += centrale_dispense(centrale, habitation_get_remaining_required_energy(habitation->habitation, rules));
    }
}

int centrale_dispense(CentraleElectrique_t* centrale, int quantite) {
    if (centrale->capacite >= quantite) {
        centrale->capacite -= quantite;
        return quantite;
    } else
        return 0;
}
