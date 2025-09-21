#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 7        
#define WORD_COUNT 10      

// List of words to guess
const char *words[WORD_COUNT] = {
    "computer", "science", "programming", "hangman", "keyboard",
    "mouse", "laptop", "internet", "software", "hardware"
};

// Function to choose a random word
void pickWord(char *chosenWord) {
    srand(time(NULL));                
    int index = rand() % WORD_COUNT;  // Randomly select a word
    strcpy(chosenWord, words[index]);
}

void displayWord(const char *word, const int guessed[]) {
    printf("\nWord: ");
    for (size_t i = 0; i < strlen(word); i++) {
        if (guessed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int isWordGuessed(const char *word, const int guessed[]) {
    for (size_t i = 0; i < strlen(word); i++) {
        if (!guessed[i]) {
            return 0;  
        }
    }
    return 1;  
}

int checkGuess(const char *word, int guessed[], char guess) {
    int correct = 0;
    for (size_t i = 0; i < strlen(word); i++) {
        if (tolower(word[i]) == tolower(guess)) {
            guessed[i] = 1;   
            correct = 1;
        }
    }
    return correct;
}

int main() {
    char chosenWord[50];
    int guessed[50] = {0};      
    char guess;
    int attempts = 0;
    char playAgain;

    do {
        pickWord(chosenWord);
        memset(guessed, 0, sizeof(guessed));  // Reset guessed letters
        attempts = 0;

        printf("\n Welcome to Hangman! \n");
        printf("You have %d incorrect attempts allowed.\n", MAX_TRIES);

        // Game loop
        while (attempts < MAX_TRIES) {
            displayWord(chosenWord, guessed);
            
            printf("\n Attempts left: %d\n", MAX_TRIES - attempts);
            printf("Enter a letter: ");
            scanf(" %c", &guess);
            guess = tolower(guess);  // Convert to lowercase

            // Check if the guess is correct
            if (checkGuess(chosenWord, guessed, guess)) {
                printf("\n Good guess!\n");
            } else {
                printf("\n Wrong guess!\n");
                attempts++;
            }

            // Check if the player won
            if (isWordGuessed(chosenWord, guessed)) {
                printf("\n Congratulations! You guessed the word: %s\n", chosenWord);
                break;
            }
        }

        // Check if the player lost
        if (!isWordGuessed(chosenWord, guessed)) {
            printf("\n You ran out of attempts! The word was: %s\n", chosenWord);
        }

        // Ask to play again
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (tolower(playAgain) == 'y');

    printf("\nThanks for playing Hangman! \n");
    
    return 0;
}

