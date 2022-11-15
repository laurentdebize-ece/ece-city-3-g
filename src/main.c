#include <stdio.h>
#include "raylib.h"
#include "jeu.h"
#include "menu_principal.h"

const ScreenInfo_t EMPTY_SCREEN = {
        .draw_callback = NULL,
        .update_callback = NULL,
        .on_enter_callback = NULL,
        .on_exit_callback = NULL,
        .screen_name = "VIDE"
};


int main() {
    Jeu_t jeu = {
            .should_exit = false,
            .screen = NULL
    };
    jeu_run(&jeu, menu_principal_alloc());

    return 0;
}
