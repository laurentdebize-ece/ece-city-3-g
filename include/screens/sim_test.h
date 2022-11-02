
#ifndef ECECITY_SIM_TEST_H
#define ECECITY_SIM_TEST_H

#include "jeu.h"
#include <stdlib.h>

typedef struct SimTestScreen_t {
    ScreenInfo_t screen_info;

    // les structures viennent après.

} SimTestScreen_t;

// callbacks de l'écran.

/// Crée un écran de gameplay prêt à être utilisé.
SimTestScreen_t* sim_test_screen_create();

void simtest_on_enter(Jeu_t* jeu, SimTestScreen_t *gameplay);

void simtest_on_exit(Jeu_t* jeu, SimTestScreen_t *gameplay);

void simtest_update(Jeu_t* jeu, SimTestScreen_t *gameplay);

void simtest_draw(Jeu_t* jeu, SimTestScreen_t *gameplay);


#endif //ECECITY_SIM_TEST_H
