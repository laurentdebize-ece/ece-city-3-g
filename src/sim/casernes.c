#include "sim/casernes.h"

CasernePompier_t* alloc_caserne(){
    CasernePompier_t* caserne = malloc(sizeof(CasernePompier_t));
    caserne->habitations = liste_alloc();
    return caserne;
}

void caserne_free(CasernePompier_t* caserne) {
    free(caserne);
}
