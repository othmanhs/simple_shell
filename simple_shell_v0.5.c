#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

extern char **environ; // Global variable for environment variables

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_INPUT_LENGTH];
    int status = 0;

    while (1)
    {
        printf(":) ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Tokenize input into arguments
        char *token;
        int i = 0;
        token = strtok(input, " ");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Check for built-in exit command
        if (strcmp(args[0], "exit") == 0)
        {
            exit(status);
        }
        // Check for built-in env command
        else if (strcmp(args[0], "env") == 0)
        {
            char **env = environ;
            while (*env != NULL)
            {
                printf("%s\n", *env);
                env++;
            }
        }
        else
        {
            // Fork a child process
            pid_t pid = fork();

            if (pid == 0)
            {
                // Child process
                if (execvp(args[0], args) == -1)
                {
                    perror("Error");
                    exit(1);
                }
            }
            else if (pid < 0)
            {
                // Forking failed
                perror("Error");
                exit(1);
            }
            else
            {
                // Parent process
                wait(&status);
            }
        }
    }

    return 0;
}
