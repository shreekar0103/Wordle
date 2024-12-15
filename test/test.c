#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/game.h"

#define COLOR_GREEN "\e[1;32m"
#define COLOR_RED "\e[1;31m"
#define COLOR_OFF "\033[0m"
#define TEST_PASS "test PASSED (\xfb)\n"
#define TEST_FAIL "test FAILED (x)\n"

void print_test_result(bool cond){
    if (cond) {
        printf(COLOR_GREEN TEST_PASS COLOR_OFF); 
    } else {
        printf(COLOR_RED TEST_FAIL COLOR_OFF);
    } 
}

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

    printf("test 1: WORDS LOADED - ");
    print_test_result(is_same == 0);

    // is_valid_word  test

    Word *test_word;
    test_word = (Word*) malloc(sizeof(Word));

    strcpy(test_word->letter, testWordLetters);


    printf("test 2: VALID WORD - ");
    print_test_result(is_valid_word(test_word,wl));

    Word random_word = select_random_word(wl);

    printf("test 3: RANDOM WORD -");
    print_test_result(is_valid_word(&random_word, wl));
    
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

    printf("test 4: PLAY GAME - ");
    print_test_result(gs->game_win);

    return 0;
}