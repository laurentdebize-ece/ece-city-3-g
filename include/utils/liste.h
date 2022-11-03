
#ifndef ECECITY_LISTE_H
#define ECECITY_LISTE_H

#include <stdlib.h>
#include <stdbool.h>

struct Maillon_t {
    void *data;
    struct Maillon_t *next;
    struct Maillon_t *prev;
};

/// Une liste doublement chainée générique
typedef struct Liste_t {
    /// pointeur sur le premier maillon
    struct Maillon_t *premier;
    /// pointeur sur le dernier maillon
    struct Maillon_t *dernier;
    /// nombre d'éléments dans la liste
    int taille;
} Liste_t;


/// Crée une liste vide.
Liste_t* liste_alloc();

/// Détruit une liste.
void liste_free(Liste_t* liste);

/// Regarde si la liste est vide.
bool liste_estVide(Liste_t *liste);

/// Ajoute un élément à la fin de la liste.
void liste_ajouter_fin(Liste_t *liste, void *data);

/// Supprime un élément en fin de liste et le retourne.
void* liste_supprimer_fin(Liste_t *liste);

/// Ajoute un élément en début de liste.
void liste_ajouter_debut(Liste_t *liste, void *data);

/// Supprime un élément en début de liste et le retourne.
void* liste_supprimer_debut(Liste_t *liste);



#endif //ECECITY_LISTE_H
