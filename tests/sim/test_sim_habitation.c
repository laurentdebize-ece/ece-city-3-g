
#include <assert.h>
#include <stdio.h>
#include "sim/habitation.h"

int main() {
    Habitation_t* habitation = habitation_alloc(TERRAIN_VAGUE);

    // test simulation avec conditions d'eau et d'electricité remplies.
    printf("--------Création d'un terrain vague + sim 60 ticks (eau, elec)--------\n\r", habitation->niveau);

    for (int i = 0; i < 15; ++i) {
        habitation->eau = habitation_get_nb_habitants(habitation);
        habitation->electricite = habitation_get_nb_habitants(habitation);

        assert(habitation->niveau == TERRAIN_VAGUE);
        habitation_step(habitation, Communiste_t);

        // vérifier que les flots sont réinitialisés après simulation du bâtiment
        assert(habitation->eau == -1);
        assert(habitation->electricite == -1);
    }

    printf("Niveau atteint: %d (CABANE)\n\r", habitation->niveau);
    assert(habitation->niveau == CABANE);

    for (int i = 0; i < 45; ++i) {
        habitation->eau = habitation_get_nb_habitants(habitation);
        habitation->electricite = habitation_get_nb_habitants(habitation);
        habitation_step(habitation, Communiste_t);
    }
    assert(habitation->niveau == GRATTE_CIEL);
    printf("Niveau atteint: %d (GRATTE_CIEL)\n\r", habitation->niveau);

    printf("--------GRATTE_CIEL en sous alimentation d'eau et d'électricité après 90 ticks--------\n\r");
    for (int i = 0; i < 75; ++i) {
        habitation->eau = 10;
        habitation->electricite = habitation_get_nb_habitants(habitation) + 1;

        habitation_step(habitation, Communiste_t);
    }
    printf("Niveau atteint: %d (CABANE)\n\r", habitation->niveau);
    assert(habitation->niveau == CABANE);

    printf("--------CABANE en sous alimentation d'eau et d'électricité après 15 ticks--------\n\r");

    for (int i = 0; i < 15; ++i)
        habitation_step(habitation, Communiste_t);

    printf("Niveau atteint: %d (RUINE)\n\r", habitation->niveau);
    assert(habitation->niveau == RUINE);

    return 0;
}