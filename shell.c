#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function prototypes
void displayPrompt();
void readCommand(char *command);
void executeCommand(char *command);

int main(void) {
    char command[100]; // Assuming maximum command length of 100 characters

    while (1) {
        displayPrompt(); // Display the shell prompt
        readCommand(command); // Read user input command
        executeCommand(command); // Execute the command
    }

    return 0;
}

// Function to display the shell prompt
void displayPrompt() {
    printf("#cisfun$ ");
}

// Function to read user input command
void readCommand(char *command) {
    fgets(command, 100, stdin); // Read input from user
}

// Function to execute the command
void executeCommand(char *command) {
    // TODO: Implement command execution logic using execve, fork, etc.
    // Make sure to handle errors appropriately
}

