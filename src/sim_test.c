
#include "screens/sim_test.h"

SimTestScreen_t* sim_test_screen_create() {
    SimTestScreen_t* gameplay = malloc(sizeof(SimTestScreen_t));
    gameplay->screen_info = (ScreenInfo_t) {
            .draw_callback = simtest_draw,
            .update_callback = simtest_update,
            .on_enter_callback = simtest_on_enter,
            .on_exit_callback = simtest_on_exit,
            .screen_name = "GAMEPLAY"
    };
    return gameplay;
}

void simtest_on_enter(Jeu_t* jeu, SimTestScreen_t *gameplay) {

}

void simtest_on_exit(Jeu_t* jeu, SimTestScreen_t *gameplay) {

}

void simtest_update(Jeu_t* jeu, SimTestScreen_t *gameplay) {

}

void simtest_draw(Jeu_t* jeu, SimTestScreen_t *gameplay) {
    ClearBackground(GREEN);
}
