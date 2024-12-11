#include <stdbool.h>

#define MAX_WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define MAX_WORDS 1389

typedef struct  
{
    char letter[MAX_WORD_LENGTH+1];
} Word;

typedef struct
{
    Word Words[MAX_WORDS];
    int word_count;
} WordList;

void intialize_word_list(WordList *word_list);
Word select_random_word(WordList *word_list);
bool is_valid_word (Word *word, WordList *word_list );
void load_words_from_file(WordList *word_list);


