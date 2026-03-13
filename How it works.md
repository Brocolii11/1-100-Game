## 1. Big picture – what this program does

- **Goal**: Play a guessing game between the **computer** and the **player**.
- **Range**: The computer secretly picks a number between **1 and 100**.
- **Loop**: The player keeps guessing until they are right.
- **Feedback**: After each guess, the program says:
  - **"Higher"** → the secret number is bigger than your guess.
  - **"Lower"** → the secret number is smaller than your guess.
  - **"Correct! You win!"** → you found the secret number.

You can think of the program like this:

```text
START
  ↓
Computer picks a secret number (1–100)
  ↓
REPEAT
    Ask player for a guess
    ↓
    Is the input a valid number?
      ├─ NO → show error, clean input, ask again
      └─ YES → compare guess with secret
                ├─ guess < secret → say "Higher"
                ├─ guess > secret → say "Lower"
                └─ guess == secret → say "Correct! You win!" and stop
UNTIL correct guess
  ↓
END
```

---

## 2. Includes – standard C libraries

At the top of the file:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
```

- **`<stdio.h>`**: Standard Input/Output
  - Gives us `printf` (print to screen) and `scanf` (read from keyboard).
- **`<stdlib.h>`**: Standard Library
  - Gives us `rand` and `srand` for random numbers.
- **`<time.h>`**: Time functions
  - Gives us `time`, which we use to initialize (seed) the random number generator.

Without these includes, the compiler wouldn’t know about these functions.

---

## 3. `main` function – entry point and variables

```c
int main(void)
{
    /* secret  = computer's hidden number
     * guess   = player's current guess
     */
    int secret;
    int guess;
    /* counts how many valid guesses the player has made */
    int attempts = 0;
    ...
}
```

- **`int main(void)`**: Starting point of the program.
  - Every C program begins executing inside `main`.
- **Local variables**:
  - `int secret;` → holds the secret number the computer chooses.
  - `int guess;` → holds the most recent guess from the player.
  - `int attempts;` → counts how many **valid** guesses the player has entered.

These variables only exist inside `main` (they are local to this function).

---

## 4. Seeding and generating the secret number

```c
srand(time(NULL));
secret = (rand() % 100) + 1;
```

### 4.1 `srand(time(NULL));`

- **`rand()`** produces a sequence of pseudo-random numbers.
- If we never call `srand`, that sequence is the same every time we run the program.
- `time(NULL)` returns the current time in seconds.
- Using `srand(time(NULL))` gives a **different seed** almost every run, so the sequence of numbers from `rand()` changes.

Think of `srand` as **shuffling the deck of random numbers** using the current time.

### 4.2 `secret = (rand() % 100) + 1;`

- `rand()` returns a large positive integer.
- `rand() % 100` gives a remainder between **0 and 99**.
- Adding `+ 1` shifts that range up to **1 through 100**.

So:

```text
rand() % 100   → 0, 1, 2, ..., 99
          + 1  → 1, 2, 3, ..., 100
```

This gives us the secret number for the game.

---

## 5. Intro and outro: explaining the game to the player

To make the game nicer, we split some printing into **two helper functions**:

```c
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
```

### 5.1 `print_intro`

- Called near the start of `main`:

```c
secret = (rand() % 100) + 1;
print_intro();
```

- Purpose:
  - Show a **title banner**.
  - Explain the range (1–100) and basic rules.
  - Make the game feel more polished and friendly.

### 5.2 `print_outro`

- Called when the player finally wins:

```c
if (guess == secret)
{
    printf("Correct! You win!\n");
    print_outro(attempts);
    break;
}
```

- Purpose:
  - Show a **"Game Over"** banner.
  - Tell the player how many **attempts** it took.
  - Use `"attempt"` vs `"attempts"` correctly with the `%s` trick.

---

## 6. The main game loop – `while (1)`

```c
while (1)
{
    ...
}
```

- `while (1)` means **"loop forever"** because the condition `1` is always true.
- We break out of this infinite loop manually when the player guesses correctly.

Inside this loop we:

1. Ask for a guess.
2. Read the guess.
3. Validate the input.
4. Compare it to the secret.
5. Give feedback or end the game.

---

## 7. Asking for the guess and reading input

```c
printf("Enter your guess: ");

if (scanf("%d", &guess) != 1)
{
    printf("Invalid input. Please enter a number.\n");
    ...
    continue;
}
```

### 7.1 `printf("Enter your guess: ");`

- Prompts the player to type a number.
- No `\n` here, so the cursor stays on the same line as the question.

### 7.2 `scanf("%d", &guess)`

- `scanf` tries to read data from keyboard input.
- `"%d"` means: "read an integer".
- `&guess` is the **address of** the `guess` variable, so `scanf` can store the value there.
  - In C, functions like `scanf` need the address to modify variables outside of themselves.

### 7.3 Checking if input is valid

- `scanf` returns the number of items it successfully read.
  - If it reads one integer correctly → it returns **1**.
  - If the user types something non-numeric (like `"hello"`) → it returns **0** or another value not equal to 1.

So:

```c
if (scanf("%d", &guess) != 1)
```

means: **"If we did NOT successfully read one integer"**.

When input is invalid:

- We print an error message:

```c
printf("Invalid input. Please enter a number.\n");
```

- Then we clean up the input buffer and skip the rest of this loop iteration.

---

## 8. Clearing the input buffer

```c
int c;
while ((c = getchar()) != '\n' && c != EOF)
    ;
```

If the user types something invalid like:

```text
abc123⏎
```

Then:
- `scanf` will fail at `"abc"`, but those characters (and the rest of the line) are still sitting in the input buffer.
- If we don’t clear them, the next `scanf` call will immediately see the same bad characters and fail again.

To avoid this, we:

- Read characters one by one using `getchar()`.
- Stop when we see:
  - `'\n'` → the newline character (end of the current line), or
  - `EOF` → end-of-file.

The `while` loop body is just `;` (an empty statement), which means:

> "Keep reading and discarding characters until the end of the line."

After that, the next `scanf` starts with a **fresh** line of input.

Finally, we call:

```c
continue;
```

This jumps back to the top of the `while (1)` loop and asks the user to guess again.

---

## 9. Comparing the guess with the secret

If the input was valid, we reach this block:

```c
if (guess == secret)
{
    printf("Correct! You win!\n");
    break;
}
else if (guess < secret)
{
    printf("Higher\n");
}
else
{
    printf("Lower\n");
}
```

### 9.1 `if (guess == secret)`

- The player guessed the exact number.
- We print `"Correct! You win!"`.
- Then we call `break;` to leave the `while (1)` loop and move toward the end of `main`.

### 9.2 `else if (guess < secret)`

- The guess is **too small**.
- We print `"Higher"` to tell the player they need to guess a **larger** number.

### 9.3 `else`

- The only remaining case is `guess > secret` (too big).
- We print `"Lower"` to tell the player they need to guess a **smaller** number.

This logic repeats until the `if (guess == secret)` branch triggers and breaks the loop. At that point, `print_outro(attempts);` runs and shows how many guesses were needed.

---

## 10. Ending the program

```c
return 0;
```

- Returning `0` from `main` tells the operating system:
  - The program finished **successfully**, with no errors.

The full flow looks like this:

```text
main starts
  ↓
declare secret, guess
  ↓
seed random generator with time
  ↓
compute secret number (1–100)
  ↓
print greeting
  ↓
while (true)
    ↓
    ask for guess
    ↓
    read guess with scanf
      ├─ invalid → show message, clear input, continue
      └─ valid   → compare with secret
                    ├─ equal  → win, break
                    ├─ lower  → say "Higher"
                    └─ higher → say "Lower"
  ↓
leave loop after correct guess
  ↓
return 0 and exit
```

This file should give someone new to C (or new to this project) a clear mental model of **how the game works** and why each piece of code is there.

