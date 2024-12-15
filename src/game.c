#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

void initialize_game(GameState *game_state, WordList *word_list){

    // Get a Word for current game
    game_state->target_word  = select_random_word(word_list);

    // Reset values for new game
    game_state->current_attempt = 0;
    game_state->game_over = false;
    game_state->game_win = false;

    // Reset guesses and its state
    // memset(address, value, size);

    memset(game_state->guesses, 0, sizeof(game_state->guesses));
    memset(game_state->guess_status, INCORRECT, sizeof(game_state->guess_status));
}

void evaluate_guess(GameState *game_state){

    // get current attempt word from guesses
    Word latest_word;
    bool used_letters[MAX_WORD_LENGTH] = {false};
    strcpy(latest_word.letter, game_state->guesses[game_state->current_attempt].letter);

    // compare with target word

        // First check for CORRECT Values
        for (int i = 0 ; i < MAX_WORD_LENGTH; i++){
            if (latest_word.letter[i] == game_state->target_word.letter[i]) {
                game_state->guess_status[game_state->current_attempt][i]  = CORRECT;
                used_letters[i] = true;
            }
        }

        // Check for PRESENT values

        /* 
            0
            tacat
              2
            caaty
            p___p
            p
        */
        

        for (int i = 0; i < MAX_WORD_LENGTH ; i++) {
            if (used_letters[i])
                continue;
            for (int j = 0; j < MAX_WORD_LENGTH; j++) {
                if (used_letters[j])
                    continue;
                LetterStatus isCorrect = game_state->guess_status[game_state->current_attempt][j];
            
                if (latest_word.letter[i] == game_state->target_word.letter[j] && isCorrect != CORRECT) {
                    game_state->guess_status[game_state->current_attempt][i] = PRESENT;
                    used_letters[j] = true;
                }
            }
        }

    // store the status in guess_status
}


bool make_guess(GameState *game_state, Word *word){
    // check if game is already over
    if (game_state->game_over){
        return game_state->game_win;
    }

    // check if maximum attempts are exceeded
    if (game_state->current_attempt > MAX_ATTEMPTS) {
        game_state->game_over = true;
        game_state->game_win = false;

        return game_state->game_win;

    }

    // store the word inside game_state->guesses
    strcpy(game_state->guesses[game_state->current_attempt].letter, word->letter);

    // call evaluate_word
    evaluate_guess(game_state);

    // check latest guess_status and tell if won or not
    LetterStatus last_attempt_state[MAX_WORD_LENGTH]; 
    
    for (int i=0 ; i < MAX_WORD_LENGTH; i++)
        last_attempt_state[i]  = game_state->guess_status[game_state->current_attempt][i];

    for (int state=0 ; state < MAX_WORD_LENGTH; state++) {
        if (last_attempt_state[state] != CORRECT) {
            return false;
        }
    }
    game_state->game_win = true;
    game_state->game_over = true;

    return game_state->game_win;
}