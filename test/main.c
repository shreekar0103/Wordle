#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/game.h"


int main() {

    WordList *wl;
    // Dynamic memory allocation
    wl = (WordList *) malloc(sizeof(WordList));

    int a;
    int *p;

    intialize_word_list(wl);
    load_words_from_file(wl);

    // print_wordlist(wl);

    // test if all words are loaded
    char lastWordLetters[MAX_WORD_LENGTH];
    
    strcpy(lastWordLetters, wl->Words[MAX_WORDS-1].letter);

    char testWordLetters[MAX_WORD_LENGTH+1] = {'s', 'h', 'a', 'v', 'e', '\0'};

    int is_same = strcmp(lastWordLetters, testWordLetters);

    if (is_same == 0){
        printf("test 1: WORDS LOADED - test PASSED ✅\n");
    } else printf("test 1: WORDS LOADED - test Failed ❌\n");

    // is_valid_word  test

    Word *test_word;
    test_word = (Word*) malloc(sizeof(Word));

    strcpy(test_word->letter, testWordLetters);

    if (is_valid_word(test_word,wl)) {
        printf("test 2: VALID WORD - test PASSED ✅\n");
    } else printf("test 2: VALID WORD - test Failed ❌\n");

    Word random_word = select_random_word(wl);

    if(is_valid_word(&random_word, wl)) {
        printf("test 3: RANDOM WORD - test PASSED ✅\n");
    } else printf("test 3: RANDOM WORD - test Failed ❌\n");

    GameState *gs;
    gs = (GameState* ) malloc(sizeof(GameState));
    initialize_game(gs,wl);
    
    strcpy(gs->target_word.letter, random_word.letter);

    Word guess_list[4] = {
        {'s', 'h', 'a', 'v', 'e', '\0'},
        {'a', 'h', 'a', 'v', 'e', '\0'},
        {'s', 'k', 'a', 'v', 'e', '\0'},
        {'s', 'h', 'a', 'v', 'e', '\0'}
    };

    strcpy(guess_list[3].letter, random_word.letter);

    int attempt = 0 ;
    
    while (!gs->game_over){
        
        printf("%s\n", guess_list[attempt].letter);
        // check valid word

        // if (is_valid_word(&guess_list[attempt], wl) == false) {
        //     printf("invalid word\n"); 
        //     continue;
        // }

        bool f = make_guess(gs, &guess_list[attempt++]);
        for(int j=0; j < MAX_WORD_LENGTH; j++) {
                printf("%d", gs->guess_status[gs->current_attempt][j]);
        }
        printf("\n");

        if (f) break;
    }

    if (gs->game_win) {
        printf("test 4: PLAY GAME - test PASSED ✅\n");
    } else printf("test 4: PLAY GAME - test Failed ❌\n");

    return 0;
}