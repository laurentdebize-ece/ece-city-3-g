
#include "utils/vector.h"


/// Crée un tableau dynamique.
Vector_t* vector_alloc(size_t initialCap) {
    Vector_t *vector = malloc(sizeof(Vector_t));
    vector->data = malloc(initialCap * sizeof(void*));
    vector->taille = 0;
    vector->capacite = initialCap;
    return vector;
}

/// Détruit un tableau dynamique.
void vector_free(Vector_t* vector) {
    free(vector->data);
    free(vector);
}

/// Ajoute un élément à la fin du tableau dynamique.
void vector_push(Vector_t* vector, void* data) {
    if (vector->taille == vector->capacite) {
        vector->capacite *= 2;
        vector->data = realloc(vector->data, vector->capacite * sizeof(void*));
    }
    vector->data[vector->taille] = data;
    vector->taille++;
}

/// Supprime un élément à la fin du tableau dynamique.
void* vector_pop(Vector_t* vector) {
    if (vector->taille == 0)
        return NULL;

    vector->taille--;
    return vector->data[vector->taille];
}

/// Retourne l'élément à l'index donné.
void* vector_get(Vector_t* vector, size_t index) {
    if (index >= vector->taille)
        return NULL;

    return vector->data[index];
}

/// Fixe l'élément à l'index donné.
void vector_set(Vector_t* vector, size_t index, void* data) {
    if (index >= vector->taille)
        return;

    vector->data[index] = data;
}
