#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char names[2][20] = {"Dhruv", "Preet"};   // default players
int wins[2] = {0, 0};
int games = 0;

void clear_input() {
    while (getchar() != '\n');
}

void show_title() {
    printf("\n");
    printf("  ====================================\n");
    printf("  ||  NUMBER GUESSING GAME - 2 PLAYERS  ||\n");
    printf("  ====================================\n");
    printf("  %s  vs  %s\n", names[0], names[1]);
}

void show_score() {
    printf("\n  ------- SCOREBOARD -------\n");
    printf("  %-10s : %d win(s)\n", names[0], wins[0]);
    printf("  %-10s : %d win(s)\n", names[1], wins[1]);
    printf("  Games played: %d\n", games);
    if (wins[0] > wins[1])
        printf("  %s is leading!\n", names[0]);
    else if (wins[1] > wins[0])
        printf("  %s is leading!\n", names[1]);
    else
        printf("  It's a tie!\n");
    printf("  --------------------------\n");
}

void play(int max, int max_tries) {
    int secret = rand() % max + 1;
    int guess, turn = 0, tries = 0;   // turn: 0 = player 1, 1 = player 2
    int winner = -1;

    printf("\nI'm thinking of a number between 1 and %d.\n", max);
    printf("Players take turns. Each player has %d tries.\n\n", max_tries);

    while (tries < max_tries * 2) {
        printf("[%s] Your guess: ", names[turn]);
        if (scanf("%d", &guess) != 1) {
            printf("Please enter a valid number.\n");
            clear_input();
            continue;
        }
        tries++;

        if (guess < secret)
            printf("  ^ Too low!\n");
        else if (guess > secret)
            printf("  v Too high!\n");
        else {
            winner = turn;
            break;
        }
        turn = 1 - turn;   // switch player
    }

    games++;
    if (winner >= 0) {
        wins[winner]++;
        printf("\n  *** %s WINS! The number was %d. ***\n", names[winner], secret);
    } else {
        printf("\n  Nobody got it! The number was %d. It's a draw.\n", secret);
    }
    show_score();   // score after every game
}

void change_names() {
    int i;
    for (i = 0; i < 2; i++) {
        printf("Enter name for Player %d: ", i + 1);
        scanf("%19s", names[i]);
    }
    clear_input();
}

void how_to_play() {
    printf("\n--- How to Play ---\n");
    printf("The computer picks a secret number.\n");
    printf("%s and %s take turns guessing it.\n", names[0], names[1]);
    printf("First to guess it wins the game and gets a point.\n");
}

int main() {
    int choice;

    srand(time(NULL));

    while (1) {
        show_title();
        printf("  1. Easy   (1-50,  5 tries each)\n");
        printf("  2. Medium (1-100, 7 tries each)\n");
        printf("  3. Hard   (1-500, 9 tries each)\n");
        printf("  4. How to Play\n");
        printf("  5. Scoreboard\n");
        printf("  6. Change Player Names\n");
        printf("  7. Exit\n");
        printf("\nChoose an option: ");

        if (scanf("%d", &choice) != 1) {
            clear_input();
            printf("Invalid choice!\n");
            continue;
        }

        switch (choice) {
            case 1: play(50, 5); break;
            case 2: play(100, 7); break;
            case 3: play(500, 9); break;
            case 4: how_to_play(); break;
            case 5: show_score(); break;
            case 6: change_names(); break;
            case 7:
                printf("\nFinal result:");
                show_score();
                printf("Thanks for playing. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
