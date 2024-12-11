#include <word_utils.h>
typedef enum { INCORRECT, PRESENT, CORRECT} LetterStatus ;

typedef struct 
{
    int current_attempt;
    bool game_over ;
    bool game_win ;
    Word guesses[MAX_ATTEMPTS];
    LetterStatus guess_status[MAX_ATTEMPTS][MAX_WORD_LENGTH];
    Word target_word ;    
    
} GameState;

void initialize_game(GameState *game_state, WordList *word_list);
bool make_guess(GameState *game_state, Word *word);
void evaluate_guess(GameState *game_state);


