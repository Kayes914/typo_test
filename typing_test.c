#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT 1000
#define MAX_PLAYERS 10

int main() {
    char sentences[5][200] = {
        "The quick brown fox jumps over the lazy dog.",
        "Programming is fun and challenging.",
        "Speed typing improves your productivity.",
        "Practice makes perfect in everything.",
        "Welcome to the typing speed test application."
    };

    char playerNames[MAX_PLAYERS][50];
    int playerScores[MAX_PLAYERS];
    int playerCorrectChars[MAX_PLAYERS];
    int playerTotalChars[MAX_PLAYERS];
    int playerMistakes[MAX_PLAYERS];
    double playerWPM[MAX_PLAYERS];
    double playerCPS[MAX_PLAYERS];
    double playerAccuracy[MAX_PLAYERS];
    double playerTime[MAX_PLAYERS];
    int numPlayers;
    int currentPlayer;

    char userInput[MAX_INPUT];
    int sentenceIndex;
    int correctChars = 0, totalChars = 0, mistakes = 0;
    double timeTaken;
    double wpm, cps;
    int score;
    int i, j;
    time_t startTime, endTime;
    char choice;


    printf("   Typo Test Application\n\n");

    // Ask how many players
    printf("How many players will play? (1-%d): ", MAX_PLAYERS);
    scanf("%d", &numPlayers);
    getchar(); // Clear newline from input buffer

    if (numPlayers < 1 || numPlayers > MAX_PLAYERS) {
        printf("Invalid number! Setting to 1 player.\n");
        numPlayers = 1;
    }

    // Get player names
    printf("\nEnter player names:\n");
    for (i = 0; i < numPlayers; i++) {
        printf("Player %d name: ", i + 1);
        fgets(playerNames[i], sizeof(playerNames[i]), stdin);
        // Remove newline from name
        if (playerNames[i][strlen(playerNames[i]) - 1] == '\n') {
            playerNames[i][strlen(playerNames[i]) - 1] = '\0';
        }
        playerScores[i] = 0;
    }

    printf("\n");

    // Main loop for all players
    for (currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++) {
        printf("===== %s's Turn =====\n\n", playerNames[currentPlayer]);

        // Each player gets one turn
        // Select a random sentence
        sentenceIndex = rand() % 5;

        printf("Type the following sentence:\n");
        printf("\"%s\"\n\n", sentences[sentenceIndex]);
        printf("Start typing (press Enter when done):\n");

        // Start timer
        startTime = time(NULL);

        // Read user input
        if (fgets(userInput, sizeof(userInput), stdin) != NULL) {
            // Remove newline if present
            if (userInput[strlen(userInput) - 1] == '\n') {
                userInput[strlen(userInput) - 1] = '\0';
            }
        }

        // End timer
        endTime = time(NULL);
        timeTaken = difftime(endTime, startTime);

        // Calculate accuracy
        int minLen = strlen(userInput) < strlen(sentences[sentenceIndex]) ?
                     strlen(userInput) : strlen(sentences[sentenceIndex]);

        for (i = 0; i < minLen; i++) {
            if (userInput[i] == sentences[sentenceIndex][i]) {
                correctChars++;
            } else {
                mistakes++;
            }
        }

        // Count extra or missing characters as mistakes
        if (strlen(userInput) != strlen(sentences[sentenceIndex])) {
            mistakes += abs((int)strlen(userInput) - (int)strlen(sentences[sentenceIndex]));
        }

        totalChars = strlen(userInput);

        // Calculate WPM
        double words = totalChars / 5.0;
        double minutes = timeTaken / 60.0;
        if (minutes > 0) {
            wpm = words / minutes;
        } else {
            wpm = 0;
        }

        // Calculate Characters Per Second
        if (timeTaken > 0) {
            cps = totalChars / timeTaken;
        } else {
            cps = 0;
        }

        // Calculate score (accuracy * wpm)
        double accuracy = totalChars > 0 ? (correctChars * 100.0 / totalChars) : 0;
        score = (int)(accuracy * (wpm > 0 ? wpm : 0));

        // Store all results for later display
        playerScores[currentPlayer] = score;
        playerCorrectChars[currentPlayer] = correctChars;
        playerTotalChars[currentPlayer] = totalChars;
        playerMistakes[currentPlayer] = mistakes;
        playerWPM[currentPlayer] = wpm;
        playerCPS[currentPlayer] = cps;
        playerAccuracy[currentPlayer] = accuracy;
        playerTime[currentPlayer] = timeTaken;

        // Just show brief message that player is done
        printf("\n%s's test completed! Moving to next player...\n\n", playerNames[currentPlayer]);

        // Reset counters for next player
        correctChars = 0;
        mistakes = 0;
    }

    // Display final scores and winner
    printf("\n\n");
    printf("########################################\n");
    printf("#        TYPING TEST - ALL RESULTS    #\n");
    printf("########################################\n\n");
    
    int maxScore = -1;
    int winnerIndex = -1;
    
    for (i = 0; i < numPlayers; i++) {
        if (playerScores[i] > maxScore) {
            maxScore = playerScores[i];
            winnerIndex = i;
        }
    }

    // Show winner first
    printf("WINNER: %s with score %d\n\n", playerNames[winnerIndex], maxScore);

    printf("========== DETAILED RESULTS ==========\n\n");
    
    // Show all player results
    for (i = 0; i < numPlayers; i++) {
        printf("--- %s ---\n", playerNames[i]);
        printf("Time Taken: %.1f seconds\n", playerTime[i]);
        printf("Total Characters Typed: %d\n", playerTotalChars[i]);
        printf("Correct Characters: %d\n", playerCorrectChars[i]);
        printf("Mistakes: %d\n", playerMistakes[i]);
        printf("Accuracy: %.2f%%\n", playerAccuracy[i]);
        printf("Characters Per Second (CPS): %.2f\n", playerCPS[i]);
        printf("Words Per Minute (WPM): %.2f\n", playerWPM[i]);
        printf("Score: %d\n", playerScores[i]);
        printf("\n");
    }

    printf("========================================\n");
    printf("Thank you for using Typing Speed Test!\n");
    printf("Good luck with your typing!\n\n");

    return 0;
}
