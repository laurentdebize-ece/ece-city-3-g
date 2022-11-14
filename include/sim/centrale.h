
#ifndef ECECITY_CENTRALE_H
#define ECECITY_CENTRALE_H

#include <stdlib.h>
#include <stdbool.h>
#include <utils/grille.h>

#define CENTRALE_PRIX_CONSTRUCTION 100000
#define CAPACITE_CENTRALE_ELECTRIQUE 5000

typedef enum ElecConnectionState_t {
    NOT_CONNECTED = -1, // n'est pas reliée au réseau électrique
    POWERED, // est reliée au réseau électrique alimentée,
    UNPOWERED // est reliée au réseau électrique mais n'est pas alimentée
} ElecConnectionState_t;


/// Représente une centrale électrique simulée.
typedef struct CentraleE_t {
    /// Flot d'électricité disponible pour la centrale.
    /// Réinitialisé à chaque début de tick de simulation.
    int capacite;

    Vector2I position;
} CentraleElectrique_t;

/// Crée une centrale électrique.
CentraleElectrique_t* centrale_alloc();

/// Détruit une centrale électrique.
void centrale_free(CentraleElectrique_t* centrale);

/// Réinitialise la capacité de la centrale.
/// A appeler au début de chaque tick de simulation.
void centrale_step(CentraleElectrique_t* centrale);

/// Tente de délivrer de l'électricité à une habitation, si la centrale peut encore alimenter l'habitation.
bool centrale_deliver_power(CentraleElectrique_t* centrale, int qte);


#endif //ECECITY_CENTRALE_H
