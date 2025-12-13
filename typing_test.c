#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT 1000

int main() {
    char sentences[5][200] = {
        "The quick brown fox jumps over the lazy dog.",
        "Programming is fun and challenging.",
        "Speed typing improves your productivity.",
        "Practice makes perfect in everything.",
        "Welcome to the typing speed test application."
    };
    
    char userInput[MAX_INPUT];
    int sentenceIndex;
    int correctChars = 0, totalChars = 0, mistakes = 0;
    double timeTaken;
    double wpm, cps;
    int i, j;
    time_t startTime, endTime;
    char choice;
    
    printf("\n");
    printf("=====================================\n");
    printf("   TYPING SPEED TEST APPLICATION\n");
    printf("=====================================\n\n");
    
    do {
        // Select a random sentence (or use index based on user choice)
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
        
        // Calculate WPM (assuming average word length of 5 characters)
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
        
        // Display results
        printf("\n");
        printf("=====================================\n");
        printf("           TEST RESULTS\n");
        printf("=====================================\n");
        printf("Time Taken: %.1f seconds\n", timeTaken);
        printf("Total Characters Typed: %d\n", totalChars);
        printf("Correct Characters: %d\n", correctChars);
        printf("Mistakes: %d\n", mistakes);
        printf("Accuracy: %.2f%%\n", totalChars > 0 ? (correctChars * 100.0 / totalChars) : 0);
        printf("Characters Per Second (CPS): %.2f\n", cps);
        printf("Words Per Minute (WPM): %.2f\n", wpm);
        printf("=====================================\n\n");
        
        // Reset counters for next attempt
        correctChars = 0;
        mistakes = 0;
        
        // Ask if user wants to retry
        printf("Do you want to try again? (y/n): ");
        scanf("%c", &choice);
        getchar(); // Clear the newline from input buffer
        printf("\n");
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("Thank you for using Typing Speed Test!\n");
    printf("Good luck with your typing!\n\n");
    
    return 0;
}
