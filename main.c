#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 1–100 Guessing Game
 *
 * The computer chooses a random number between 1 and 100.
 * The player repeatedly enters guesses.
 * After each guess, the program prints:
 *   - "Higher" if the secret number is bigger than the guess
 *   - "Lower"  if the secret number is smaller than the guess
 *   - "Correct! You win!" when the player guesses the number
 * At the end, the program shows how many valid attempts the player needed.
 */

void print_intro(void)
{
    printf("=============================================\n");
    printf("            1 - 100 Guessing Game            \n");
    printf("=============================================\n");
    printf("I have chosen a number between 1 and 100.\n");
    printf("Try to guess it! After each guess,\n");
    printf("I will tell you if you were: Higher, Lower, or Correct.\n\n");
}

void print_outro(int attempts)
{
    printf("=============================================\n");
    printf("            Game Over - You Won!             \n");
    printf("=============================================\n");
    printf("You guessed the number in %d attempt%s.\n",
           attempts, attempts == 1 ? "" : "s");
    printf("=============================================\n");
}

int main(void)
{
    /* secret  = computer's hidden number
     * guess   = player's current guess
     * attempts = count of valid guesses the player has made
     * play_again = flag to determine if the player wants to play again
     */
    int secret;
    int guess;
    int attempts = 0;
    int play_again = 1;

    /*
     * Seed the pseudo‑random number generator with the current time.
     * Without this, rand() would return the same sequence every run.
     */
    srand(time(NULL));

    /*
     * Generate a number in the range [1, 100].
     * rand() % 100 gives a value in [0, 99]; +1 shifts it to [1, 100].
     */
    secret = (rand() % 100) + 1;

    print_intro();

    /*
     * Main game loop.
     * We use while (1) to loop indefinitely and break when the player wins.
     */
    while (1)
    {
        printf("Enter your guess: ");

        /*
         * Read an integer from the user.
         * scanf returns the number of successfully read items.
         * If it is not 1, the input was not a valid integer.
         */
        if (scanf("%d", &guess) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            /*
             * Clear the rest of the current input line so the
             * next scanf call starts with fresh input.
             */
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            /* Skip the rest of this loop iteration and ask again. */
            continue;
        }

        /* If we reach here, the input was a valid number, so count it. */
        attempts++;
        /*
         * Compare the player's guess to the secret number and
         * provide feedback or end the game.
         */
        if (guess == secret)
        {
            printf("Correct! You win!\n");
            print_outro(attempts);
            break;  /* Exit the while loop, ending the game. */
        }
        else if (guess < secret)
        {
            printf("Higher\n");
        }
        else
        {
            printf("Lower\n");
        }
    }
    
    printf("Press Enter to exit.\n");
    getchar();
    return 0;
}