#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void displayHangman(int tries);
void displayWord(char word[], int length, int guessed[]);
int guessedWord (char word[], int length, int guessed[]);
int playGame(char word[], char hint[], int maxTries);
void levelTwo(char *options[], char *hints[], int numSpaces);

