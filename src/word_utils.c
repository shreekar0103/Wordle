#include "..\include\word_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//.. means the file goes back 


/*
POINTERS

type *variable_name;

what do they store ? 
    - address

int *p = NULL;

int a = 5; 

&a - address

p = &a;

printf("%d", p); - address of a

printf("%d", *p); - value of a


struct A {
    int data;
};

struct A a = {0} ; 

struct A *p = NULL; 

p = &a; 

p->data

*/
void intialize_word_list(WordList *word_list){
    word_list->word_count = 0;
}


// load words from file
/*
    read the file and copy to string
    parse the string and extract words
        - copy all words into Wordlist
    update word count
*/
int load_words_from_file(WordList *word_list){
    char words_array[FILE_LENGTH+1];
    FILE *fptr;
    char ch;


    fptr = fopen("wordlist.txt", "r");
    if( NULL == fptr){
        printf("file cant be open ");
        return EXIT_FAILURE;
    }

    int wi = 0 ; 
    while ((ch = fgetc (fptr))!=EOF){
        words_array[wi++] = ch;
    }

    words_array[wi] = '\0';

    // word_arrays = [ 'z''a', 'u', 'd', 'i', 'o', ',',]

    int word_index = 0;
    
    for(int i=0; i < FILE_LENGTH; i++){
        if(i%6 < 5){
            word_list->Words[word_index].letter[i%6] = words_array[i];
        } else {
            word_list->Words[word_index].letter[i%6] = '\0';
            word_index++;
        }
    }


    fclose(fptr);

}

void print_wordlist(WordList *word_list){
 
    for(int wi=0 ; wi < MAX_WORDS; wi++){
        printf("%s\n", word_list->Words[wi].letter);
    }
    
}


// is valid word 
/*
parse all the wordlist
    for every word check if it match with current_word

*/
bool is_valid_word (Word *word, WordList *word_list ){
    for(int i=0; i<MAX_WORDS; i++){
       int is_same = strcmp(word_list->Words[i].letter, word->letter);
       if(is_same == 0){
            return true;
       }
    }
    return false;
}

// select random word
/*
use rand() function and select a random word from wordlist

*/

Word select_random_word(WordList *word_list){
    srand(time(NULL));
    int r = rand() % MAX_WORDS;
    Word random_word = word_list->Words[r]; 

    return random_word;
}
