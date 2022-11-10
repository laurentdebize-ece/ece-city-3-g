
#include "affichage.h"
#include "sim/chateau.h"

enum SPRITE_MAP get_route_sprite_variant(SimWorld_t *eceCity, int x, int y)
{
    if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
        eceCity->map[x][y - 1].type == KIND_ROUTE &&
        eceCity->map[x + 1][y].type == KIND_ROUTE &&
        eceCity->map[x - 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_14;
    }
    else if (eceCity->map[x - 1][y].type == KIND_ROUTE &&
             eceCity->map[x][y - 1].type == KIND_ROUTE &&
             eceCity->map[x + 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_13;
    }
    else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
             eceCity->map[x][y - 1].type == KIND_ROUTE &&
             eceCity->map[x - 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_12;
    }
    else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
             eceCity->map[x - 1][y].type == KIND_ROUTE &&
             eceCity->map[x + 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_11;
    }
    else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
             eceCity->map[x][y - 1].type == KIND_ROUTE &&
             eceCity->map[x + 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_10;
    }
    else if (eceCity->map[x][y - 1].type == KIND_ROUTE &&
             eceCity->map[x - 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_9;
    }
    else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
             eceCity->map[x + 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_8;
    }
    else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
             eceCity->map[x - 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_7;
    }
    else if (eceCity->map[x][y - 1].type == KIND_ROUTE &&
             eceCity->map[x + 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_6;
    }
    else if (eceCity->map[x][y + 1].type == KIND_ROUTE &&
             eceCity->map[x][y - 1].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_5;
    }
    else if (eceCity->map[x + 1][y].type == KIND_ROUTE &&
             eceCity->map[x - 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_4;
    }
    else if (eceCity->map[x - 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_3;
    }
    else if (eceCity->map[x][y + 1].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_2;
    }
    else if (eceCity->map[x + 1][y].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_1;
    }
    else if (eceCity->map[x][y - 1].type == KIND_ROUTE)
    {
        return SPRITE_ROUTE_0;
    }

    return SPRITE_ROUTE_0;
}

void affichage_draw_terrain_background(SpriteSheet_t *sheet, SimWorld_t *world)
{
    for (int i = 0; i < 45; ++i)
    {
        for (int j = 0; j < 35; ++j)
        {
            switch (world->map[i][j].type)
            {
            case KIND_VIDE:
                sprite_sheet_draw_sprite(sheet, SPRITE_TERRAIN_0, WHITE, i, j);
                break;

            case KIND_ROUTE:
                sprite_sheet_draw_sprite(sheet, get_route_sprite_variant(world, i, j), WHITE, i, j);
                break;

            default:
                break;
            }
        }
    }
}

/// Dessine les tuiles de la carte.
void affichage_draw_entities(SpriteSheet_t *sheet, SimWorld_t *world)
{

    // todo: trier les entités a dessiner par ordre croissant de distance à l'origine dans un tableau dynamique.
    struct Maillon_t *centrales = world->centrales->premier;
    while (centrales)
    {
        CentraleElectrique_t *centrale = (CentraleElectrique_t *)centrales->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_ENERGY_6X4, WHITE, centrale->position.x, centrale->position.y);
        centrales = centrales->next;
    }

    struct Maillon_t *chateaux = world->chateaux->premier;
    while (chateaux)
    {
        ChateauEau_t *chateau = (ChateauEau_t *)chateaux->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_EAU_4X6, WHITE, chateau->position.x, chateau->position.y);
        chateaux = chateaux->next;
    }

    struct Maillon_t *maison = world->habitations->premier;
    while (maison)
    {
        Habitation_t *hab = (Habitation_t *)maison->data;
        sprite_sheet_draw_sprite(sheet, SPRITE_GRATTE_CIEL_3X3, WHITE, hab->position.x, hab->position.y);
        maison = maison->next;
    }
}