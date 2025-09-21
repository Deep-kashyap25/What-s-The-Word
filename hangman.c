#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 7        // Maximum number of incorrect guesses
#define WORD_COUNT 10       // Number of possible words

// List of words to guess
const char *words[WORD_COUNT] = {
    "computer", "science", "programming", "hangman", "keyboard",
    "mouse", "laptop", "internet", "software", "hardware"
};

// Function to choose a random word
void pickWord(char *chosenWord) {
    srand(time(NULL));                // Seed the random number generator
    int index = rand() % WORD_COUNT;  // Randomly select a word
    strcpy(chosenWord, words[index]);
}

// Function to display the current state of the word
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

// Function to check if the word is fully guessed
int isWordGuessed(const char *word, const int guessed[]) {
    for (size_t i = 0; i < strlen(word); i++) {
        if (!guessed[i]) {
            return 0;  // Word is not fully guessed yet
        }
    }
    return 1;  // All letters are guessed
}

// Function to check if the guess is correct
int checkGuess(const char *word, int guessed[], char guess) {
    int correct = 0;
    for (size_t i = 0; i < strlen(word); i++) {
        if (tolower(word[i]) == tolower(guess)) {
            guessed[i] = 1;   // Mark the letter as guessed
            correct = 1;
        }
    }
    return correct;
}

int main() {
    char chosenWord[50];
    int guessed[50] = {0};      // Array to track guessed letters
    char guess;
    int attempts = 0;
    char playAgain;

    do {
        // Pick a random word and reset game variables
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
