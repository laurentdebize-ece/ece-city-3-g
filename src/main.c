#include <stdio.h>
#include "raylib.h"
#include "jeu.h"
#include "screens/gameplay.h"

int main() {
    Jeu_t jeu = {
            .should_exit = false,
            .screen = NULL
    };
    GameplayScreen_t* gameplay = gameplay_create_screen();
    jeu_run(&jeu, gameplay);
}
