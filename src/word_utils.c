#include "..\include\word_utils.h"
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


// is valid word 
/*
parse all the wordlist
    for every word check if it match with current_word

*/

// select random word
/*
use rand() function and select a random word from wordlist

*/