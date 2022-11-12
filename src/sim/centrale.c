#include "sim/centrale.h"

/// Crée une centrale électrique.
CentraleElectrique_t* centrale_alloc() {
    CentraleElectrique_t* centrale = malloc(sizeof(CentraleElectrique_t));
    centrale->capacite = CAPACITE_CENTRALE_ELECTRIQUE;
    return centrale;
}

/// Détruit une centrale électrique.
void centrale_free(CentraleElectrique_t* centrale) {
    free(centrale);
}

/// Incrémente d'un tick la simulation d'une centrale électrique.
void centrale_step(CentraleElectrique_t* centrale) {
    centrale->capacite = CAPACITE_CENTRALE_ELECTRIQUE;
}

Vector2 get_centrale_position(CentraleElectrique_t* centrale){
    return centrale->position;
}

/// Tente de délivrer de l'électricité à une habitation, si la centrale peut encore alimenter l'habitation.
/// Retourne si la centrale a pu délivrer l'électricité demandée.
bool centrale_deliver_power(CentraleElectrique_t* centrale, int qte) {
    if (centrale->capacite >= qte) {
        centrale->capacite -= qte;
        return true;
    }
    return false;
}

