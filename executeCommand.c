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
    pid_t pid;
    int status;

    // Create a child process
    pid = fork();

    if (pid == 0) { // Child process
        char *args[100]; // Assuming maximum number of arguments is 100
        int numArgs = 0;
        char *arg = strtok(command, " \n"); // Tokenize the command by space and newline

        while (arg != NULL) {
            args[numArgs++] = arg; // Store each argument in the args array
            arg = strtok(NULL, " \n"); // Get the next argument
        }

        args[numArgs] = NULL; // Set the last element of args array to NULL as required by execve

        // Execute the command with arguments using execve
        if (execve(args[0], args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }

    } else if (pid < 0) { // Error occurred while forking
        perror("fork");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Wait for the child process to complete
        wait(&status);
    }
}
