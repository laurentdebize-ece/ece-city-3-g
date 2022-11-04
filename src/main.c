#include <stdio.h>
#include "raylib.h"
#include "jeu.h"
#include "screens/sim_test.h"

int main() {
    Jeu_t jeu = {
            .should_exit = false,
            .screen = NULL
    };
    SimTestScreen_t* gameplay = sim_test_screen_create();
    jeu_run(&jeu, gameplay);
}
