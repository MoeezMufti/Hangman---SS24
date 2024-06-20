#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "hangman_functions.h"

int main() {
    char literature[] = "literature";
    char film[] = "movies";

    srand(time(NULL));

    char playAgain = 'Y';                                                                    //initialize playAgain to 'Y' to restart the game. Else, the game wouldn't begin.
                                                                                    

    while (playAgain == 'Y' || playAgain == 'y') {                                           //game will loop as long as the player wants

        char *word;                                                                         //pointer used so that it can store the memory address of both lit and mov.
        char hint[100];
        int maxTries = 6;
        
        if (rand() % 2 == 0) {                                                               //randomly selects between literature and movie for level one
            word = literature;
            strcpy(hint, "a pile of papers in a stack");
        } else {
            word = film;
            strcpy(hint, "moving pictures");
        }

        // function for declaring the results of level 1

        int levelOneResult = playGame(word, hint, maxTries);                                 /*if the result is true (non-zero), it proceeds to execute
                                                                                               the next code block. It stores the results of the first game level*/


        if (levelOneResult) {                                                                //conditioning levelOneResult to its respective category if true (non-zero)
            char *literatureOptions[] = {"Tolstoy", "Dickens", "Shelley", "Flaubert"};
            char *literatureHints[] = {"War and Anna", "Oliver Twist", "Doctor Franken", "Bovary"};
            char *moviesOptions[] = {"Christopher", "Hitchcock", "Scorcese", "Kubrick"};
            char *moviesHints[] = {"Dark Knight", "Vertigo", "Taxi Driver", "The Shining"};

            
            int totalLiteratureOptions = sizeof(literatureOptions) / sizeof(literatureOptions[0]);    //returns the number of entities through bytes calculations
            

            int totalMoviesOptions = sizeof(moviesOptions) / sizeof(moviesOptions[0]);        /*sizeOf allows correct number of entities to be passed so that
                                                                                               it can randomize it based on the category using the integer value*/
            

            int totalOptions;                                                                
            char **options;                                                                  /*it points to the pointer of movie or literaturOptions. 
                                                                                              This way there is no need to initialize again and again.*/
            char **hints;
            
            // Hints and options for the respective word
            
            if (strcmp(word, literature) == 0) {                                            /*strcmp compares the word pointer to literature array. If it is equal, it returns zero  
                                                                                             and then points to the respective hints and category*/              
                options = literatureOptions;
                hints = literatureHints;
                totalOptions = totalLiteratureOptions;

            } else {
                options = moviesOptions;
                hints = moviesHints;
                totalOptions = totalMoviesOptions;                                                  
            }
            
            
            levelTwo(options, hints, totalOptions);              //for playing level two
        }

        printf("Do you want to play again? (Y/N): ");
        while (1) {                                             //the condition of 1 will run infinitely until a correct input is entered.
                                                                
            scanf(" %c", &playAgain);                           
            int c;
            while ((c = getchar()) != '\n' && c != EOF);        //flushes an input buffer

            if (playAgain == 'Y' || playAgain == 'y' || playAgain == 'N' || playAgain == 'n') {
                break;
            } 
            
            else {
                printf("Invalid character. Please enter 'Y' or 'N': \n");
            }
        }

        if (playAgain == 'Y' || playAgain == 'y') {
            system("cls");                                      //clears the system
        }
    }

    printf("Thank you for playing! Goodbye!\n");

    return 0;
}

void displayHangman(int tries) {
    switch (tries) {
        
        case 1:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |      \n");
            printf("  |      \n");
            printf("  |\n");
            printf("__|__\n\n");
            break;
        case 2:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |     |\n");
            printf("  |      \n");
            printf("  |\n");
            printf("__|__\n\n");
            break;
        case 3:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\n");
            printf("  |      \n");
            printf("  |\n");
            printf("__|__\n\n");
            break;
        case 4:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |      \n");
            printf("  |\n");
            printf("__|__\n\n");
            break;
        case 5:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |    /  \n");
            printf("  |\n");
            printf("__|__\n\n");
            break;
        case 6:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |    / \\\n");
            printf("  |\n");
            printf("__|__\n\n");
            break;
        default:
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |      \n");
            printf("  |      \n");
            printf("  |      \n");
            printf("  |\n");
            printf("__|__\n\n");
            break;
    }
}

void displayWord(char word[], int length, int guessed[]) {     //function is for displaying the word with either blanks or correct

    for (int i = 0; i < length; i++) {                         //iterates through the length of the entire word

        if (guessed[i]) {                                      //if the letter is correct, guessed[1] is output so it prints the letter
            printf("%c ", word[i]);
        } else {                                               //if not guessed then guessed[0], so it will print a blank space for every unguessed
            printf("_ ");
        }
    }
    printf("\n\n");
}

int guessedWord(char word[], int length, int guessed[]) {     //function checks whether or not the letter is correctly guessed

    for (int i = 0; i < length; i++) {                        //iterates through the length of the word

        if (!guessed[i]) {                                    //if the letter guessed is incorrect, the function will become not true
            return 0;
        }
    }
    return 1;                                                 //if correct, it will be guessed[1] which will print the letter on screen
}

int playGame(char word[], char hint[], int maxTries) {          
    int wordLength = strlen(word);                           //length is stored in the wordLength variable, which will be used later to allocate memory for the guessed array.
    
    int *guessed = (int *)malloc(wordLength * sizeof(int));  /*Dynamically allocate memory of pointer guessed to int using malloc based on its length 
                                                               because array has a fixed size and we need dynamic size*/
    
    if (guessed == NULL) {                                   //test for determining if memory is successfully allocated
        return 0;
    }

    for (int i = 0; i < wordLength; i++) {
        guessed[i] = 0;                                      //initializes to zero cuz no letter has been guessed in the beginning
    }
    int tries = 0;
    char wrongLetters[26] = {0};                             //whole alphabetical array and initialized to 0 for beginning

    int wrongIndex = 0;                                      /*keep track of wrong letter input. A wrong letter is placed into the wrongLetters array
                                                              and then Index is incremented by 1 to the next available position in the array */

    printf("Welcome to Hangman!\n");                            
    printf("This is Level One! Once you guess this correctly, you will proceed to level two!\n");

    displayHangman(tries);                                   //initial display of the gallows at default

    while (tries < maxTries) {                               //as long as tries<maxTries the game will run
        displayWord(word, wordLength, guessed);

        printf("Hint: %s\n", hint);                         
        printf("Wrong letters: ");
        for (int i = 0; i < wrongIndex; i++) {             //iterate through the word, if letter is not found, it's put into the array
            printf("%c ", wrongLetters[i]);
        }
        printf("\n");

        printf("Number of attempts left: %d\n", maxTries - tries); //subtracts the tries done with the max

        char guess;
        printf("Enter your guess: ");
        scanf(" %c", &guess);
        guess = tolower(guess);                             //to accept both lower 

        int correct = 0;                                    //initialized to 0 for beginning
        for (int i = 0; i < wordLength; i++) {
            if (tolower(word[i]) == guess) {                
                guessed[i] = 1;                             //if letter is correct, it will result in true
                correct = 1;                                //this will change to 1 so true indicating at least one attempt is true
            }
        }

        if (!correct) {                                     //if not correct it will return 0
            wrongLetters[wrongIndex++] = guess;             //incorrect guess is stored in Letters array and the Index is incremented to next position for the next wrong      
            tries++;                                        
        }
        
        displayHangman(tries);                              //by checking tries done, the respective hangman will appear

        if (guessedWord(word, wordLength, guessed)) {
            printf("Congratulations! You guessed the word: %s\n", word);
            return 1;                                                      
        }
    }

    displayHangman(tries);                                  //when tries are over

    printf("Sorry, you lost. The word was: %s\n", word);
    return 0;
}

void levelTwo(char *options[], char *hints[], int numSpaces) { //numSpaces is passed as the argument for totalOptions
    srand(time(NULL));

    int choice = rand() % numSpaces;                       //randomises between 0 & numSpaces (the number of options)- 1 and stores it in choice
    char *word = options[choice];                          //the choice is then used to select respective hint and option.
    char *hint = hints[choice];                            //pointers help to manipulate by storing memory addresses without duplication
    int maxTries = 6;

    int wordLength = strlen(word);                         //returns the number of characters in integer
    int *guessed = (int *)malloc(wordLength * sizeof(int));
    if (guessed == NULL) {
        
        return;                                             // if memory allocation failed, handle the error or exit gracefully
    }

    for (int i = 0; i < wordLength; i++) {
        guessed[i] = 0;
    }
    int tries = 0;
    char wrongLetters[26] = {0};
    int wrongIndex = 0;
    int correctGuessStreak = 0;

    printf("\n\n");
    printf("******************************\n");
    printf(" Welcome to Level Two! \n");
    printf("******************************\n");

    displayHangman(tries);                                      // initial display of the gallows at default

    printf("Hint: %s\n", hint);

    while (tries < maxTries) {

        displayWord(word, wordLength, guessed);

        printf("Wrong letters: ");
        for (int i = 0; i < wrongIndex; i++) {
        printf("%c ", wrongLetters[i]);
        }
        
        printf("\n");

        printf("Number of attempts left: %d\n", maxTries - tries);

        char guess;
        printf("Enter your guess: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        int correct = 0;
        for (int i = 0; i < wordLength; i++) {
            if (tolower(word[i]) == guess) {
                guessed[i] = 1;
                correct = 1;
                }
            }

         if (correct) {
            correctGuessStreak++;                              //each time a correct entry is input, the variable will increment by one

         if (correctGuessStreak % 3 == 0 && tries > 0) {       //for every correct streak divisible by 3 & for at least one incorrect try, the tries will decrement
                tries--;
            }
        } else {
            wrongLetters[wrongIndex++] = guess;
            tries++;
            correctGuessStreak = 0;                            //for an incorrect entry within the streak, the variable resets to zero
        }

        displayHangman(tries);

        if (guessedWord(word, wordLength, guessed)) {
        printf("Congratulations! You guessed the word: %s\n", word);
        return;
        }
    }

    displayHangman(tries);
    printf("Sorry, you lost. The word was: %s\n", word);
    printf("Game Over!\n");
    return;
    
    free(guessed);                                              /*this releases any memory for the guessed variable to ensure no excess or rewritten memory is 
                                                                  present when game is restarted*/
    return;
}
