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
 */
int main(void)
{
    /* secret  = computer's hidden number
     * guess   = player's current guess
     */
    int secret;
    int guess;

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

    printf("I have chosen a number between 1 and 100.\n");

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

        /*
         * Compare the player's guess to the secret number and
         * provide feedback or end the game.
         */
        if (guess == secret)
        {
            printf("Correct! You win!\n");
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

    return 0;
}