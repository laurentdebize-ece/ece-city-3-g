#include "sim/chateau.h"
#include "sim/sim.h"
#include "affichage.h"
#include "screens/gameplay.h"


///afficher les capacités des centrales et chateaux

void afficher_capacite(SimWorld_t* world) {
    struct Maillon_t* centrales = world->centrales->premier;
    while (centrales) {
        CentraleElectrique_t* centraleElectrique = (CentraleElectrique_t*)centrales->data;
        DrawText(TextFormat("%d/5000", centraleElectrique->capacite), (ORIGINEX * SPRITELARGEUR) + centraleElectrique->position.x * (SPRITELARGEUR/2) - centraleElectrique->position.y * (SPRITELARGEUR/2), (ORIGINEY * SPRITEHAUTEUR) + centraleElectrique->position.y * (SPRITEHAUTEUR/2) + centraleElectrique->position.x * (SPRITEHAUTEUR/2), 20, WHITE);
        centrales = centrales->next;
    }
    struct Maillon_t* chateaux = world->chateaux->premier;
    while(chateaux){
        ChateauEau_t* chateauEau = (ChateauEau_t*)chateaux->data;
        DrawText(TextFormat("%d/5000", chateauEau->capacite), (ORIGINEX * SPRITELARGEUR) + chateauEau->position.x * (SPRITELARGEUR/2) - chateauEau->position.y * (SPRITELARGEUR/2), (ORIGINEY * SPRITEHAUTEUR) + chateauEau->position.y * (SPRITEHAUTEUR/2) + chateauEau->position.x * (SPRITEHAUTEUR/2), 20, WHITE);
        chateaux = chateaux->next;
    }

}

///afficher le niveay -1 des canalisations

void afficher_level_eau(SpriteSheet_t* sheet, SimWorld_t* world){
    struct Maillon_t* chateaux = world->chateaux->premier;
    enum SPRITE_MAP map;
    while(chateaux){
        ChateauEau_t* chateauEau = (ChateauEau_t*)chateaux->data;
        if(chateauEau->orientation == ORIENTATION_4X6){
            map = SPRITE_EAU_4X6;
        } else {
            map = SPRITE_EAU_6X4;
        }
        sprite_sheet_draw_sprite(sheet, map, BLUE, chateauEau->position.x, chateauEau->position.y);
        chateaux = chateaux->next;
    }
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        if (hab->distance_chateau_eau[0] != DISTANCE_CHATEAU_EAU_NULL) {
            sprite_sheet_draw_sprite(sheet, SPRITE_GRATTE_CIEL_3X3, BLUE, hab->position.x, hab->position.y);
        }
        maison = maison->next;
    }
}

///afficher le niveau -2 de l'electricité

void afficher_level_elec(SpriteSheet_t* sheet, SimWorld_t* world){
    struct Maillon_t* centrales = world->centrales->premier;
    enum SPRITE_MAP map;
    while (centrales) {
        CentraleElectrique_t* centraleElectrique = (CentraleElectrique_t*)centrales->data;
        if(centraleElectrique->orientation == ORIENTATION_4X6){
            map = SPRITE_ENERGY_4X6;
        } else {
            map = SPRITE_ENERGY_6X4;
        }
        sprite_sheet_draw_sprite(sheet, map, YELLOW, centraleElectrique->position.x, centraleElectrique->position.y);
        centrales = centrales->next;
    }
    struct Maillon_t* maison = world->habitations->premier;
    while (maison) {
        Habitation_t * hab = (Habitation_t*) maison->data;
        if (hab->connexion_reseau_electrique) {
            sprite_sheet_draw_sprite(sheet, SPRITE_GRATTE_CIEL_3X3, YELLOW, hab->position.x, hab->position.y);
        }
        maison = maison->next;
    }
}

void afficher_level(SpriteSheet_t* sheet, SimWorld_t* world, GameplayScreen_t *gameplay){
    Rectangle textBoxElec = {440, 950, 50, 50};
    Rectangle textBoxEau = {660, 950, 50, 50};
    if (CheckCollisionPointRec(GetMousePosition(), textBoxEau)) {
        afficher_level_eau(&gameplay->spriteSheet, gameplay->world);
    }
    if (CheckCollisionPointRec(GetMousePosition(), textBoxElec)) {
        afficher_level_elec(&gameplay->spriteSheet, gameplay->world);
    }
}