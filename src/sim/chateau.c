#include "sim/chateau.h"

ChateauEau_t* chateau_alloc() {
    ChateauEau_t* chateau = malloc(sizeof(ChateauEau_t));
    chateau->capacite = CAPACITE_CHATEAU_EAU;
    chateau->habitations = liste_alloc();
    return chateau;
}

void chateau_free(ChateauEau_t* chateau) {
    free(chateau);
}

void chateau_step(ChateauEau_t* chateau) {
    chateau->capacite = CAPACITE_CHATEAU_EAU;
}
