#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define HAND_SIZE 5
#define NUM_PLAYERS 2
#define MAX_HANDS 5

// Function to compare integers (for qsort)
int compareInts(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to check hand rank
int checkHand(int hand[], int size) {
    qsort(hand, size, sizeof(int), compareInts);
    bool flush = true, straight = true;
    int pairs = 0, triples = 0, four_of_a_kind = 0;

    for (int i = 1; i < size; ++i) {
        if (hand[i] != hand[i - 1] + 1) {
            straight = false;
        }
    }

    for (int i = 0; i < size - 1; ++i) {
        if (hand[i] == hand[i + 1]) {
            if (i < size - 2 && hand[i] == hand[i + 2]) {
                ++triples;
                i += 2;
            } else if (i < size - 1 && hand[i] == hand[i + 1]) {
                ++pairs;
                ++i;
            }
        }
    }

    if (straight) {
        for (int i = 1; i < size; ++i) {
            if (hand[i] % 100 != hand[i - 1] % 100) {
                flush = false;
                break;
            }
        }
    }

    if (flush && straight) {
        if (hand[0] == 10) { 
            return 9; // Royal Flush
        }
        return 8; // Straight Flush
    }

    if (four_of_a_kind) {
        return 7; // Four of a Kind
    }

    if (triples && pairs) {
        return 6; // Full House
    }

    if (flush) {
        return 5; // Flush
    }

    if (straight) {
        return 4; // Straight
    }

    if (triples) {
        return 3; // Three of a Kind
    }

    if (pairs == 2) {
        return 2; // Two Pair
    }

    if (pairs == 1) {
        return 1; // One Pair
    }

    return 0; // High Card
}

// Function to evaluate hand rank
int evaluateHandRank(int hand[]) {
    return checkHand(hand, HAND_SIZE);
}

// Function to compare two poker hands and determine the winner
int compareHands(int hand1[], int hand2[]) {
    int rank1 = evaluateHandRank(hand1);
    int rank2 = evaluateHandRank(hand2);

    if (rank1 > rank2) {
        return 1; // Hand 1 wins
    } else if (rank1 < rank2) {
        return 2; // Hand 2 wins
    } else {
        // If both hands have the same rank, compare highest cards
        for (int i = HAND_SIZE - 1; i >= 0; --i) {
            if (hand1[i] % 100 > hand2[i] % 100) {
                return 1; // Hand 1 wins
            } else if (hand1[i] % 100 < hand2[i] % 100) {
                return 2; // Hand 2 wins
            }
        }
        return 0; // It's a tie
    }
}

// Function to parse a line of input into two separate poker hands
void parsePokerHands(int hand1[], int hand2[]) {
    for (int i = 0; i < HAND_SIZE; i++) {
        scanf("%d", &hand1[i]);
    }

    for (int i = 0; i < HAND_SIZE; i++) {
        scanf("%d", &hand2[i]);
    }
}

// Function to print a poker hand
void printHand(int hand[]) {
    for (int i = 0; i < HAND_SIZE; i++) {
        if (hand[i] % 100 == 11)
            printf("J");
        else if (hand[i] % 100 == 12)
            printf("Q");
        else if (hand[i] % 100 == 13)
            printf("K");
        else if (hand[i] % 100 == 14)
            printf("A");
        else
            printf("%d", hand[i] % 100);

        if (hand[i] / 100 == 1)
            printf("H ");
        else if (hand[i] / 100 == 2)
            printf("D ");
        else if (hand[i] / 100 == 3)
            printf("C ");
        else if (hand[i] / 100 == 4)
            printf("S ");
    }
}

int main() {
    srand(time(NULL));

    int playerHands[NUM_PLAYERS][HAND_SIZE];
    int wins[NUM_PLAYERS] = {0};

    printf("Enter poker hands (max %d hands, each hand separated by space):\n", MAX_HANDS);

    // Read and process input hands
    int totalHands = 0;
    while (totalHands < MAX_HANDS) {
        printf("Hand %d\n", totalHands + 1);
        parsePokerHands(playerHands[0], playerHands[1]);
        int winner = compareHands(playerHands[0], playerHands[1]);

        printf("Player 1\tPlayer 2\n");
        printHand(playerHands[0]);
        printf("\t\t");
        printHand(playerHands[1]);
        printf("\n");

        if (winner == 1) {
            printf("Winner: Player 1\n\n");
            wins[0]++;
        } else if (winner == 2) {
            printf("Winner: Player 2\n\n");
            wins[1]++;
        } else {
            printf("Winner: Tie\n\n");
        }
        totalHands++;
    }

    // Print results
    printf("Player 1 wins: %d times\n", wins[0]);
    printf("Player 2 wins: %d times\n", wins[1]);
    if (wins[0] > wins[1]) {
        printf("Player 1 wins more games!\n");
    } else if (wins[0] < wins[1]) {
        printf("Player 2 wins more games!\n");
    } else {
        printf("Both players have the same number of wins!\n");
    }

    return 0;
}
