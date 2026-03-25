# Game of Chance

A terminal-based betting game simulator written in C. This project features a user account system with basic credit management and three probability-based mini-games.

## Features

* **Account Management:** Tracks user credits, updates high scores, and allows for username changes and account resets.
* **Pick A Number:** A classic number guessing game. Players pay 10 credits for 3 attempts to guess a random number between 1 and 20, with "higher" or "lower" hints provided after each incorrect guess.
* **No Match:** A high-stakes probability game. Players place a custom bet, and the system generates 16 random numbers (1-100). The player wins double their bet only if there are zero matching numbers in the set.
* **Find The Ace:** A card game inspired by the Monty Hall problem. Players pick one of three cards (one Ace, two Queens) to find the Ace. After the initial pick, one Queen is revealed, and the player is given the option to keep their current pick, change their card, or increase their bet.
