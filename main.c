#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hack.h"

typedef struct{
    int id;
    int credit;
    int highscore;
    char name[50];
    int (*currentgame)();
} user;

user player;
int selection = 0;

int printMenu(){
    printf("\n---GAME OF CHANCE MENU---\n");
    printf("1. Pick Number Game\n");
    printf("2. No Match Game\n");
    printf("3. Find The Ace Game\n");
    printf("4. View Current Highscore\n");
    printf("5. Change username\n");
    printf("6. Reset Account\n");
    printf("7. Quit\n");
    do {
        printf("Your selection: ");
        scanf("%d", &selection);
    } while (selection < 1 || selection > 7);
    return selection;
}

void reset(user *playerdata){
    playerdata->credit = 100;
}

int back1 = 0;
void PickANum(){
    char playornot;
    if (player.credit < 10){
        printf("\nYou don't have enough credits (Need 10, have %d)\n", player.credit);
        return;
    }

    printf("\n--- Pick A Number Game ---\n");
    printf("Cost: 10 credits. 3 guesses to find a number (1-20).\n");

    if (back1 == 0){
        printf("Do you want to play? (y/n): ");
        scanf(" %c", &playornot); 
    }
    if (playornot == 'n'){
        return;
    }

    player.credit -= 10;
    int target = rand() % 20 + 1;
    int pick;
    int won = 0;

    for (int i = 0; i < 3; i++){
        printf("Guess %d/3: ", i + 1);
        scanf("%d", &pick);
        if (pick == target){
            printf("CONGRATULATIONS! You won 20 credits!\n");
            player.credit += 20;
            won = 1;
            break;
        } 
        else if (pick > target){
            printf("Lower\n");
        }
        else {
            printf("Higher\n");
        }
    }

    if (!won){
        printf("You lose! The number was %d.\n", target);
    }
    printf("Your current credit: %d\n", player.credit);
    printf("Play again? (y/n): ");
    scanf(" %c", &playornot);
    if (playornot == 'y'){
        back1 = 1;
        PickANum();
    }
}

int back2 = 0;
void NoMatch(){
    char playornot;
    int bet;

    if (player.credit <= 0) {
        printf("\nYou don't have enough credit!\n");
        return;
    }

    printf("\n--- No Match Game ---\n");
    printf("Random 16 cards, if no match, you win.\n");

    if (back2 == 0){
        printf("Do you want to play? (y/n): ");
        scanf(" %c", &playornot); 
    }
    if (playornot == 'n'){
        return;
    }
    do {
        printf("Current credit: %d\n",player.credit);
        printf("How many do you want to bet: ");
        scanf(" %d", &bet);
    } while (bet <= 0 || bet > player.credit);
    player.credit -= bet;

    int numbers[16];
    int match = -1;
    printf("Dealing 16 random numbers: \n");
    for (int i =0;i<16;i++){
        numbers[i] = rand()%100+1;
        printf("%d\t", numbers[i]);
        if ((i+1)%4 == 0){
            printf("\n");
        }
    }
    for (int i = 0; i < 15; i++){
        for (int j = i+1; j <16; j++){
            if (numbers[i] == numbers[j]){
                match = numbers[i];
                break;
            }
        }
    }

    if (match != -1){
        printf("You lose!!\n");
        printf("The number %d matched!\n", match);
    }
    else{
        printf("CONGRATULATIONS!!\n");
        printf("There were no matches! You win %d credits!\n", bet*2);
        player.credit += bet*2;
    }

    printf("Your current credit: %d\n", player.credit);
    printf("Play again? (y/n): ");
    scanf(" %c", &playornot);
    if (playornot == 'y'){
        back2 = 1;
        NoMatch();
    }
};

int back3 = 0;
void FindTheAce(){
    char playornot;
    int bet;

    if (player.credit <= 0) {
        printf("\nYou don't have enough credit!\n");
        return;
    }

    printf("\n--- Find The Ace Game ---\n");
    printf("3 cards (2 Queens, 1 Ace), pick the Ace, you win.\n");

    if (back3 == 0){
        printf("Do you want to play? (y/n): ");
        scanf(" %c", &playornot); 
    }
    if (playornot == 'n'){
        return;
    }
    do {
        printf("Current credit: %d\n",player.credit);
        printf("How many do you want to bet: ");
        scanf(" %d", &bet);
    } while (bet <= 0 || bet > player.credit);

    int choice;
    int randomqueen;
    int won = 0;
    printf("Dealing Cards\n");
    char cards[3];
    int x = rand()%3;
    for (int i = 0;i < 3; i++){
        if (i == x){
            cards[i] = 'A';
        }
        else{
            cards[i] = 'Q';
        }
    }
    printf("Cards: \t [X] \t [X] \t [X]\n");
    printf("       \t  1  \t  2  \t  3 \n");
    printf("Select a card: ");
    scanf("%d",&choice);
    choice -= 1;

    if (choice == x){
        do {
            randomqueen = rand()%3;
        } while (randomqueen == x );
    }
    else{
        do {
            randomqueen = rand()%3;
        } while (randomqueen == x || randomqueen == choice);
    }

    printf("Revealing 1 Queen\n");
    printf("Cards: ");
    for (int i = 0; i<3; i++){
        printf("\t");
        if (i == randomqueen){
            printf(" Q ");
        }
        else{
            printf(" X ");
        }
    }
    printf("\n");
    printf("      ");
    int amountspace = 3+6*choice + 2*choice;
    char space[22];

    for (int i = 0; i < amountspace;i++){
        strcat(space," ");
    }
    printf("%s",space);
    printf("^--Your pick\n");
    char changeorincrease = 'a';
    do {
        printf("Would you like to increase your bet (i) or change your pick (c): ");
        scanf(" %c",&changeorincrease);
    } while (changeorincrease != 'i' && changeorincrease != 'c');
    if (changeorincrease == 'i'){
        do {
            printf("Current credit: %d\n",player.credit);
            printf("Change to: ");
            scanf(" %d", &bet);
        } while (bet <= 0 || bet > player.credit);
        if (choice == x){
            won = 1;
        }
    }
    else{
        if (choice != x){
            won = 1;
        }
    }
    printf("Revealing cards\n");
    printf("Cards: ");
    for (int i = 0;i<3;i++){
        printf("\t");
        printf("%c", cards[i]);
    }
    printf("\n");
    if (won == 1){
        printf("CONGRATULATIONS, YOU WON %d CREDITS!!\n",bet*2);
        player.credit += bet;
    }
    else{
        printf("You lose\n");
        player.credit -= bet;
    }
    printf("Your current credit: %d\n", player.credit);
    printf("Play again? (y/n): ");
    scanf(" %c", &playornot);
    if (playornot == 'y'){
        back3 = 1;
        FindTheAce();
    }
}

int main() {
    player.highscore = 100;
    player.id = 2003;

    srand(time(0));
    reset(&player);
    strcpy(player.name, "Dave");

    while (selection != 7){
        printMenu();
        switch (selection){
            case 1:
                PickANum();
                back1 = 0;
                break;
            case 2: 
                NoMatch();
                back2 = 0;
                break;
            case 3: 
                FindTheAce();
                back3 = 0;
                break;
            case 4: 
                printf("\nYour current highscore: %d\n", player.highscore);
                break;
            case 5:
                printf("What's your new username: ");
                scanf("%s", player.name);
                printf("\nWelcome, %s!\n", player.name);
                break;
            case 6:
                reset(&player);
                printf("\nAccount reset to 100 credits.\n");
                break;
            case 7:
                printf("\nGameble end!!");
                break;
        }
        if (player.credit > player.highscore){
            player.highscore = player.credit;
        }
    }
    return 0;
}