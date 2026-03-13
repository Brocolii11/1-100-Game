# 1-100 Game

Two players take turns guessing each other's secret number. The first player to guess correctly wins.

> **Current implementation note**  
> Right now, the C program in this folder implements **Player vs Computer** only:
>
> - The **computer** secretly chooses a number between 1 and 100.
> - The player repeatedly guesses until they find the correct number.
> - After each guess, the program prints **Higher**, **Lower**, or **Correct!**.
>
> A full version of both players entering their own secret numbers, is not implemented yet. I don't know how to make that yet. Feel free to reach out if you know how to do it. 

## Setup

1. Each player secretly chooses a number between 1 and 100.
2. Decide who goes first (or flip a digital coin in the program).

## Rules

- On each turn, the active player guesses the **opponent's** secret number.
- The opponent responds with one of:
  - **Correct** — the guesser wins the game.
  - **Higher** — the secret number is greater than the guess.
  - **Lower** — the secret number is less than the guess.
- Players alternate turns. Play continues until one player guesses the opponent's number correctly.

