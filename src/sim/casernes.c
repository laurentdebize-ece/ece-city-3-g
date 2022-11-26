#include "sim/casernes.h"

CasernePompier_t* alloc_caserne(){
    CasernePompier_t* caserne = malloc(sizeof(CasernePompier_t));
    caserne->habitations = vector_alloc(10);
    return caserne;
}

void draw_enfeu(SimWorld_t *world, SpriteSheet_t* sheet){
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        if(hab->enfeu == true){
            DrawTexture(sheet->spriteFeu, (ORIGINEX * SPRITELARGEUR) + hab->position.x * (SPRITELARGEUR / 2) -
                                                                 hab->position.y * (SPRITELARGEUR / 2), (ORIGINEY * SPRITEHAUTEUR) + hab->position.y * (SPRITEHAUTEUR / 2) +
                                                                                                        hab->position.x * (SPRITEHAUTEUR / 2) - 10, WHITE);
        }
        maison = maison->next;
    }
}

void caserne_free(CasernePompier_t* caserne) {
    free(caserne);
}

