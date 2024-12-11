#include "../include/game.h"

void initialize_game(GameState *game_state, WordList *word_list){

    // Get a Word for current game
    game_state->target_word  = select_random_word(word_list);


    // Reset values for new game
    game_state->current_attempt = 0;
    game_state->game_over=false;
    game_state->game_win=false;

    // Reset guesses and its state
    // memset(address, value, size);

    memset(game_state->guesses, 0, sizeof(game_state->guesses));
    memset(game_state->guess_status, INCORRECT, sizeof(game_state->guess_status));
    
}

void evaluate_guess(GameState *game_state){

    // get current attempt word from guesses

    // compare with target word 

        // First check for CORRECT Values 

        // Check for PRESENT values

    // store the status in guess_status
}


bool make_guess(GameState *game_state, Word *word){
    // check if game is already over

    // check if maximum attempts are exceeded

    // update current attempt

    // store the word inside game_state->guesses

    // call evaluate_word

    // check latest guess_status and tell if won or not

}