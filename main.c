// include libraries for basic operations and gui

// wordle struct

struct Wordle {
    int counter;
    char *available_words[];

};


    
// // declare a array of all existing 5 letter words : available_words[]

// int checkWord(char word[],char available_words) {
//     for(int i=0; i<5; i++){
//         if(strcmp(word,available_words)==0){
//             //word found 
//             return 1;
//         }
//     }
//     return 0;
//     /*
//         check if word exists in available_words

//         1 - true
//         0 - false
//     */
// }

// // WORDLE
// char* wordle(char word[], char actualWord[]) {

//     // check if word is meaningful
//     int f = checkWord(word,available_words);

//     if (f) {

//     /*
//         for each letter in word
//             check if
//                 1 - word not present in actualWord
//                 2 - word present in actualWord but different position
//                 3 - word present in actualWord and same position.
//     */

//     // decrease the counter

//     }

//     return "*****" ; 
// }



// main

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

int main() {
    struct Wordle w;

    // w.counter = 6;
    // char wordlist[3][5] = {"audio","break","zudio"};

    // w.available_words = wordlist;

    // for(int i = 0 ; i < 3 ; i++){
    //     printf("%s \n", w.available_words[i] );
    // }
    FILE *fptr;

// Open a file in read mode
fptr = fopen("wordlist.txt", "r");
char word_list [13890];
fgets (word_list,13890,fptr);
printf("%s",word_list);
fclose(fptr);
char array [1389][5];





    // generate UI environment

    // gets inputs from GUI

    // call wordle function
    

    /*
        response = wordle(word);

        if (response == "*****") {
            retry                
        } else if (response == "22222") {
            success
        } else {
            if (counter == 0) {
                failed 
            } else { 
                print response and retry.
            }     
        }
    */


    // give response to GUI


    return 0;
}   
