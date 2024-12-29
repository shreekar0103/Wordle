#include <stdio.h>
#include <stdlib.h>
#include "src/gui.c"


int main (int argc, char **argv) {

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
    printf("Welcome to Wordle!!\n");
    printf("In this game you have to guess a 5 letters word that should match to our targeted word\n");
    printf("in this game The number of a letter will change to show you how close your guess was.\n");
    printf("If the letter turns to number 2, the letter is in the word, and it is in the correct spot.\n");
    printf("If the letter turns to number 1, the letter is in the word, but it is not in the correct spot.\n");
    printf("If the letter turns to number 0, the letter is not in the word.\n");
    printf("Let's Start The Game !!!!!!\n");

    GameState *gs =  (GameState*) malloc(sizeof(GameState));
    initialize_game(gs, wl);

    // Generate UI
    GtkApplication *app;
    int status;


    // create game UI 

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    GameUI* ui = NULL; 
    ui = create_game_gui(app, wl, gs);

    printf("KARTHIK %d", !ui);

    g_signal_connect (app, "activate", G_CALLBACK (activate), ui);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return 0;
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