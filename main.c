#include <stdio.h>
#include <stdlib.h>
#include "include/game.h"


int main() {

    WordList *wl;
    // Dynamic memory allocation
    /*
        malloc - generic pointer 
        typecast to known struct type pointer
    */
    wl = (WordList *) malloc(sizeof(WordList));

    intialize_word_list(wl);
    load_words_from_file(wl);
    // print_wordlist(wl);

    Word user_input; 

    GameState *gs =  (GameState*) malloc(sizeof(GameState));
    initialize_game(gs, wl);

    while (!gs->game_over) {
        
        gets(user_input.letter);
        
        make_guess(gs, &user_input);

        for(int i = 0 ; i < MAX_WORD_LENGTH; i++)
            printf("%d", gs->guess_status[gs->current_attempt][i]);
        printf("\n");

        // update current attempt
        gs->current_attempt++;
    }

    if (gs->game_win) {
        printf("Hoorayy!!!! YOU WON !!\n");
    } else {
        printf("OOPS!!! Better Luck Next Time\n");
        printf("CORRECT WORD: %s\n", gs->target_word.letter);
    }

    return 0;
}