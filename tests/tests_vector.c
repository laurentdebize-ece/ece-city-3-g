#include "utils/vector.h"
#include <assert.h>

int main() {
    Vector_t* vec = vector_alloc(10);
    assert(vec->capacite == 10);

    vector_push(vec, (void*) 1);
    assert(vec->taille == 1);

    vector_push(vec, (void*) 2);
    vector_push(vec, (void*) 3);
    assert(vec->taille == 3);

    assert(vector_pop(vec) == 3);
    assert(vec->taille == 2);

    assert(vector_pop(vec) == 2);
    assert(vec->taille == 1);

    assert(vector_pop(vec) == 1);
    assert(vec->taille == 0);

    return 0;
}