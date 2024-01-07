#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20

void displayWord(char *word, char *guessedLetters) {
    for (int i = 0; i < strlen(word); i++) {
        if (strchr(guessedLetters, word[i]) != NULL) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int isGameOver(char *word, char *guessedLetters) {
    int correctGuesses = 0;

    for (int i = 0; i < strlen(word); i++) {
        if (strchr(guessedLetters, word[i]) != NULL) {
            correctGuesses++;
        }
    }

    if (correctGuesses == strlen(word)) {
        printf("Congratulations! You guessed the word: %s\n", word);
        return 1;
    }

    if (strlen(guessedLetters) >= MAX_TRIES) {
        printf("Sorry, you ran out of tries. The correct word was: %s\n", word);
        return 1;
    }
    return 0;
}
int main() {
    char *wordList[] = {"programming", "hangman", "computer", "algorithm", "language", "data structures", "array", "linked list", "graph", "queue", "trees"};
    srand(time(NULL));

    char *word = wordList[rand() % (sizeof(wordList) / sizeof(wordList[0]))];
    char guessedLetters[MAX_TRIES + 1] = {'\0'};
    char guess;

    printf("Welcome to Hangman!\n");

    // Provide a hint about the word's length
    printf("Hint: The word is related to %d letters.\n", (int)strlen(word));

    // Provide a hint about one of the letters
    int hintIndex = rand() % strlen(word);
    printf("Hint: One of the letters is '%c'.\n", word[hintIndex]);

    while (!isGameOver(word, guessedLetters)) {
        printf("Guessed letters: %s\n", guessedLetters);
        displayWord(word, guessedLetters);

        printf("Enter your guess: ");
        scanf(" %c", &guess);

        if (strchr(guessedLetters, guess) != NULL) {
            printf("You already guessed that letter. Try again.\n");
        } else {
            guessedLetters[strlen(guessedLetters)] = guess;

            if (strchr(word, guess) == NULL) {
                printf("Incorrect guess. Tries remaining: %d\n", MAX_TRIES - strlen(guessedLetters));
            }
        }
        
        if (isGameOver(word, guessedLetters)) {
            break;  // Exit the loop after displaying the final result
        }
    }

    return 0;
}