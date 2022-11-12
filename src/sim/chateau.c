#include "sim/chateau.h"

ChateauEau_t* chateau_alloc() {
    ChateauEau_t* chateau = malloc(sizeof(ChateauEau_t));
    chateau->capacite = CAPACITE_CHATEAU_EAU;
    return chateau;
}

void chateau_free(ChateauEau_t* chateau) {
    free(chateau);
}

Vector2 get_chateau_position(ChateauEau_t* chateau){
    return chateau->position;
}

void chateau_step(ChateauEau_t* chateau) {
    chateau->capacite = CAPACITE_CHATEAU_EAU;
}
